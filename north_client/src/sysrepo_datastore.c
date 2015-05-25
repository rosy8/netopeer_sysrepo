#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>

#include "srd.h"
#include "config.h"

int sysrepo_fd = -1;

/* local locks info */
/*struct {
    int running;
    char *running_sid;
    int startup;
    char *startup_sid;
    int cand;
    char *cand_sid;
} locks = {0, NULL, 0, NULL, 0, NULL};*/

/* localy maintained datastores */
/*xmlDocPtr gds_startup = NULL;
xmlDocPtr gds_cand = NULL;*/

int sysrepo_init(void* UNUSED(data)) {
	const char server_ip[] = "127.0.0.1";
	char* ds_list;

	if (srd_connect((char*)server_ip, SRD_DEFAULTSERVERPORT, &sysrepo_fd) != 1) {
		nc_verb_error("Failed to connect to sysrepo on %s:%d", server_ip, SRD_DEFAULTSERVERPORT);
		return EXIT_FAILURE;
	}

	if (!srd_listOpDataStores(sysrepo_fd, &ds_list)) {
		nc_verb_error("Failed to get sysrepo datastores");
		return EXIT_FAILURE;
	}

	if (strstr(ds_list, NP_SYSREPO_IFC_DS) == NULL) {
		nc_verb_error("Sysrepo does not have the ifc datastore created");
		return EXIT_FAILURE;
	}
	free(ds_list);

	return EXIT_SUCCESS;
}

void sysrepo_free(void* UNUSED(data)) {
	/*if (srd_stopUsingOpDataStore(sysrepo_fd, NP_SYSREPO_IFC_DS) != 1) {
		nc_verb_error("Failed to stop using %s datastore", NP_SYSREPO_IFC_DS);
	}*/

    if (sysrepo_fd != -1) {
		char msg[50];
		sprintf(msg, "<xml><command>disconnect</command></xml>");
		if (!srd_sendServer(sysrepo_fd, msg, strlen(msg))) {
			nc_verb_error("%s: Error in sending msg: %s", __func__, msg);
		}
		if (!srd_isServerResponseOK(sysrepo_fd, NULL)) {
			nc_verb_error("%s: Server response to disconnect is not OK.", __func__);
		}
		close(sysrepo_fd);
		sysrepo_fd = -1;
	}
}

static void store_rollback(const xmlDocPtr doc, NC_DATASTORE type) {
	/* TODO */
    /*if (rollback.doc) {
        xmlFreeDoc(rollback.doc);
    }

    rollback.doc = doc;
    rollback.type = type;*/
}

int sysrepo_changed(void* UNUSED(data)) {
	/* TODO */
    /* always false the function is not needed now, we can implement it later
     * for internal purposes, but for now the datastore content is synced
     * continuously */
    return (0);
}

int sysrepo_lock(void* UNUSED(data), NC_DATASTORE target, const char* session_id, struct nc_err** error) {
	/* TODO not operational DS */
	/*if (srd_lockDataStore(sysrepo_fd) != 1) {
		nc_verb_error("Failed to lock sysrepo datastore");
		return EXIT_FAILURE;
	}*/

	return EXIT_SUCCESS;
}

int sysrepo_unlock(void* UNUSED(data), NC_DATASTORE target, const char* session_id, struct nc_err** error) {
	/* TODO not operational DS */
	/*if (src_unlockDataStore(sysrepo_fd) != 1) {
		nc_verb_error("Failed to unlock sysrepo datastore");
		return EXIT_FAILURE;
	}*/

	return EXIT_SUCCESS;
}

char* sysrepo_getconfig(void* UNUSED(data), NC_DATASTORE target, struct nc_err** error) {
    char *config_data = NULL;

    switch (target) {
    case NC_DATASTORE_RUNNING:
        srd_applyXPathOpDataStore(sysrepo_fd, NP_SYSREPO_IFC_DS, "/*/*[local-name()='interfaces']", &config_data);
		break;
    case NC_DATASTORE_STARTUP:
		/* TODO */
        /*if (!gds_startup) {
            config_data = xmlStrdup(BAD_CAST "");
        } else {
            xmlDocDumpMemory(gds_startup, &config_data, NULL);
        }
        break;*/
    case NC_DATASTORE_CANDIDATE:
		/* TODO */
        /*if (!gds_cand) {
            config_data = xmlStrdup(BAD_CAST "");
        } else {
            xmlDocDumpMemory(gds_cand, &config_data, NULL);
        }
        break;*/
    default:
        nc_verb_error("Invalid <get-config> source.");
        *error = nc_err_new(NC_ERR_BAD_ELEM);
        nc_err_set(*error, NC_ERR_PARAM_INFO_BADELEM, "source");
    }

    return config_data;
}

