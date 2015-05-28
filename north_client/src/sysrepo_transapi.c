/*
 * This is automatically generated callbacks file
 * It contains 3 parts: Configuration callbacks, RPC callbacks and state data callbacks.
 * Do NOT alter function signatures or any structures unless you know exactly what you are doing.
 */
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <libnetconf_xml.h>

#include "../../srd.h"
#include "config.h"

/* transAPI version which must be compatible with libnetconf */
//int transapi_version = 6;

/* Signal to libnetconf that configuration data were modified by any callback.
 * 0 - data not modified
 * 1 - data have been modified
 */
int sysrepo_config_modified = 0;

/*
 * Determines the callbacks order.
 * Set this variable before compilation and DO NOT modify it in runtime.
 * TRANSAPI_CLBCKS_LEAF_TO_ROOT (default)
 * TRANSAPI_CLBCKS_ROOT_TO_LEAF
 */
const TRANSAPI_CLBCKS_ORDER_TYPE sysrepo_callbacks_order = TRANSAPI_CLBCKS_ORDER_DEFAULT;

/* Do not modify or set! This variable is set by libnetconf to announce edit-config's error-option
Feel free to use it to distinguish module behavior for different error-option values.
 * Possible values:
 * NC_EDIT_ERROPT_STOP - Following callback after failure are not executed, all successful callbacks executed till
                         failure point must be applied to the device.
 * NC_EDIT_ERROPT_CONT - Failed callbacks are skipped, but all callbacks needed to apply configuration changes are executed
 * NC_EDIT_ERROPT_ROLLBACK - After failure, following callbacks are not executed, but previous successful callbacks are
                         executed again with previous configuration data to roll it back.
 */
NC_EDIT_ERROPT_TYPE sysrepo_erropt = NC_EDIT_ERROPT_NOTSET;

/* the connection to sysrepod */
extern int sysrepo_fd;

/**
 * @brief Initialize plugin after loaded and before any other functions are called.

 * This function should not apply any configuration data to the controlled device. If no
 * running is returned (it stays *NULL), complete startup configuration is consequently
 * applied via module callbacks. When a running configuration is returned, libnetconf
 * then applies (via module's callbacks) only the startup configuration data that
 * differ from the returned running configuration data.

 * Please note, that copying startup data to the running is performed only after the
 * libnetconf's system-wide close - see nc_close() function documentation for more
 * information.

 * @param[out] running	Current configuration of managed device.

 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
int sysrepo_transapi_init(xmlDocPtr* UNUSED(running)) {
	return EXIT_SUCCESS;
}

/**
 * @brief Free all resources allocated on plugin runtime and prepare plugin for removal.
 */
void sysrepo_transapi_close(void) {
}

/**
 * @brief Retrieve state data from device and return them as XML document
 *
 * @param model	Device data model. libxml2 xmlDocPtr.
 * @param running	Running datastore content. libxml2 xmlDocPtr.
 * @param[out] err  Double pointer to error structure. Fill error when some occurs.
 * @return State data as libxml2 xmlDocPtr or NULL in case of error.
 */
xmlDocPtr sysrepo_get_state_data(xmlDocPtr UNUSED(model), xmlDocPtr UNUSED(running), struct nc_err** err) {
	xmlDocPtr doc, state_doc;
	xmlNodePtr root, nodes;
	xmlNsPtr ns;
	char* state_data = NULL;

	if (sysrepo_fd == -1) {
		nc_verb_error("%s: invalid sysrepo socket", __func__);
		*err = nc_err_new(NC_ERR_OP_FAILED);
		nc_err_set(*err, NC_ERR_PARAM_MSG, "Invalid sysrepo socket.");
		return NULL;
	}

	srd_applyXPathOpDataStore(sysrepo_fd, NP_SYSREPO_IFC_DS, "/*/*[local-name()='interfaces-state']", &state_data);
	if (state_data == NULL) {
		nc_verb_error("%s: failed to get ifc state data from sysrepo", __func__);
		*err = nc_err_new(NC_ERR_OP_FAILED);
		nc_err_set(*err, NC_ERR_PARAM_MSG, "Failed to get state data from sysrepo.");
		return NULL;
	}

	state_doc = xmlParseMemory(state_data, strlen(state_data));
	if (state_doc == NULL) {
		nc_verb_error("%s: failed to parse sysrepo ifc state data", __func__);
		*err = nc_err_new(NC_ERR_OP_FAILED);
		nc_err_set(*err, NC_ERR_PARAM_MSG, "Invalid sysrepo state data retrieved.");
		return NULL;
	}
	free(state_data);

	nodes = xmlDocCopyNodeList(state_doc, state_doc->children);
	xmlFreeDoc(state_doc);

	doc = xmlNewDoc(BAD_CAST "1.0");
	root = xmlNewNode(NULL, BAD_CAST "interfaces-state");
	ns = xmlNewNs(root, BAD_CAST "urn:ietf:params:xml:ns:yang:ietf-interfaces", NULL);
	xmlSetNs(root, ns);
	xmlDocSetRootElement(doc, root);

	xmlAddChildList(root, nodes);

	return doc;
}
/*
 * Mapping prefixes with namespaces.
 * Do NOT modify this structure!
 */
