/**
 * \file nacm.c
 * \author Radek Krejci <rkrejci@cesnet.cz>
 * \brief Implementation of NETCONF Access Control Module defined in RFC 6536
 *
 * Copyright (c) 2012-2014 CESNET, z.s.p.o.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name of the Company nor the names of its contributors
 *    may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * ALTERNATIVELY, provided that this notice is retained in full, this
 * product may be distributed under the terms of the GNU General Public
 * License (GPL) version 2 or later, in which case the provisions
 * of the GPL apply INSTEAD OF those given above.
 *
 * This software is provided ``as is, and any express or implied
 * warranties, including, but not limited to, the implied warranties of
 * merchantability and fitness for a particular purpose are disclaimed.
 * In no event shall the company or contributors be liable for any
 * direct, indirect, incidental, special, exemplary, or consequential
 * damages (including, but not limited to, procurement of substitute
 * goods or services; loss of use, data, or profits; or business
 * interruption) however caused and on any theory of liability, whether
 * in contract, strict liability, or tort (including negligence or
 * otherwise) arising in any way out of the use of this software, even
 * if advised of the possibility of such damage.
 *
 */

#define _GNU_SOURCE
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include <libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>

#include "messages.h"
#include "messages_xml.h"
#include "netconf_internal.h"
#include "nacm.h"
#include "datastore.h"
#include "datastore_internal.h"
#include "notifications.h"

static const char rcsid[] __attribute__((used)) ="$Id: "__FILE__": "RCSID" $";

extern struct ncds_ds* nacm_ds; /* NACM datastore from datastore.c */

typedef enum {
	NACM_RULE_NOTSET = 0,
	NACM_RULE_OPERATION = 1,
	NACM_RULE_NOTIF = 2,
	NACM_RULE_DATA = 3
} NACM_RULE_TYPE;

struct nacm_group {
	char* name;
	char** users;
};

struct nacm_ns {
	char* prefix;
	char* href;
	struct nacm_ns *next;
};

struct nacm_path {
	char* path;
	struct nacm_ns* ns_list;
};

struct nacm_rule {
	char* module;
	NACM_RULE_TYPE type;
	/*
	 * data item contains:
	 * - rpc-name for NACM_RULE_OPERATION type
	 * - notification-name for NACM_RULE_NOTIF type
	 * - path for NACM_RULE_DATA type
	 */
	union {
		struct nacm_path* path;
		char** rpc_names;
		char** ntf_names;
	} type_data;
	uint8_t access; /* macros NACM_ACCESS_* */
	bool action; /* false (0) for permit, true (1) for deny */
};

struct rule_list {
	char** groups;
	struct nacm_rule** rules;
};

/* access to the NACM statistics */
struct nc_shared_info *nc_info;

static void nacm_path_free(struct nacm_path* path)
{
	struct nacm_ns* aux;

	if (path != NULL) {
		free(path->path);
		for (aux = path->ns_list; aux!= NULL; aux = path->ns_list) {
			path->ns_list = aux->next;
			free(aux->prefix);
			free(aux->href);
			free(aux);
		}
		free(path);
	}
}

static struct nacm_path* nacm_path_dup(struct nacm_path* orig)
{
	struct nacm_path *new;
	struct nacm_ns *ns, *ns_new;

	if (orig == NULL || orig->path == NULL) {
		return (NULL);
	}

	new = malloc(sizeof(struct nacm_path));
	if (new == NULL) {
		nc_verb_error("Memory reallocation failed (%s:%d).", __FILE__, __LINE__);
		return (NULL);
	}
	new->path = strdup(orig->path);
	new->ns_list = NULL;

	for(ns = orig->ns_list; ns != NULL; ns = ns->next) {
		ns_new = malloc(sizeof(struct nacm_ns));
		if (ns_new == NULL) {
			nc_verb_error("Memory reallocation failed (%s:%d).", __FILE__, __LINE__);
			nacm_path_free(new);
			return (NULL);
		}
		ns_new->prefix = strdup(ns->prefix);
		ns_new->href = strdup(ns->href);
		ns_new->next = new->ns_list;
		new->ns_list = ns_new;
	}