int sysrepo_deleteconfig(void *UNUSED(data), NC_DATASTORE target, struct nc_err **error) {
	/* TODO */
    /*switch (target) {
    case NC_DATASTORE_RUNNING:
        *error = nc_err_new(NC_ERR_OP_FAILED);
        nc_err_set(*error, NC_ERR_PARAM_MSG,
                   "Cannot delete a running datastore.");
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
    }*/

    return EXIT_SUCCESS;
}

int sysrepo_editconfig(void* UNUSED(data), const nc_rpc* UNUSED(rpc), NC_DATASTORE target, const char* config, NC_EDIT_DEFOP_TYPE defop, NC_EDIT_ERROPT_TYPE UNUSED(errop), struct nc_err** error) {
	/* TODO */
//     int ret = EXIT_FAILURE, running = 0;
//     char *aux;
//     int cfgds_new = 0;
//     xmlDocPtr cfgds = NULL, cfg = NULL, cfg_clone = NULL;
//     xmlNodePtr rootcfg;
//
//     if (defop == NC_EDIT_DEFOP_NOTSET) {
//         defop = NC_EDIT_DEFOP_MERGE;
//     }
//
//     cfg = xmlReadMemory(config, strlen(config), NULL, NULL, XML_READ_OPT);
//     rootcfg = xmlDocGetRootElement(cfg);
//     if (!cfg
//         || (rootcfg
//             && !xmlStrEqual(rootcfg->name, BAD_CAST "capable-switch"))) {
//         nc_verb_error("Invalid <edit-config> configuration data.");
//         *error = nc_err_new(NC_ERR_BAD_ELEM);
//         nc_err_set(*error, NC_ERR_PARAM_INFO_BADELEM, "config");
//         return EXIT_FAILURE;
//     }
//
//     switch (target) {
//     case NC_DATASTORE_RUNNING:
//         /* Make a copy of parsed config - we will find port/configuration in
//          * it.  It is used after txn_commit(). */
//         cfg_clone = xmlCopyDoc(cfg, 1);
//
//         aux = ofc_get_config_data();
//         if (!aux) {
//             *error = nc_err_new(NC_ERR_OP_FAILED);
//             goto error_cleanup;
//         }
//         cfgds = xmlReadMemory(aux, strlen(aux), NULL, NULL, XML_READ_OPT);
//         free(aux);
//
//         running = 1;
//         break;
//     case NC_DATASTORE_STARTUP:
//         cfgds = gds_startup;
//         break;
//     case NC_DATASTORE_CANDIDATE:
//         cfgds = gds_cand;
//         break;
//     default:
//         nc_verb_error("Invalid <edit-config> target.");
//         *error = nc_err_new(NC_ERR_BAD_ELEM);
//         nc_err_set(*error, NC_ERR_PARAM_INFO_BADELEM, "target");
//         goto error_cleanup;
//     }
//     store_rollback(xmlCopyDoc(cfgds, 1), target);
//
//     /* check keys in config's lists */
//     ret = check_keys(cfg, error);
//     if (ret != EXIT_SUCCESS) {
//         goto error_cleanup;
//     }
//
//     /* check operations */
//     ret = check_edit_ops(NC_EDIT_OP_DELETE, defop, cfgds, cfg, error);
//     if (ret != EXIT_SUCCESS) {
//         goto error_cleanup;
//     }
//     ret = check_edit_ops(NC_EDIT_OP_CREATE, defop, cfgds, cfg, error);
//     if (ret != EXIT_SUCCESS) {
//         goto error_cleanup;
//     }
//
//     if (target == NC_DATASTORE_RUNNING) {
//         txn_init();
//     }
//
//     ret = compact_edit_operations(cfg, defop);
//     if (ret != EXIT_SUCCESS) {
//         nc_verb_error("Compacting edit-config operations failed.");
//         if (error != NULL) {
//             *error = nc_err_new(NC_ERR_OP_FAILED);
//         }
//         goto error_cleanup;
//     }
//
//     /* perform operations */
//     if (!cfgds) {
//         cfgds_new = 1;
//         cfgds = xmlNewDoc(BAD_CAST "1.0");
//     }
//     ret = edit_operations(cfgds, cfg, defop, running, error);
//     if (ret != EXIT_SUCCESS) {
//         goto error_cleanup;
//     }
//
//     /* with defaults capability */
//     if (ncdflt_get_basic_mode() == NCWD_MODE_TRIM) {
//         /* server work in trim basic mode and therefore all default values
//          * must be removed from the datastore. */
//         /* TODO */
//     }
//
//     if (target == NC_DATASTORE_RUNNING) {
//         ret = txn_commit(error);
//
//         if (ret == EXIT_SUCCESS) {
//             /* modify port/configuration of ports that were created */
//             ret = of_post_ports(xmlDocGetRootElement(cfg_clone), error);
//         }
//         /* config clone was used and it is not needed by now */
//         xmlFreeDoc(cfg_clone);
//
//         xmlFreeDoc(cfgds);
//     } else if (cfgds_new){
//         if (cfgds->children) {
//             /* document changed, because we started with empty document */
//             if (target == NC_DATASTORE_STARTUP) {
//                 gds_startup = cfgds;
//                 cfgds = NULL;
//             } else if (target == NC_DATASTORE_CANDIDATE) {
//                 gds_cand = cfgds;
//                 cfgds = NULL;
//             }
//         }
//         xmlFreeDoc(cfgds);
//     }
//     xmlFreeDoc(cfg);
//
//     return ret;
//
// error_cleanup:
//
//     if (target == NC_DATASTORE_RUNNING) {
//         txn_abort();
//         xmlFreeDoc(cfg_clone);
//         xmlFreeDoc(cfgds);
//     }
//     xmlFreeDoc(cfg);
//
//     return ret;
	return EXIT_SUCCESS;
}

