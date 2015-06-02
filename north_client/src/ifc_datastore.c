#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>
#include <errno.h>

#include <libnetconf.h>
#include <srd.h>

#include "libnetconf/edit_config.h"
#include "config.h"

#define XML_READ_OPT XML_PARSE_NOBLANKS|XML_PARSE_NSCLEAN

extern int sysrepo_fd;
extern struct ncds_ds* ifc_ds;

/* The last valid running for rollback */
struct rollback_s {
    xmlDocPtr doc;
    NC_DATASTORE type;
};
static struct rollback_s rollback = { NULL, NC_DATASTORE_ERROR };

static int rollbacking = 0;
static int internal_getconfig = 0;

/* local locks info */
static struct {
    int running;
    char *running_sid;
    int startup;
    char *startup_sid;
    int cand;
    char *cand_sid;
} locks = {0, NULL, 0, NULL, 0, NULL};

/* localy maintained datastores */
static xmlDocPtr gds_run = NULL;
static xmlDocPtr gds_startup = NULL;
static xmlDocPtr gds_cand = NULL;

char* ifc_getconfig(void* UNUSED(data), NC_DATASTORE target, struct nc_err** error);

int ifc_init(void* UNUSED(data)) {
	char* ds_list, *aux;

	if (sysrepo_fd == -1) {
		nc_verb_error("Netopeer must be connected to sysrepod");
		return EXIT_FAILURE;
	}

	if (!srd_listOpDataStores(sysrepo_fd, &ds_list)) {
		nc_verb_error("Failed to get sysrepo datastores");
		return EXIT_FAILURE;
	}

	if (strstr(ds_list, NP_SYSREPO_IFC_DS "/interfaces-state") == NULL) {
		nc_verb_error("Sysrepo does not have the ifc operational datastore created");
		free(ds_list);
		return EXIT_FAILURE;
	}
	free(ds_list);

	if (!srd_listDataStores(sysrepo_fd, &ds_list)) {
		nc_verb_error("Failed to get sysrepo datastores");
		return EXIT_FAILURE;
	}

	if (strstr(ds_list, NP_SYSREPO_IFC_DS "/interfaces") == NULL) {
		nc_verb_error("Sysrepo does not have the ifc datastore created");
		free(ds_list);
		return EXIT_FAILURE;
	}
	free(ds_list);

	if (!srd_setDataStore(sysrepo_fd, NP_SYSREPO_IFC_DS "/interfaces")) {
		nc_verb_error("Cannot use sysrepo datastore");
		return EXIT_FAILURE;
	}

	aux = ifc_getconfig(NULL, NC_DATASTORE_RUNNING, NULL);
	if (!aux) {
		nc_verb_error("Failed to get sysrepo ifc data.");
		return EXIT_FAILURE;
	}
	gds_cand = xmlReadMemory(aux, strlen(aux), NULL, NULL, XML_READ_OPT);
	free(aux);

	if (eaccess(CFG_DIR "/sysrepo_ifc/startup.xml", R_OK) != -1) {
		gds_startup = xmlReadFile(CFG_DIR "/sysrepo_ifc/startup.xml", NULL, XML_READ_OPT);
		if (gds_startup == NULL) {
			nc_verb_warning("Could not parse sysrepo ifc startup config.");
		}
	}

	if (gds_startup == NULL) {
		gds_startup = xmlCopyDoc(gds_cand, 1);
	}

	return EXIT_SUCCESS;
}

void ifc_free(void* UNUSED(data)) {
	FILE* startup_file;

	startup_file = fopen(CFG_DIR "/sysrepo_ifc/startup.xml", "w");
	if (startup_file == NULL) {
		nc_verb_warning("Failed to store startup config (%s).", strerror(errno));
	} else {
		if (xmlDocFormatDump(startup_file, gds_startup, 1) == -1) {
			nc_verb_warning("Failed to dump startup config doc.");
		}
		fclose(startup_file);
	}

	xmlFreeDoc(rollback.doc);
	rollback.doc = NULL;

	xmlFreeDoc(gds_run);
	xmlFreeDoc(gds_startup);
	xmlFreeDoc(gds_cand);
}

static void store_rollback(const xmlDocPtr doc, NC_DATASTORE type) {
    if (rollback.doc) {
        xmlFreeDoc(rollback.doc);
    }

    rollback.doc = doc;
    rollback.type = type;
}