	return (new);
}

static void nacm_rule_free(struct nacm_rule* r)
{
	int i;

	if (r != NULL) {
		if (r->type == NACM_RULE_NOTIF) {
			if (r->type_data.ntf_names != NULL) {
				for(i = 0; r->type_data.ntf_names[i] != NULL; i++) {
					free(r->type_data.ntf_names[i]);
				}
				free(r->type_data.ntf_names);
			}
		} else if (r->type == NACM_RULE_OPERATION) {
			if (r->type_data.rpc_names != NULL) {
				for(i = 0; r->type_data.rpc_names[i] != NULL; i++) {
					free(r->type_data.rpc_names[i]);
				}
				free(r->type_data.rpc_names);
			}
		} else if (r->type == NACM_RULE_DATA) {
			nacm_path_free(r->type_data.path);
		}
		free(r->module);
		free(r);
	}
}

void nacm_rule_list_free(struct rule_list* rl)
{
	int i;

	if (rl != NULL) {
		if (rl->groups != NULL) {
			for(i = 0; rl->groups[i] != NULL; i++) {
				free(rl->groups[i]);
			}
			free(rl->groups);
		}
		if (rl->rules != NULL) {
			for(i = 0; rl->rules[i] != NULL; i++) {
				nacm_rule_free(rl->rules[i]);
			}
			free(rl->rules);
		}
		free(rl);
	}
}

static struct rule_list* nacm_rule_list_dup(struct rule_list* r)
{
	struct rule_list *new = NULL;
	int i, j;

	if (r != NULL) {
		new = malloc(sizeof(struct rule_list));
		if (new != NULL) {
			if (r->groups != NULL) {
				for(i = 0; r->groups[i] != NULL; i++);
				new->groups = malloc((i+1) * sizeof(char*));
				if (new->groups == NULL) {
					free(new);
					return (NULL);
				}
				for(i = 0; r->groups[i] != NULL; i++) {
					new->groups[i] = strdup(r->groups[i]);
				}
				new->groups[i] = NULL;
			} else {
				new->groups = NULL;
			}

			if (r->rules != NULL) {
				for(i = 0; r->rules[i] != NULL; i++);
				new->rules = malloc((i+1) * sizeof(char*));
				if (new->rules == NULL) {
					nacm_rule_list_free(new);
					return (NULL);
				}
				for(i = 0; r->rules[i] != NULL; i++) {
					new->rules[i] = malloc(sizeof(struct nacm_rule));
					if (new->rules[i] == NULL) {
						nacm_rule_list_free(new);
						return (NULL);
					}
					new->rules[i]->type = r->rules[i]->type;
					switch(new->rules[i]->type) {
					case NACM_RULE_NOTIF:
						for (j = 0; r->rules[i]->type_data.ntf_names != NULL && r->rules[i]->type_data.ntf_names[j] != NULL; j++) ;
						if (j > 0) {
							new->rules[i]->type_data.ntf_names = malloc((j + 1) * sizeof(char*));
							if (new->rules[i]->type_data.ntf_names == NULL) {
								nacm_rule_list_free(new);
								return (NULL);
							}
							for (j = 0; r->rules[i]->type_data.ntf_names[j] != NULL; j++) {
								new->rules[i]->type_data.ntf_names[j] = strdup(r->rules[i]->type_data.ntf_names[j]);
							}
							new->rules[i]->type_data.ntf_names[j] = NULL; /* list terminating NULL byte */
						}
						break;
					case NACM_RULE_OPERATION:
						for (j = 0; r->rules[i]->type_data.rpc_names != NULL && r->rules[i]->type_data.rpc_names[j] != NULL; j++);
						if (j > 0) {
							new->rules[i]->type_data.rpc_names = malloc((j + 1) * sizeof(char*));
							if (new->rules[i]->type_data.rpc_names == NULL) {
								nacm_rule_list_free(new);
								return (NULL);
							}
							for (j = 0; r->rules[i]->type_data.rpc_names[j] != NULL; j++) {
								new->rules[i]->type_data.rpc_names[j] = strdup(r->rules[i]->type_data.rpc_names[j]);
							}
							new->rules[i]->type_data.rpc_names[j] = NULL; /* list terminating NULL byte */
						}
						break;
					case NACM_RULE_DATA:
						new->rules[i]->type_data.path = (r->rules[i]->type_data.path == NULL) ? NULL : nacm_path_dup(r->rules[i]->type_data.path);
						break;
					default:
						new->rules[i]->type_data.path = NULL; /* covers also type_data.rpc_names and type_data.ntf_names */
						break;
					}
					new->rules[i]->action = r->rules[i]->action;
					new->rules[i]->access = r->rules[i]->access;
					new->rules[i]->module = (r->rules[i]->module == NULL) ? NULL : strdup(r->rules[i]->module);
				}
				new->rules[i] = NULL;
			} else {
				new->rules = NULL;
			}
		}
	}