struct ns_pair sysrepo_namespace_mapping[] = {
	{"if", "urn:ietf:params:xml:ns:yang:ietf-interfaces"},
	{NULL, NULL}
};

/*
* CONFIGURATION callbacks
* Here follows set of callback functions run every time some change in associated part of running datastore occurs.
* You can safely modify the bodies of all function as well as add new functions for better lucidity of code.
*/

int callback_if_interfaces(void** UNUSED(data), XMLDIFF_OP op, xmlNodePtr UNUSED(old_node), xmlNodePtr new_node, struct nc_err** error) {
	return EXIT_SUCCESS;
}

int callback_if_interfaces_if_interface(void** UNUSED(data), XMLDIFF_OP op, xmlNodePtr UNUSED(old_node), xmlNodePtr new_node, struct nc_err** error) {
	return EXIT_SUCCESS;
}

int callback_if_interfaces_if_interface_if_name(void** UNUSED(data), XMLDIFF_OP op, xmlNodePtr UNUSED(old_node), xmlNodePtr new_node, struct nc_err** error) {
	return EXIT_SUCCESS;
}

int callback_if_interfaces_if_interface_if_description(void** UNUSED(data), XMLDIFF_OP op, xmlNodePtr UNUSED(old_node), xmlNodePtr new_node, struct nc_err** error) {
	return EXIT_SUCCESS;
}

int callback_if_interfaces_if_interface_if_type(void** UNUSED(data), XMLDIFF_OP op, xmlNodePtr UNUSED(old_node), xmlNodePtr new_node, struct nc_err** error) {
	return EXIT_SUCCESS;
}

int callback_if_interfaces_if_interface_if_enabled(void** UNUSED(data), XMLDIFF_OP op, xmlNodePtr UNUSED(old_node), xmlNodePtr new_node, struct nc_err** error) {
	return EXIT_SUCCESS;
}

int callback_if_interfaces_if_interface_if_link_up_down_trap_enable(void** UNUSED(data), XMLDIFF_OP op, xmlNodePtr UNUSED(old_node), xmlNodePtr new_node, struct nc_err** error) {
	return EXIT_SUCCESS;
}

/*
* Structure transapi_config_callbacks provide mapping between callback and path in configuration datastore.
* It is used by libnetconf library to decide which callbacks will be run.
* DO NOT alter this structure
*/
struct transapi_data_callbacks sysrepo_clbks =  {
	.callbacks_count = 7,
	.data = NULL,
	.callbacks = {
		{.path = "/if:interfaces", .func = callback_if_interfaces},
		{.path = "/if:interfaces/if:interface", .func = callback_if_interfaces_if_interface},
		{.path = "/if:interfaces/if:interface/if:name", .func = callback_if_interfaces_if_interface_if_name},
		{.path = "/if:interfaces/if:interface/if:description", .func = callback_if_interfaces_if_interface_if_description},
		{.path = "/if:interfaces/if:interface/if:type", .func = callback_if_interfaces_if_interface_if_type},
		{.path = "/if:interfaces/if:interface/if:enabled", .func = callback_if_interfaces_if_interface_if_enabled},
		{.path = "/if:interfaces/if:interface/if:link-up-down-trap-enable", .func = callback_if_interfaces_if_interface_if_link_up_down_trap_enable}
	}
};

/*
* RPC callbacks
* Here follows set of callback functions run every time RPC specific for this device arrives.
* You can safely modify the bodies of all function as well as add new functions for better lucidity of code.
* Every function takes array of inputs as an argument. On few first lines they are assigned to named variables. Avoid accessing the array directly.
* If input was not set in RPC message argument in set to NULL.
*/

/*
* Structure transapi_rpc_callbacks provide mapping between callbacks and RPC messages.
* It is used by libnetconf library to decide which callbacks will be run when RPC arrives.
* DO NOT alter this structure
*/
struct transapi_rpc_callbacks sysrepo_rpc_clbks = {
	.callbacks_count = 0,
	.callbacks = {
	}
};

/* overall structure providing content of this module to the libnetconf */
struct transapi sysrepo_transapi = {
    .version = 6,
    .init = sysrepo_transapi_init,
    .close = sysrepo_transapi_close,
    .get_state = sysrepo_get_state_data,
    .clbks_order = TRANSAPI_CLBCKS_ORDER_DEFAULT,
    .data_clbks = &sysrepo_clbks,
    .rpc_clbks = &sysrepo_rpc_clbks,
    .ns_mapping = sysrepo_namespace_mapping,
    .config_modified = &sysrepo_config_modified,
    .erropt = &sysrepo_erropt,
    .file_clbks = NULL
};