int ifc_changed(void* UNUSED(data)) {
	/* always false the function is not needed now, we can implement it later
	 * for internal purposes, but for now the datastore content is synced
	 * continuously */
	return 0;
}

int ifc_lock(void* UNUSED(data), NC_DATASTORE target, const char* session_id, struct nc_err** error) {
	int* locked;
	char** sid;

	switch (target) {
	case NC_DATASTORE_RUNNING:
		if (!srd_lockDataStore(sysrepo_fd)) {
			nc_verb_error("Failed to lock datastore.");
			return EXIT_FAILURE;
		}
		locked = &(locks.running);
		sid = &(locks.running_sid);
		break;
	case NC_DATASTORE_STARTUP:
		locked = &(locks.startup);
		sid = &(locks.startup_sid);
		break;
	case NC_DATASTORE_CANDIDATE:
		locked = &(locks.cand);
		sid = &(locks.cand_sid);
		break;
	default:
		/* handled by libnetconf */
		return EXIT_FAILURE;
	}

	if (*locked) {
		/* datastore is already locked */
		*error = nc_err_new(NC_ERR_LOCK_DENIED);
		nc_err_set(*error, NC_ERR_PARAM_INFO_SID, *sid);
		return EXIT_FAILURE;
	} else {
		/* remember the lock */
		*locked = 1;
		*sid = strdup(session_id);
		nc_verb_verbose("Sysrepo ifc datastore %d locked by %s.", target, session_id);
	}

	return EXIT_SUCCESS;
}