	return (new);
}

struct rule_list** nacm_rule_lists_dup(struct rule_list** list)
{
	int i;
	struct rule_list** new;

	if (list == NULL) {
		return (NULL);
	}

	for(i = 0; list[i] != NULL; i++);
	new = malloc((i+1) * sizeof(struct rule_list*));
	if (new == NULL) {
		return (NULL);
	}
	for(i = 0; list[i] != NULL; i++) {
		new[i] = nacm_rule_list_dup(list[i]);
		if (new[i] == NULL) {
			for(i--; i >= 0; i--) {
				nacm_rule_list_free(new[i]);
			}
			return (NULL);
		}
	}
	new[i] = NULL; /* list terminating NULL byte */

	return (new);
}

static void nacm_check_data_read_recursion(xmlNodePtr subtree, const struct nacm_rpc* nacm, struct ncds_ds* sysrepo_ds)
{
	xmlNodePtr node, next;

	if (nacm_check_data_sysrepo(subtree, NACM_ACCESS_READ, nacm, sysrepo_ds) == NACM_DENY) {
		xmlUnlinkNode(subtree);
		xmlFreeNode(subtree);
	} else {
		for (node = subtree->children; node != NULL; node = next) {
			next = node->next;
			if (node->type == XML_ELEMENT_NODE) {
				nacm_check_data_read_recursion(node, nacm, sysrepo_ds);
			}
		}
	}
}

int nacm_check_data_read_sysrepo(xmlDocPtr doc, const struct nacm_rpc* nacm, struct ncds_ds* sysrepo_ds)
{
	xmlNodePtr node, next;

	if (doc == NULL) {
		return (EXIT_FAILURE);
	}

	if (nacm == NULL) {
		return (EXIT_SUCCESS);
	}

	for (node = doc->children; node != NULL; node = next) {
		next = node->next;
		if (node->type == XML_ELEMENT_NODE) {
			nacm_check_data_read_recursion(node, nacm, sysrepo_ds);
		}
	}

	return (EXIT_SUCCESS);
}

/*
 * return 0 as false (nodes are not equivalent), 1 as true (model_node defines
 * node in model)
 */