int sysrepo_copyconfig(void *UNUSED(data), NC_DATASTORE target, NC_DATASTORE source, char *config, struct nc_err **error) {
	/* TODO */
// 	int ret = EXIT_FAILURE;
//     char *s;
//     xmlDocPtr src_doc = NULL;
//     xmlDocPtr dst_doc = NULL;
//     xmlNodePtr root;
//     static const char *ds[] = {"error", "<config>", "URL", "running",
//                                "startup", "candidate"};
//
//     nc_verb_verbose("OFC COPY-CONFIG (from %s to %s)", ds[source], ds[target]);
//
//     switch (source) {
//     case NC_DATASTORE_RUNNING:
//         s = sysrepo_getconfig(NULL, NC_DATASTORE_RUNNING, error);
//         if (!s) {
//             nc_verb_error
//                 ("copy-config: unable to get running source repository");
//             return EXIT_FAILURE;
//         }
//         src_doc = xmlReadMemory(s, strlen(s), NULL, NULL, XML_READ_OPT);
//         free(s);
//         if (!src_doc) {
//             nc_verb_error("copy-config: invalid running source data");
//             *error = nc_err_new(NC_ERR_OP_FAILED);
//             nc_err_set(*error, NC_ERR_PARAM_INFO_BADELEM,
//                        "invalid running source data");
//             return EXIT_FAILURE;
//         }
//         break;
//     case NC_DATASTORE_STARTUP:
//         src_doc = xmlCopyDoc(gds_startup, 1);
//         break;
//     case NC_DATASTORE_CANDIDATE:
//         src_doc = xmlCopyDoc(gds_cand, 1);
//         break;
//     case NC_DATASTORE_CONFIG:
//         if (config && strlen(config) > 0) {
//             src_doc = xmlReadMemory(config, strlen(config), NULL, NULL,
//                                     XML_READ_OPT);
//         }
//         if (!config || (strlen(config) > 0 && !src_doc)) {
//             nc_verb_error("Invalid source configuration data.");
//             *error = nc_err_new(NC_ERR_BAD_ELEM);
//             nc_err_set(*error, NC_ERR_PARAM_INFO_BADELEM, "config");
//             return EXIT_FAILURE;
//         }
//
//         break;
//     default:
//         nc_verb_error("Invalid <get-config> source.");
//         *error = nc_err_new(NC_ERR_BAD_ELEM);
//         nc_err_set(*error, NC_ERR_PARAM_INFO_BADELEM, "source");
//         return EXIT_FAILURE;
//     }
//
//     switch (target) {
//     case NC_DATASTORE_RUNNING:
//         /* apply source to OVSDB */
//
//         s = sysrepo_getconfig(NULL, NC_DATASTORE_RUNNING, error);
//         if (!s) {
//             nc_verb_error("copy-config: unable to get running source data");
//             goto cleanup;
//         }
//         dst_doc = xmlReadMemory(s, strlen(s), NULL, NULL, XML_READ_OPT);
//         free(s);
//
//         root = xmlDocGetRootElement(src_doc);
//         if (!dst_doc) {
//             /* create envelope */
//             dst_doc = xmlNewDoc(BAD_CAST "1.0");
//         }
//         if (!rollbacking) {
//             store_rollback(xmlCopyDoc(dst_doc, 1), target);
//         }
//
//         txn_init();
//         if (edit_replace(dst_doc, root, 1, error)) {
//             txn_abort();
//         } else {
//             ret = txn_commit(error);
//         }
//         xmlFreeDoc(dst_doc);
//         goto cleanup;
//         break;
//     case NC_DATASTORE_STARTUP:
//     case NC_DATASTORE_CANDIDATE:
//         /* create copy */
//         if (src_doc) {
//             dst_doc = src_doc;
//             src_doc = NULL;
//         }
//
//         /* store the copy */
//         if (target == NC_DATASTORE_STARTUP) {
//             if (!rollbacking) {
//                 store_rollback(gds_startup, target);
//             } else {
//                 xmlFreeDoc(gds_startup);
//             }
//             gds_startup = dst_doc;
//         } else {                /* NC_DATASTORE_CANDIDATE */
//             if (!rollbacking) {
//                 store_rollback(gds_cand, target);
//             } else {
//                 xmlFreeDoc(gds_cand);
//             }
//             gds_cand = dst_doc;
//         }
//
//         break;
//     default:
//         nc_verb_error("Invalid <get-config> source.");
//         *error = nc_err_new(NC_ERR_BAD_ELEM);
//         nc_err_set(*error, NC_ERR_PARAM_INFO_BADELEM, "source");
//         goto cleanup;
//     }
//
//     ret = EXIT_SUCCESS;
//
// cleanup:
//     xmlFreeDoc(src_doc);
//
//     return ret;
	return EXIT_SUCCESS;
}