int ifc_unlock(void* UNUSED(data), NC_DATASTORE target, const char* session_id, struct nc_err** error) {
	int* locked;
	char** sid;

	switch (target) {
	case NC_DATASTORE_RUNNING:
		if (!srd_unlockDataStore(sysrepo_fd)) {
			nc_verb_error("Failed to unlock datastore.");
			return EXIT_FAILURE;
		}
		locked = &(locks.running);
		sid = &(locks.running_sid);
		break;
	case NC_DATASTORE_STARTUP:
		locked = &(locks.startup);
		sid = &(locks.startup_sid);
		break;
	case NC_DATASTORE_CANDIDATE:
		locked = &(locks.cand);
		sid = &(locks.cand_sid);
		break;
	default:
		/* handled by libnetconf */
		return EXIT_FAILURE;
	}

	if (*locked) {
		if (strcmp(*sid, session_id) == 0) {
			/* correct request, unlock */
			*locked = 0;
			free(*sid);
			*sid = NULL;
			nc_verb_verbose("Sysrepo ifc datastore %d unlocked by %s.", target, session_id);
		} else {
			/* locked by another session */
			*error = nc_err_new(NC_ERR_LOCK_DENIED);
			nc_err_set(*error, NC_ERR_PARAM_INFO_SID, *sid);
			nc_err_set(*error, NC_ERR_PARAM_MSG, "Target datastore is locked by another session.");
			return EXIT_FAILURE;
		}
	} else {
		/* not locked */
		*error = nc_err_new(NC_ERR_OP_FAILED);
		nc_err_set(*error, NC_ERR_PARAM_MSG, "Target datastore is not locked.");
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

char* ifc_getconfig(void* UNUSED(data), NC_DATASTORE target, struct nc_err** error) {
	xmlChar* config_data = NULL;

	switch (target) {
	case NC_DATASTORE_RUNNING:
		if (internal_getconfig) {
			xmlDocDumpMemory(gds_run, &config_data, NULL);
			--internal_getconfig;
		} else {
			srd_applyXPath(sysrepo_fd, "/*[local-name()='data']/*[local-name()='interfaces']", (char**)&config_data);
		}
		break;
	case NC_DATASTORE_STARTUP:
		if (!gds_startup) {
			config_data = xmlStrdup(BAD_CAST "");
		} else {
			xmlDocDumpMemory(gds_startup, &config_data, NULL);
		}
		break;
	case NC_DATASTORE_CANDIDATE:
		if (!gds_cand) {
			config_data = xmlStrdup(BAD_CAST "");
		} else {
			xmlDocDumpMemory(gds_cand, &config_data, NULL);
		}
		break;
	default:
		nc_verb_error("Invalid <get-config> source.");
		*error = nc_err_new(NC_ERR_BAD_ELEM);
		nc_err_set(*error, NC_ERR_PARAM_INFO_BADELEM, "source");
	}

	return (char*)config_data;
}

int ifc_deleteconfig(void *UNUSED(data), NC_DATASTORE target, struct nc_err **error) {
	switch (target) {
	case NC_DATASTORE_RUNNING:
		*error = nc_err_new(NC_ERR_OP_FAILED);
		nc_err_set(*error, NC_ERR_PARAM_MSG, "Cannot delete the running datastore.");
		return EXIT_FAILURE;
	case NC_DATASTORE_STARTUP:
		store_rollback(gds_startup, NC_DATASTORE_STARTUP);
		gds_startup = NULL;
		break;
	case NC_DATASTORE_CANDIDATE:
		store_rollback(gds_cand, NC_DATASTORE_CANDIDATE);
		gds_cand = NULL;
		break;
	default:
		nc_verb_error("Invalid <delete-config> target.");
		*error = nc_err_new(NC_ERR_BAD_ELEM);
		nc_err_set(*error, NC_ERR_PARAM_INFO_BADELEM, "target");
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

int ifc_editconfig(void* UNUSED(data), const nc_rpc* rpc, NC_DATASTORE target, const char* config, NC_EDIT_DEFOP_TYPE defop, NC_EDIT_ERROPT_TYPE errop, struct nc_err** error) {
	int ret = EXIT_FAILURE;
	char* aux;
	xmlDocPtr old_doc = NULL, new_doc = NULL;
	xmlNodePtr root;

	if (defop == NC_EDIT_DEFOP_NOTSET) {
		defop = NC_EDIT_DEFOP_MERGE;
	}

	new_doc = xmlReadMemory(config, strlen(config), NULL, NULL, XML_READ_OPT);
	root = xmlDocGetRootElement(new_doc);
	if (!new_doc || (root && !xmlStrEqual(root->name, BAD_CAST "interfaces"))) {
		nc_verb_error("Invalid <edit-config> configuration data.");
		*error = nc_err_new(NC_ERR_BAD_ELEM);
		nc_err_set(*error, NC_ERR_PARAM_INFO_BADELEM, "config");
		goto error_cleanup;
	}

	switch (target) {
	case NC_DATASTORE_RUNNING:
		aux = ifc_getconfig(NULL, NC_DATASTORE_RUNNING, error);
		if (!aux) {
			nc_verb_error("Failed to get sysrepo ifc data.");
			*error = nc_err_new(NC_ERR_OP_FAILED);
			nc_err_set(*error, NC_ERR_PARAM_MSG, "Sysrepo <get-config> failed");
			goto error_cleanup;
		}
		old_doc = xmlReadMemory(aux, strlen(aux), NULL, NULL, XML_READ_OPT);
		free(aux);
		break;
	case NC_DATASTORE_STARTUP:
		old_doc = gds_startup;
		break;
	case NC_DATASTORE_CANDIDATE:
		old_doc = gds_cand;
		break;
	default:
		nc_verb_error("Invalid <edit-config> target.");
		*error = nc_err_new(NC_ERR_BAD_ELEM);
		nc_err_set(*error, NC_ERR_PARAM_INFO_BADELEM, "target");
		goto error_cleanup;
	}
	store_rollback(xmlCopyDoc(old_doc, 1), target);

	if (edit_config(old_doc, new_doc, ifc_ds, defop, errop, (rpc != NULL ? rpc->nacm : NULL), ifc_ds, error) != EXIT_SUCCESS) {
		goto error_cleanup;
	}

	if (target == NC_DATASTORE_RUNNING) {
		xmlFreeDoc(gds_run);
		gds_run = old_doc;
		internal_getconfig = 2;
	}
	ret = EXIT_SUCCESS;

error_cleanup:
	xmlFreeDoc(new_doc);
	return ret;
}

int ifc_copyconfig(void* UNUSED(data), NC_DATASTORE target, NC_DATASTORE source, char* config, struct nc_err** error) {
	char* aux;
	xmlDocPtr src_doc = NULL;
	xmlDocPtr dst_doc = NULL;

	switch (source) {
	case NC_DATASTORE_RUNNING:
		aux = ifc_getconfig(NULL, NC_DATASTORE_RUNNING, error);
		if (!aux) {
			nc_verb_error("Failed to get sysrepo ifc data.");
			*error = nc_err_new(NC_ERR_OP_FAILED);
			nc_err_set(*error, NC_ERR_PARAM_MSG, "Sysrepo <get-config> failed");
			return EXIT_FAILURE;
		}
		src_doc = xmlReadMemory(aux, strlen(aux), NULL, NULL, XML_READ_OPT);
		free(aux);
		break;
	case NC_DATASTORE_STARTUP:
		src_doc = xmlCopyDoc(gds_startup, 1);
		break;
	case NC_DATASTORE_CANDIDATE:
		src_doc = xmlCopyDoc(gds_cand, 1);
		break;
	case NC_DATASTORE_CONFIG:
		if (config) {
			if (strlen(config) > 0) {
				src_doc = xmlReadMemory(config, strlen(config), NULL, NULL, XML_READ_OPT);
			} else {
				src_doc = xmlNewDoc(BAD_CAST "1.0");
			}
		}
		if (!config || !src_doc) {
			nc_verb_error("Invalid source configuration data.");
			*error = nc_err_new(NC_ERR_BAD_ELEM);
			nc_err_set(*error, NC_ERR_PARAM_INFO_BADELEM, "config");
			return EXIT_FAILURE;
		}

		break;
	default:
		nc_verb_error("Invalid <get-config> source.");
		*error = nc_err_new(NC_ERR_BAD_ELEM);
		nc_err_set(*error, NC_ERR_PARAM_INFO_BADELEM, "source");
		return EXIT_FAILURE;
	}

	switch (target) {
	case NC_DATASTORE_RUNNING:
		aux = ifc_getconfig(NULL, NC_DATASTORE_RUNNING, error);
		if (!aux) {
			nc_verb_error("Failed to get sysrepo ifc data.");
			*error = nc_err_new(NC_ERR_OP_FAILED);
			nc_err_set(*error, NC_ERR_PARAM_MSG, "Sysrepo <get-config> failed");
			return EXIT_FAILURE;
		}
		dst_doc = xmlReadMemory(aux, strlen(aux), NULL, NULL, XML_READ_OPT);
		free(aux);

		if (!dst_doc) {
			/* create envelope */
			dst_doc = xmlNewDoc(BAD_CAST "1.0");
		}
		if (!rollbacking) {
			store_rollback(dst_doc, target);
		} else {
			xmlFreeDoc(dst_doc);
		}

		xmlFreeDoc(gds_run);
		gds_run = src_doc;
		internal_getconfig = 1;
		break;
    case NC_DATASTORE_STARTUP:
		if (!rollbacking) {
			store_rollback(gds_startup, target);
		} else {
			xmlFreeDoc(gds_startup);
		}
		gds_startup = src_doc;
		break;
	case NC_DATASTORE_CANDIDATE:
		if (!rollbacking) {
			store_rollback(gds_cand, target);
		} else {
			xmlFreeDoc(gds_cand);
		}
		gds_cand = src_doc;
		break;
	default:
		nc_verb_error("Invalid <get-config> source.");
		*error = nc_err_new(NC_ERR_BAD_ELEM);
		nc_err_set(*error, NC_ERR_PARAM_INFO_BADELEM, "source");
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

int ifc_rollback(void* UNUSED(data)) {
	xmlChar *data;
	int size, ret;
	struct nc_err *e;

	if (rollback.type == NC_DATASTORE_ERROR) {
		nc_verb_error("No data to rollback");
		return EXIT_FAILURE;
	}

	/* dump data for copy-config */
	if (rollback.doc) {
		xmlDocDumpMemory(rollback.doc, &data, &size);
	} else {
		data = xmlStrdup(BAD_CAST "");
	}
	rollbacking = 1;
	ret = ifc_copyconfig(NULL, rollback.type, NC_DATASTORE_CONFIG, (char*)data, &e);
	rollbacking = 0;

	if (ret) {
		nc_err_free(e);
	}
	xmlFree(data);

	return ret;
}

struct ncds_custom_funcs ifc_funcs = {
    .init = ifc_init,
    .free = ifc_free,
    .was_changed = ifc_changed,
    .rollback = ifc_rollback,
    .lock = ifc_lock,
    .unlock = ifc_unlock,
    .is_locked = NULL,
    .getconfig = ifc_getconfig,
    .copyconfig = ifc_copyconfig,
    .deleteconfig = ifc_deleteconfig,
    .editconfig = ifc_editconfig
};