static int compare_node_to_model(const xmlNodePtr node, const xmlNodePtr model_node, const char* model_namespace)
{
	xmlChar* name;
	xmlNodePtr model_parent;

	/* \todo Add support for augment models */

	if ((name = xmlGetProp (model_node, BAD_CAST "name")) == NULL) {
		return (0);
	}

	if (xmlStrcmp(node->name, name) != 0) {
		xmlFree(name);
		return (0);
	}
	xmlFree(name);

	if (node->ns == NULL || node->ns->href == NULL ||
	    xmlStrcmp(node->ns->href, BAD_CAST model_namespace) != 0) {
		return (0);
	}

	/* check namespace */
	if (node->parent->type == XML_DOCUMENT_NODE) {
		/* we are in the root */
		if (xmlStrcmp(model_node->parent->name, BAD_CAST "module")) {
			/* also in model we are on the top */
			return (1);
		} else {
			/* there is something left in model */
			return (0);
		}
	} else {
		/* do recursion */
		model_parent = model_node->parent;
		while ((model_parent != NULL) && (model_parent->type == XML_ELEMENT_NODE) &&
		    (xmlStrcmp(model_parent->name, BAD_CAST "choice") == 0 ||
		    xmlStrcmp(model_parent->name, BAD_CAST "case") == 0 ||
		    xmlStrcmp(model_parent->name, BAD_CAST "augment") == 0)) {
			model_parent = model_parent->parent;
		}
		return (compare_node_to_model(node->parent, model_parent, model_namespace));
	}
}