int sysrepo_rollback(void* UNUSED(data)) {
	/* TODO */
//     xmlChar *data;
//     int size, ret;
//     struct nc_err *e;
//
//     if (rollback.type == NC_DATASTORE_ERROR) {
//         nc_verb_error("No data to rollback");
//         return EXIT_FAILURE;
//     }
//
//     /* dump data for copy-config */
//     if (rollback.doc) {
//         xmlDocDumpMemory(rollback.doc, &data, &size);
//     } else {
//         data = xmlStrdup(BAD_CAST "");
//     }
//     rollbacking = 1;
//     ret = sysrepo_copyconfig(NULL, rollback.type, NC_DATASTORE_CONFIG,
//                            (char *) data, &e);
//     rollbacking = 0;
//
//     if (ret) {
//         nc_err_free(e);
//     }
//     xmlFree(data);
//
//     return ret;
	return EXIT_SUCCESS;
}

struct ncds_custom_funcs sysrepo_funcs = {
    .init = sysrepo_init,
    .free = sysrepo_free,
    .was_changed = sysrepo_changed,
    .rollback = sysrepo_rollback,
    .lock = sysrepo_lock,
    .unlock = sysrepo_unlock,
    .is_locked = NULL,
    .getconfig = sysrepo_getconfig,
    .copyconfig = sysrepo_copyconfig,
    .deleteconfig = sysrepo_deleteconfig,
    .editconfig = sysrepo_editconfig
};