int nacm_check_data_sysrepo(const xmlNodePtr node, const int access, const struct nacm_rpc* nacm, struct ncds_ds* sysrepo_ds)
{
	xmlXPathObjectPtr defdeny;
	xmlXPathContextPtr model_ctxt = NULL;
	xmlXPathContextPtr ctxt = NULL;
	xmlXPathObjectPtr xpath_result = NULL;
	struct nacm_ns *ns;
	struct nacm_rule* rule;
	const struct data_model* module = NULL;
	int i, j, k;
	int retval = -1;

	if (access == 0 || node == NULL || node->doc == NULL) {
		/* invalid input parameter */
		return (-1);
	}

	if (nacm == NULL) {
		/* NACM will not affect this request */
		return (NACM_PERMIT);
	}

	if (node->type != XML_ELEMENT_NODE) {
		/* skip comments or other elements not covered by NACM rules */
		return (NACM_PERMIT);
	}

	/* get module name where the data node is defined */
	if (node->ns != NULL) {
		module = sysrepo_ds->data_model;
		if (strcmp(module->ns, (char*)(node->ns->href)) != 0) {
			module = NULL;
		}
	}

	if (module != NULL) {
		for (i = 0; nacm->rule_lists != NULL && nacm->rule_lists[i] != NULL; i++) {
			for (j = 0; nacm->rule_lists[i]->rules != NULL && nacm->rule_lists[i]->rules[j] != NULL; j++) {
				/*
				 * check rules (all must be met):
				 * - module-name matches "*" or the name of the module where the data node is defined
				 * - type is NACM_RULE_NOTSET or type is NACM_RULE_DATA and data contain "*" or the operation name
				 * - access has set NACM_ACCESS_EXEC bit
				 */
				rule = nacm->rule_lists[i]->rules[j]; /* shortcut */

				/* 1) module name */
				if (!(strcmp(rule->module, "*") == 0 ||
				    strcmp(rule->module, module->name) == 0)) {
					/* rule does not match */
					continue;
				}

				/* 3) access - do it before 2 for optimize, the 2nd step is the most difficult */
				if ((rule->access & access) == 0) {
					/* rule does not match */
					continue;
				}

				/* 2) type and operation name */
				if (rule->type != NACM_RULE_NOTSET) {
					if (rule->type == NACM_RULE_DATA &&
					    rule->type_data.path != NULL) {
						/* create xPath context for search in node's document */
						if ((ctxt = xmlXPathNewContext(node->doc)) == NULL) {
							nc_verb_error("%s: Creating XPath context failed.", __func__);
							return (-1);
						}

						/* register namespaces from the rule's path */
						for (ns = rule->type_data.path->ns_list; ns != NULL; ns = ns->next) {
							if (xmlXPathRegisterNs(ctxt, BAD_CAST ns->prefix, BAD_CAST ns->href) != 0) {
								nc_verb_error("Registering NACM rule path namespace for the xpath context failed.");
								xmlXPathFreeContext(ctxt);
								return (-1);
							}
						}

						/* query the rule's path in the node's document and compare results with the node */
						if ((xpath_result = xmlXPathEvalExpression(BAD_CAST rule->type_data.path->path, ctxt)) != NULL) {
							if (xmlXPathNodeSetIsEmpty(xpath_result->nodesetval)) {
								/* rule does not match - path does not exist in document */
								xmlXPathFreeObject(xpath_result);
								xmlXPathFreeContext(ctxt);
								continue;
							}
							for (k = 0; k < xpath_result->nodesetval->nodeNr; k++) {
								if (node == xpath_result->nodesetval->nodeTab[k]) {
									/* the path selects the node */
									break;
								}
							}

							if (k == xpath_result->nodesetval->nodeNr) {
								/* rule does not match */
								xmlXPathFreeObject(xpath_result);
								xmlXPathFreeContext(ctxt);
								continue;
							}

							xmlXPathFreeObject(xpath_result);
						} else {
							nc_verb_warning("%s: Unable to evaluate path \"%s\"", __func__, rule->type_data.path->path);
						}

						/* cleanup */
						xmlXPathFreeContext(ctxt);
					} else {
						/* rule does not match - another type of rule */
						continue;
					}
				}

				/* rule matches */
				retval = rule->action;
				goto result;
			}
		}
		/* no matching rule found */

		/* check nacm:default-deny-all and nacm:default-deny-write */
		if ((model_ctxt = xmlXPathNewContext(module->xml)) != NULL &&
		    xmlXPathRegisterNs(model_ctxt, BAD_CAST "yin", BAD_CAST NC_NS_YIN) == 0 &&
		    xmlXPathRegisterNs(model_ctxt, BAD_CAST "nacm", BAD_CAST NC_NS_NACM) == 0) {
			if ((defdeny = xmlXPathEvalExpression(BAD_CAST "/yin:module//nacm:default-deny-all", model_ctxt)) != NULL) {
				if (!xmlXPathNodeSetIsEmpty(defdeny->nodesetval)) {
					/* process all default-deny-all elements */
					for (i = 0; i < defdeny->nodesetval->nodeNr; i++) {
						if (compare_node_to_model(node, defdeny->nodesetval->nodeTab[i]->parent, module->ns) == 1) {
							xmlXPathFreeObject(defdeny);
							xmlXPathFreeContext(model_ctxt);
							retval = NACM_DENY;
							goto result;
						}
					}
				}
				xmlXPathFreeObject(defdeny);
			}
			if ((access & (NACM_ACCESS_CREATE | NACM_ACCESS_DELETE | NACM_ACCESS_UPDATE)) != 0) {
				/* check default-deny-write */
				if ((defdeny = xmlXPathEvalExpression(BAD_CAST "/yin:module//nacm:default-deny-write", model_ctxt)) != NULL ) {
					if (!xmlXPathNodeSetIsEmpty(defdeny->nodesetval)) {
						/* process all default-deny-all elements */
						for (i = 0; i < defdeny->nodesetval->nodeNr; i++) {
							if (compare_node_to_model(node, defdeny->nodesetval->nodeTab[i]->parent, module->ns) == 1) {
								xmlXPathFreeObject(defdeny);
								xmlXPathFreeContext(model_ctxt);
								retval = NACM_DENY;
								goto result;
							}
						}
					}
					xmlXPathFreeObject(defdeny);
				}
			}
		}
		xmlXPathFreeContext(model_ctxt);
	}
	/* no matching rule found */

	/* default action */
	if ((access & NACM_ACCESS_READ) != 0) {
		retval = nacm->default_read;
		goto result;
	}
	if ((access & (NACM_ACCESS_CREATE | NACM_ACCESS_DELETE | NACM_ACCESS_UPDATE)) != 0) {
		retval = nacm->default_write;
		goto result;
	}

	/* unknown access request - deny */
	retval = NACM_DENY;

result:
	/* update stats */
	if (retval == NACM_DENY && nc_info) {
		pthread_rwlock_wrlock(&(nc_info->lock));
		nc_info->stats_nacm.denied_data++;
		pthread_rwlock_unlock(&(nc_info->lock));
	}

	return (retval);
}
