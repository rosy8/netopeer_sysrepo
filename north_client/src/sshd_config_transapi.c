/*
 * This is automatically generated callbacks file
 * It contains 3 parts: Configuration callbacks, RPC callbacks and state data callbacks.
 * Do NOT alter function signatures or any structures unless you know exactly what you are doing.
 */

#include <stdlib.h>
#include <libxml/tree.h>

#include <libnetconf_xml.h>
#include <srd.h>

#include "config.h"

/* transAPI version which must be compatible with libnetconf */
//int transapi_version = 6;

/* Signal to libnetconf that configuration data were modified by any callback.
 * 0 - data not modified
 * 1 - data have been modified
 */
int sshdc_config_modified = 0;

/*
 * Determines the callbacks order.
 * Set this variable before compilation and DO NOT modify it in runtime.
 * TRANSAPI_CLBCKS_LEAF_TO_ROOT (default)
 * TRANSAPI_CLBCKS_ROOT_TO_LEAF
 */
//const TRANSAPI_CLBCKS_ORDER_TYPE callbacks_order = TRANSAPI_CLBCKS_ORDER_DEFAULT;

/* Do not modify or set! This variable is set by libnetconf to announce edit-config's error-option
Feel free to use it to distinguish module behavior for different error-option values.
 * Possible values:
 * NC_EDIT_ERROPT_STOP - Following callback after failure are not executed, all successful callbacks executed till
                         failure point must be applied to the device.
 * NC_EDIT_ERROPT_CONT - Failed callbacks are skipped, but all callbacks needed to apply configuration changes are executed
 * NC_EDIT_ERROPT_ROLLBACK - After failure, following callbacks are not executed, but previous successful callbacks are
                         executed again with previous configuration data to roll it back.
 */
NC_EDIT_ERROPT_TYPE sshdc_erropt = NC_EDIT_ERROPT_NOTSET;

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
int sshdc_transapi_init(xmlDocPtr *running) {
	char* aux = NULL;

	srd_applyXPath(sysrepo_fd, "/*[local-name()='config']/*[local-name()='sshd_config_options']", &aux);
	if (aux == NULL) {
		nc_verb_error("Failed to get sysrepo sshdc data.");
		return EXIT_FAILURE;
	}

	*running = xmlReadMemory(aux, strlen(aux), NULL, NULL, XML_PARSE_NOBLANKS|XML_PARSE_NSCLEAN);
	free(aux);
	return EXIT_SUCCESS;
}

/**
 * @brief Free all resources allocated on plugin runtime and prepare plugin for removal.
 */
void sshdc_transapi_close(void) {
	return;
}

/**
 * @brief Retrieve state data from device and return them as XML document
 *
 * @param model	Device data model. libxml2 xmlDocPtr.
 * @param running	Running datastore content. libxml2 xmlDocPtr.
 * @param[out] err  Double pointer to error structure. Fill error when some occurs.
 * @return State data as libxml2 xmlDocPtr or NULL in case of error.
 */
xmlDocPtr sshdc_get_state_data(xmlDocPtr model, xmlDocPtr running, struct nc_err **err) {
	return(NULL);
}
/*
 * Mapping prefixes with namespaces.
 * Do NOT modify this structure!
 */
struct ns_pair sshdc_namespace_mapping[] = {{"ss", "urn:ietf:params:xml:ns:yang:ssh:sshd_config"}, {NULL, NULL}};

/*
 * CONFIGURATION callbacks
 * Here follows set of callback functions run every time some change in associated part of running datastore occurs.
 * You can safely modify the bodies of all function as well as add new functions for better lucidity of code.
 */

/**
 * @brief This callback will be run when node in path /ss:sshd_config_options/ss:AcceptEnv changes
 *
 * @param[in] data	Double pointer to void. Its passed to every callback. You can share data using it.
 * @param[in] op	Observed change in path. XMLDIFF_OP type.
 * @param[in] old_node	Old configuration node. If op == XMLDIFF_ADD, it is NULL.
 * @param[in] new_node	New configuration node. if op == XMLDIFF_REM, it is NULL.
 * @param[out] error	If callback fails, it can return libnetconf error structure with a failure description.
 *
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
/* !DO NOT ALTER FUNCTION SIGNATURE! */
int callback_ss_sshd_config_options_ss_AcceptEnv(void **data, XMLDIFF_OP op, xmlNodePtr old_node, xmlNodePtr new_node, struct nc_err **error) {
	return EXIT_SUCCESS;
}

/**
 * @brief This callback will be run when node in path /ss:sshd_config_options/ss:AddressFamily changes
 *
 * @param[in] data	Double pointer to void. Its passed to every callback. You can share data using it.
 * @param[in] op	Observed change in path. XMLDIFF_OP type.
 * @param[in] old_node	Old configuration node. If op == XMLDIFF_ADD, it is NULL.
 * @param[in] new_node	New configuration node. if op == XMLDIFF_REM, it is NULL.
 * @param[out] error	If callback fails, it can return libnetconf error structure with a failure description.
 *
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
/* !DO NOT ALTER FUNCTION SIGNATURE! */
int callback_ss_sshd_config_options_ss_AddressFamily(void **data, XMLDIFF_OP op, xmlNodePtr old_node, xmlNodePtr new_node, struct nc_err **error) {
	return EXIT_SUCCESS;
}

/**
 * @brief This callback will be run when node in path /ss:sshd_config_options/ss:AllowAgentForwarding changes
 *
 * @param[in] data	Double pointer to void. Its passed to every callback. You can share data using it.
 * @param[in] op	Observed change in path. XMLDIFF_OP type.
 * @param[in] old_node	Old configuration node. If op == XMLDIFF_ADD, it is NULL.
 * @param[in] new_node	New configuration node. if op == XMLDIFF_REM, it is NULL.
 * @param[out] error	If callback fails, it can return libnetconf error structure with a failure description.
 *
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
/* !DO NOT ALTER FUNCTION SIGNATURE! */
int callback_ss_sshd_config_options_ss_AllowAgentForwarding(void **data, XMLDIFF_OP op, xmlNodePtr old_node, xmlNodePtr new_node, struct nc_err **error) {
	return EXIT_SUCCESS;
}

/**
 * @brief This callback will be run when node in path /ss:sshd_config_options/ss:AllowGroups changes
 *
 * @param[in] data	Double pointer to void. Its passed to every callback. You can share data using it.
 * @param[in] op	Observed change in path. XMLDIFF_OP type.
 * @param[in] old_node	Old configuration node. If op == XMLDIFF_ADD, it is NULL.
 * @param[in] new_node	New configuration node. if op == XMLDIFF_REM, it is NULL.
 * @param[out] error	If callback fails, it can return libnetconf error structure with a failure description.
 *
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
/* !DO NOT ALTER FUNCTION SIGNATURE! */
int callback_ss_sshd_config_options_ss_AllowGroups(void **data, XMLDIFF_OP op, xmlNodePtr old_node, xmlNodePtr new_node, struct nc_err **error) {
	return EXIT_SUCCESS;
}

/**
 * @brief This callback will be run when node in path /ss:sshd_config_options/ss:AllowTcpForwarding changes
 *
 * @param[in] data	Double pointer to void. Its passed to every callback. You can share data using it.
 * @param[in] op	Observed change in path. XMLDIFF_OP type.
 * @param[in] old_node	Old configuration node. If op == XMLDIFF_ADD, it is NULL.
 * @param[in] new_node	New configuration node. if op == XMLDIFF_REM, it is NULL.
 * @param[out] error	If callback fails, it can return libnetconf error structure with a failure description.
 *
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
/* !DO NOT ALTER FUNCTION SIGNATURE! */
int callback_ss_sshd_config_options_ss_AllowTcpForwarding(void **data, XMLDIFF_OP op, xmlNodePtr old_node, xmlNodePtr new_node, struct nc_err **error) {
	return EXIT_SUCCESS;
}

/**
 * @brief This callback will be run when node in path /ss:sshd_config_options/ss:AllowUsers changes
 *
 * @param[in] data	Double pointer to void. Its passed to every callback. You can share data using it.
 * @param[in] op	Observed change in path. XMLDIFF_OP type.
 * @param[in] old_node	Old configuration node. If op == XMLDIFF_ADD, it is NULL.
 * @param[in] new_node	New configuration node. if op == XMLDIFF_REM, it is NULL.
 * @param[out] error	If callback fails, it can return libnetconf error structure with a failure description.
 *
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
/* !DO NOT ALTER FUNCTION SIGNATURE! */
int callback_ss_sshd_config_options_ss_AllowUsers(void **data, XMLDIFF_OP op, xmlNodePtr old_node, xmlNodePtr new_node, struct nc_err **error) {
	return EXIT_SUCCESS;
}

/**
 * @brief This callback will be run when node in path /ss:sshd_config_options/ss:AuthenticationMethods changes
 *
 * @param[in] data	Double pointer to void. Its passed to every callback. You can share data using it.
 * @param[in] op	Observed change in path. XMLDIFF_OP type.
 * @param[in] old_node	Old configuration node. If op == XMLDIFF_ADD, it is NULL.
 * @param[in] new_node	New configuration node. if op == XMLDIFF_REM, it is NULL.
 * @param[out] error	If callback fails, it can return libnetconf error structure with a failure description.
 *
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
/* !DO NOT ALTER FUNCTION SIGNATURE! */
int callback_ss_sshd_config_options_ss_AuthenticationMethods(void **data, XMLDIFF_OP op, xmlNodePtr old_node, xmlNodePtr new_node, struct nc_err **error) {
	return EXIT_SUCCESS;
}

/**
 * @brief This callback will be run when node in path /ss:sshd_config_options/ss:AuthorizedKeysCommand changes
 *
 * @param[in] data	Double pointer to void. Its passed to every callback. You can share data using it.
 * @param[in] op	Observed change in path. XMLDIFF_OP type.
 * @param[in] old_node	Old configuration node. If op == XMLDIFF_ADD, it is NULL.
 * @param[in] new_node	New configuration node. if op == XMLDIFF_REM, it is NULL.
 * @param[out] error	If callback fails, it can return libnetconf error structure with a failure description.
 *
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
/* !DO NOT ALTER FUNCTION SIGNATURE! */
int callback_ss_sshd_config_options_ss_AuthorizedKeysCommand(void **data, XMLDIFF_OP op, xmlNodePtr old_node, xmlNodePtr new_node, struct nc_err **error) {
	return EXIT_SUCCESS;
}

/**
 * @brief This callback will be run when node in path /ss:sshd_config_options/ss:AuthorizedKeysCommandUser changes
 *
 * @param[in] data	Double pointer to void. Its passed to every callback. You can share data using it.
 * @param[in] op	Observed change in path. XMLDIFF_OP type.
 * @param[in] old_node	Old configuration node. If op == XMLDIFF_ADD, it is NULL.
 * @param[in] new_node	New configuration node. if op == XMLDIFF_REM, it is NULL.
 * @param[out] error	If callback fails, it can return libnetconf error structure with a failure description.
 *
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
/* !DO NOT ALTER FUNCTION SIGNATURE! */
int callback_ss_sshd_config_options_ss_AuthorizedKeysCommandUser(void **data, XMLDIFF_OP op, xmlNodePtr old_node, xmlNodePtr new_node, struct nc_err **error) {
	return EXIT_SUCCESS;
}

/**
 * @brief This callback will be run when node in path /ss:sshd_config_options/ss:AuthorizedKeysFile changes
 *
 * @param[in] data	Double pointer to void. Its passed to every callback. You can share data using it.
 * @param[in] op	Observed change in path. XMLDIFF_OP type.
 * @param[in] old_node	Old configuration node. If op == XMLDIFF_ADD, it is NULL.
 * @param[in] new_node	New configuration node. if op == XMLDIFF_REM, it is NULL.
 * @param[out] error	If callback fails, it can return libnetconf error structure with a failure description.
 *
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
/* !DO NOT ALTER FUNCTION SIGNATURE! */
int callback_ss_sshd_config_options_ss_AuthorizedKeysFile(void **data, XMLDIFF_OP op, xmlNodePtr old_node, xmlNodePtr new_node, struct nc_err **error) {
	return EXIT_SUCCESS;
}

/**
 * @brief This callback will be run when node in path /ss:sshd_config_options/ss:AuthorizedPrincipalsFile changes
 *
 * @param[in] data	Double pointer to void. Its passed to every callback. You can share data using it.
 * @param[in] op	Observed change in path. XMLDIFF_OP type.
 * @param[in] old_node	Old configuration node. If op == XMLDIFF_ADD, it is NULL.
 * @param[in] new_node	New configuration node. if op == XMLDIFF_REM, it is NULL.
 * @param[out] error	If callback fails, it can return libnetconf error structure with a failure description.
 *
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
/* !DO NOT ALTER FUNCTION SIGNATURE! */
int callback_ss_sshd_config_options_ss_AuthorizedPrincipalsFile(void **data, XMLDIFF_OP op, xmlNodePtr old_node, xmlNodePtr new_node, struct nc_err **error) {
	return EXIT_SUCCESS;
}

/**
 * @brief This callback will be run when node in path /ss:sshd_config_options/ss:Banner changes
 *
 * @param[in] data	Double pointer to void. Its passed to every callback. You can share data using it.
 * @param[in] op	Observed change in path. XMLDIFF_OP type.
 * @param[in] old_node	Old configuration node. If op == XMLDIFF_ADD, it is NULL.
 * @param[in] new_node	New configuration node. if op == XMLDIFF_REM, it is NULL.
 * @param[out] error	If callback fails, it can return libnetconf error structure with a failure description.
 *
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
/* !DO NOT ALTER FUNCTION SIGNATURE! */
int callback_ss_sshd_config_options_ss_Banner(void **data, XMLDIFF_OP op, xmlNodePtr old_node, xmlNodePtr new_node, struct nc_err **error) {
	return EXIT_SUCCESS;
}

/**
 * @brief This callback will be run when node in path /ss:sshd_config_options/ss:ChallengeResponseAuthentication changes
 *
 * @param[in] data	Double pointer to void. Its passed to every callback. You can share data using it.
 * @param[in] op	Observed change in path. XMLDIFF_OP type.
 * @param[in] old_node	Old configuration node. If op == XMLDIFF_ADD, it is NULL.
 * @param[in] new_node	New configuration node. if op == XMLDIFF_REM, it is NULL.
 * @param[out] error	If callback fails, it can return libnetconf error structure with a failure description.
 *
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
/* !DO NOT ALTER FUNCTION SIGNATURE! */
int callback_ss_sshd_config_options_ss_ChallengeResponseAuthentication(void **data, XMLDIFF_OP op, xmlNodePtr old_node, xmlNodePtr new_node, struct nc_err **error) {
	return EXIT_SUCCESS;
}

/**
 * @brief This callback will be run when node in path /ss:sshd_config_options/ss:ChrootDirectory changes
 *
 * @param[in] data	Double pointer to void. Its passed to every callback. You can share data using it.
 * @param[in] op	Observed change in path. XMLDIFF_OP type.
 * @param[in] old_node	Old configuration node. If op == XMLDIFF_ADD, it is NULL.
 * @param[in] new_node	New configuration node. if op == XMLDIFF_REM, it is NULL.
 * @param[out] error	If callback fails, it can return libnetconf error structure with a failure description.
 *
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
/* !DO NOT ALTER FUNCTION SIGNATURE! */
int callback_ss_sshd_config_options_ss_ChrootDirectory(void **data, XMLDIFF_OP op, xmlNodePtr old_node, xmlNodePtr new_node, struct nc_err **error) {
	return EXIT_SUCCESS;
}

/**
 * @brief This callback will be run when node in path /ss:sshd_config_options/ss:Ciphers changes
 *
 * @param[in] data	Double pointer to void. Its passed to every callback. You can share data using it.
 * @param[in] op	Observed change in path. XMLDIFF_OP type.
 * @param[in] old_node	Old configuration node. If op == XMLDIFF_ADD, it is NULL.
 * @param[in] new_node	New configuration node. if op == XMLDIFF_REM, it is NULL.
 * @param[out] error	If callback fails, it can return libnetconf error structure with a failure description.
 *
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
/* !DO NOT ALTER FUNCTION SIGNATURE! */
int callback_ss_sshd_config_options_ss_Ciphers(void **data, XMLDIFF_OP op, xmlNodePtr old_node, xmlNodePtr new_node, struct nc_err **error) {
	return EXIT_SUCCESS;
}

/**
 * @brief This callback will be run when node in path /ss:sshd_config_options/ss:ClientAliveCountMax changes
 *
 * @param[in] data	Double pointer to void. Its passed to every callback. You can share data using it.
 * @param[in] op	Observed change in path. XMLDIFF_OP type.
 * @param[in] old_node	Old configuration node. If op == XMLDIFF_ADD, it is NULL.
 * @param[in] new_node	New configuration node. if op == XMLDIFF_REM, it is NULL.
 * @param[out] error	If callback fails, it can return libnetconf error structure with a failure description.
 *
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
/* !DO NOT ALTER FUNCTION SIGNATURE! */
int callback_ss_sshd_config_options_ss_ClientAliveCountMax(void **data, XMLDIFF_OP op, xmlNodePtr old_node, xmlNodePtr new_node, struct nc_err **error) {
	return EXIT_SUCCESS;
}

/**
 * @brief This callback will be run when node in path /ss:sshd_config_options/ss:ClientAliveInterval changes
 *
 * @param[in] data	Double pointer to void. Its passed to every callback. You can share data using it.
 * @param[in] op	Observed change in path. XMLDIFF_OP type.
 * @param[in] old_node	Old configuration node. If op == XMLDIFF_ADD, it is NULL.
 * @param[in] new_node	New configuration node. if op == XMLDIFF_REM, it is NULL.
 * @param[out] error	If callback fails, it can return libnetconf error structure with a failure description.
 *
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
/* !DO NOT ALTER FUNCTION SIGNATURE! */
int callback_ss_sshd_config_options_ss_ClientAliveInterval(void **data, XMLDIFF_OP op, xmlNodePtr old_node, xmlNodePtr new_node, struct nc_err **error) {
	return EXIT_SUCCESS;
}

/**
 * @brief This callback will be run when node in path /ss:sshd_config_options/ss:Compression changes
 *
 * @param[in] data	Double pointer to void. Its passed to every callback. You can share data using it.
 * @param[in] op	Observed change in path. XMLDIFF_OP type.
 * @param[in] old_node	Old configuration node. If op == XMLDIFF_ADD, it is NULL.
 * @param[in] new_node	New configuration node. if op == XMLDIFF_REM, it is NULL.
 * @param[out] error	If callback fails, it can return libnetconf error structure with a failure description.
 *
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
/* !DO NOT ALTER FUNCTION SIGNATURE! */
int callback_ss_sshd_config_options_ss_Compression(void **data, XMLDIFF_OP op, xmlNodePtr old_node, xmlNodePtr new_node, struct nc_err **error) {
	return EXIT_SUCCESS;
}

/**
 * @brief This callback will be run when node in path /ss:sshd_config_options/ss:DebianBanner changes
 *
 * @param[in] data	Double pointer to void. Its passed to every callback. You can share data using it.
 * @param[in] op	Observed change in path. XMLDIFF_OP type.
 * @param[in] old_node	Old configuration node. If op == XMLDIFF_ADD, it is NULL.
 * @param[in] new_node	New configuration node. if op == XMLDIFF_REM, it is NULL.
 * @param[out] error	If callback fails, it can return libnetconf error structure with a failure description.
 *
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
/* !DO NOT ALTER FUNCTION SIGNATURE! */
int callback_ss_sshd_config_options_ss_DebianBanner(void **data, XMLDIFF_OP op, xmlNodePtr old_node, xmlNodePtr new_node, struct nc_err **error) {
	return EXIT_SUCCESS;
}

/**
 * @brief This callback will be run when node in path /ss:sshd_config_options/ss:DenyGroups changes
 *
 * @param[in] data	Double pointer to void. Its passed to every callback. You can share data using it.
 * @param[in] op	Observed change in path. XMLDIFF_OP type.
 * @param[in] old_node	Old configuration node. If op == XMLDIFF_ADD, it is NULL.
 * @param[in] new_node	New configuration node. if op == XMLDIFF_REM, it is NULL.
 * @param[out] error	If callback fails, it can return libnetconf error structure with a failure description.
 *
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
/* !DO NOT ALTER FUNCTION SIGNATURE! */
int callback_ss_sshd_config_options_ss_DenyGroups(void **data, XMLDIFF_OP op, xmlNodePtr old_node, xmlNodePtr new_node, struct nc_err **error) {
	return EXIT_SUCCESS;
}

/**
 * @brief This callback will be run when node in path /ss:sshd_config_options/ss:DenyUsers changes
 *
 * @param[in] data	Double pointer to void. Its passed to every callback. You can share data using it.
 * @param[in] op	Observed change in path. XMLDIFF_OP type.
 * @param[in] old_node	Old configuration node. If op == XMLDIFF_ADD, it is NULL.
 * @param[in] new_node	New configuration node. if op == XMLDIFF_REM, it is NULL.
 * @param[out] error	If callback fails, it can return libnetconf error structure with a failure description.
 *
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
/* !DO NOT ALTER FUNCTION SIGNATURE! */
int callback_ss_sshd_config_options_ss_DenyUsers(void **data, XMLDIFF_OP op, xmlNodePtr old_node, xmlNodePtr new_node, struct nc_err **error) {
	return EXIT_SUCCESS;
}

/**
 * @brief This callback will be run when node in path /ss:sshd_config_options/ss:ForceCommand changes
 *
 * @param[in] data	Double pointer to void. Its passed to every callback. You can share data using it.
 * @param[in] op	Observed change in path. XMLDIFF_OP type.
 * @param[in] old_node	Old configuration node. If op == XMLDIFF_ADD, it is NULL.
 * @param[in] new_node	New configuration node. if op == XMLDIFF_REM, it is NULL.
 * @param[out] error	If callback fails, it can return libnetconf error structure with a failure description.
 *
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
/* !DO NOT ALTER FUNCTION SIGNATURE! */
int callback_ss_sshd_config_options_ss_ForceCommand(void **data, XMLDIFF_OP op, xmlNodePtr old_node, xmlNodePtr new_node, struct nc_err **error) {
	return EXIT_SUCCESS;
}

/**
 * @brief This callback will be run when node in path /ss:sshd_config_options/ss:GatewayPorts changes
 *
 * @param[in] data	Double pointer to void. Its passed to every callback. You can share data using it.
 * @param[in] op	Observed change in path. XMLDIFF_OP type.
 * @param[in] old_node	Old configuration node. If op == XMLDIFF_ADD, it is NULL.
 * @param[in] new_node	New configuration node. if op == XMLDIFF_REM, it is NULL.
 * @param[out] error	If callback fails, it can return libnetconf error structure with a failure description.
 *
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
/* !DO NOT ALTER FUNCTION SIGNATURE! */
int callback_ss_sshd_config_options_ss_GatewayPorts(void **data, XMLDIFF_OP op, xmlNodePtr old_node, xmlNodePtr new_node, struct nc_err **error) {
	return EXIT_SUCCESS;
}

/**
 * @brief This callback will be run when node in path /ss:sshd_config_options/ss:GSSAPIAuthentication changes
 *
 * @param[in] data	Double pointer to void. Its passed to every callback. You can share data using it.
 * @param[in] op	Observed change in path. XMLDIFF_OP type.
 * @param[in] old_node	Old configuration node. If op == XMLDIFF_ADD, it is NULL.
 * @param[in] new_node	New configuration node. if op == XMLDIFF_REM, it is NULL.
 * @param[out] error	If callback fails, it can return libnetconf error structure with a failure description.
 *
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
/* !DO NOT ALTER FUNCTION SIGNATURE! */
int callback_ss_sshd_config_options_ss_GSSAPIAuthentication(void **data, XMLDIFF_OP op, xmlNodePtr old_node, xmlNodePtr new_node, struct nc_err **error) {
	return EXIT_SUCCESS;
}

/**
 * @brief This callback will be run when node in path /ss:sshd_config_options/ss:GSSAPIKeyExchange changes
 *
 * @param[in] data	Double pointer to void. Its passed to every callback. You can share data using it.
 * @param[in] op	Observed change in path. XMLDIFF_OP type.
 * @param[in] old_node	Old configuration node. If op == XMLDIFF_ADD, it is NULL.
 * @param[in] new_node	New configuration node. if op == XMLDIFF_REM, it is NULL.
 * @param[out] error	If callback fails, it can return libnetconf error structure with a failure description.
 *
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
/* !DO NOT ALTER FUNCTION SIGNATURE! */
int callback_ss_sshd_config_options_ss_GSSAPIKeyExchange(void **data, XMLDIFF_OP op, xmlNodePtr old_node, xmlNodePtr new_node, struct nc_err **error) {
	return EXIT_SUCCESS;
}

/**
 * @brief This callback will be run when node in path /ss:sshd_config_options/ss:GSSAPICleanupCredentials changes
 *
 * @param[in] data	Double pointer to void. Its passed to every callback. You can share data using it.
 * @param[in] op	Observed change in path. XMLDIFF_OP type.
 * @param[in] old_node	Old configuration node. If op == XMLDIFF_ADD, it is NULL.
 * @param[in] new_node	New configuration node. if op == XMLDIFF_REM, it is NULL.
 * @param[out] error	If callback fails, it can return libnetconf error structure with a failure description.
 *
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
/* !DO NOT ALTER FUNCTION SIGNATURE! */
int callback_ss_sshd_config_options_ss_GSSAPICleanupCredentials(void **data, XMLDIFF_OP op, xmlNodePtr old_node, xmlNodePtr new_node, struct nc_err **error) {
	return EXIT_SUCCESS;
}

/**
 * @brief This callback will be run when node in path /ss:sshd_config_options/ss:GSSAPIStrictAcceptorCheck changes
 *
 * @param[in] data	Double pointer to void. Its passed to every callback. You can share data using it.
 * @param[in] op	Observed change in path. XMLDIFF_OP type.
 * @param[in] old_node	Old configuration node. If op == XMLDIFF_ADD, it is NULL.
 * @param[in] new_node	New configuration node. if op == XMLDIFF_REM, it is NULL.
 * @param[out] error	If callback fails, it can return libnetconf error structure with a failure description.
 *
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
/* !DO NOT ALTER FUNCTION SIGNATURE! */
int callback_ss_sshd_config_options_ss_GSSAPIStrictAcceptorCheck(void **data, XMLDIFF_OP op, xmlNodePtr old_node, xmlNodePtr new_node, struct nc_err **error) {
	return EXIT_SUCCESS;
}

/**
 * @brief This callback will be run when node in path /ss:sshd_config_options/ss:GSSAPIStoreCredentialsOnRekey changes
 *
 * @param[in] data	Double pointer to void. Its passed to every callback. You can share data using it.
 * @param[in] op	Observed change in path. XMLDIFF_OP type.
 * @param[in] old_node	Old configuration node. If op == XMLDIFF_ADD, it is NULL.
 * @param[in] new_node	New configuration node. if op == XMLDIFF_REM, it is NULL.
 * @param[out] error	If callback fails, it can return libnetconf error structure with a failure description.
 *
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
/* !DO NOT ALTER FUNCTION SIGNATURE! */
int callback_ss_sshd_config_options_ss_GSSAPIStoreCredentialsOnRekey(void **data, XMLDIFF_OP op, xmlNodePtr old_node, xmlNodePtr new_node, struct nc_err **error) {
	return EXIT_SUCCESS;
}

/**
 * @brief This callback will be run when node in path /ss:sshd_config_options/ss:HostbasedAuthentication changes
 *
 * @param[in] data	Double pointer to void. Its passed to every callback. You can share data using it.
 * @param[in] op	Observed change in path. XMLDIFF_OP type.
 * @param[in] old_node	Old configuration node. If op == XMLDIFF_ADD, it is NULL.
 * @param[in] new_node	New configuration node. if op == XMLDIFF_REM, it is NULL.
 * @param[out] error	If callback fails, it can return libnetconf error structure with a failure description.
 *
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
/* !DO NOT ALTER FUNCTION SIGNATURE! */
int callback_ss_sshd_config_options_ss_HostbasedAuthentication(void **data, XMLDIFF_OP op, xmlNodePtr old_node, xmlNodePtr new_node, struct nc_err **error) {
	return EXIT_SUCCESS;
}

/**
 * @brief This callback will be run when node in path /ss:sshd_config_options/ss:HostbasedUsesNameFromPacketOnly changes
 *
 * @param[in] data	Double pointer to void. Its passed to every callback. You can share data using it.
 * @param[in] op	Observed change in path. XMLDIFF_OP type.
 * @param[in] old_node	Old configuration node. If op == XMLDIFF_ADD, it is NULL.
 * @param[in] new_node	New configuration node. if op == XMLDIFF_REM, it is NULL.
 * @param[out] error	If callback fails, it can return libnetconf error structure with a failure description.
 *
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
/* !DO NOT ALTER FUNCTION SIGNATURE! */
int callback_ss_sshd_config_options_ss_HostbasedUsesNameFromPacketOnly(void **data, XMLDIFF_OP op, xmlNodePtr old_node, xmlNodePtr new_node, struct nc_err **error) {
	return EXIT_SUCCESS;
}

/**
 * @brief This callback will be run when node in path /ss:sshd_config_options/ss:HostCertificate changes
 *
 * @param[in] data	Double pointer to void. Its passed to every callback. You can share data using it.
 * @param[in] op	Observed change in path. XMLDIFF_OP type.
 * @param[in] old_node	Old configuration node. If op == XMLDIFF_ADD, it is NULL.
 * @param[in] new_node	New configuration node. if op == XMLDIFF_REM, it is NULL.
 * @param[out] error	If callback fails, it can return libnetconf error structure with a failure description.
 *
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
/* !DO NOT ALTER FUNCTION SIGNATURE! */
int callback_ss_sshd_config_options_ss_HostCertificate(void **data, XMLDIFF_OP op, xmlNodePtr old_node, xmlNodePtr new_node, struct nc_err **error) {
	return EXIT_SUCCESS;
}

/**
 * @brief This callback will be run when node in path /ss:sshd_config_options/ss:HostKey changes
 *
 * @param[in] data	Double pointer to void. Its passed to every callback. You can share data using it.
 * @param[in] op	Observed change in path. XMLDIFF_OP type.
 * @param[in] old_node	Old configuration node. If op == XMLDIFF_ADD, it is NULL.
 * @param[in] new_node	New configuration node. if op == XMLDIFF_REM, it is NULL.
 * @param[out] error	If callback fails, it can return libnetconf error structure with a failure description.
 *
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
/* !DO NOT ALTER FUNCTION SIGNATURE! */
int callback_ss_sshd_config_options_ss_HostKey(void **data, XMLDIFF_OP op, xmlNodePtr old_node, xmlNodePtr new_node, struct nc_err **error) {
	return EXIT_SUCCESS;
}

/**
 * @brief This callback will be run when node in path /ss:sshd_config_options/ss:HostKeyAgent changes
 *
 * @param[in] data	Double pointer to void. Its passed to every callback. You can share data using it.
 * @param[in] op	Observed change in path. XMLDIFF_OP type.
 * @param[in] old_node	Old configuration node. If op == XMLDIFF_ADD, it is NULL.
 * @param[in] new_node	New configuration node. if op == XMLDIFF_REM, it is NULL.
 * @param[out] error	If callback fails, it can return libnetconf error structure with a failure description.
 *
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
/* !DO NOT ALTER FUNCTION SIGNATURE! */
int callback_ss_sshd_config_options_ss_HostKeyAgent(void **data, XMLDIFF_OP op, xmlNodePtr old_node, xmlNodePtr new_node, struct nc_err **error) {
	return EXIT_SUCCESS;
}

/**
 * @brief This callback will be run when node in path /ss:sshd_config_options/ss:IgnoreRhosts changes
 *
 * @param[in] data	Double pointer to void. Its passed to every callback. You can share data using it.
 * @param[in] op	Observed change in path. XMLDIFF_OP type.
 * @param[in] old_node	Old configuration node. If op == XMLDIFF_ADD, it is NULL.
 * @param[in] new_node	New configuration node. if op == XMLDIFF_REM, it is NULL.
 * @param[out] error	If callback fails, it can return libnetconf error structure with a failure description.
 *
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
/* !DO NOT ALTER FUNCTION SIGNATURE! */
int callback_ss_sshd_config_options_ss_IgnoreRhosts(void **data, XMLDIFF_OP op, xmlNodePtr old_node, xmlNodePtr new_node, struct nc_err **error) {
	return EXIT_SUCCESS;
}

/**
 * @brief This callback will be run when node in path /ss:sshd_config_options/ss:IgnoreUserKnownHosts changes
 *
 * @param[in] data	Double pointer to void. Its passed to every callback. You can share data using it.
 * @param[in] op	Observed change in path. XMLDIFF_OP type.
 * @param[in] old_node	Old configuration node. If op == XMLDIFF_ADD, it is NULL.
 * @param[in] new_node	New configuration node. if op == XMLDIFF_REM, it is NULL.
 * @param[out] error	If callback fails, it can return libnetconf error structure with a failure description.
 *
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
/* !DO NOT ALTER FUNCTION SIGNATURE! */
int callback_ss_sshd_config_options_ss_IgnoreUserKnownHosts(void **data, XMLDIFF_OP op, xmlNodePtr old_node, xmlNodePtr new_node, struct nc_err **error) {
	return EXIT_SUCCESS;
}

/**
 * @brief This callback will be run when node in path /ss:sshd_config_options/ss:IPQoS changes
 *
 * @param[in] data	Double pointer to void. Its passed to every callback. You can share data using it.
 * @param[in] op	Observed change in path. XMLDIFF_OP type.
 * @param[in] old_node	Old configuration node. If op == XMLDIFF_ADD, it is NULL.
 * @param[in] new_node	New configuration node. if op == XMLDIFF_REM, it is NULL.
 * @param[out] error	If callback fails, it can return libnetconf error structure with a failure description.
 *
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
/* !DO NOT ALTER FUNCTION SIGNATURE! */
int callback_ss_sshd_config_options_ss_IPQoS(void **data, XMLDIFF_OP op, xmlNodePtr old_node, xmlNodePtr new_node, struct nc_err **error) {
	return EXIT_SUCCESS;
}

/**
 * @brief This callback will be run when node in path /ss:sshd_config_options/ss:KbdInteractiveAuthentication changes
 *
 * @param[in] data	Double pointer to void. Its passed to every callback. You can share data using it.
 * @param[in] op	Observed change in path. XMLDIFF_OP type.
 * @param[in] old_node	Old configuration node. If op == XMLDIFF_ADD, it is NULL.
 * @param[in] new_node	New configuration node. if op == XMLDIFF_REM, it is NULL.
 * @param[out] error	If callback fails, it can return libnetconf error structure with a failure description.
 *
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
/* !DO NOT ALTER FUNCTION SIGNATURE! */
int callback_ss_sshd_config_options_ss_KbdInteractiveAuthentication(void **data, XMLDIFF_OP op, xmlNodePtr old_node, xmlNodePtr new_node, struct nc_err **error) {
	return EXIT_SUCCESS;
}

/**
 * @brief This callback will be run when node in path /ss:sshd_config_options/ss:KerberosAuthentication changes
 *
 * @param[in] data	Double pointer to void. Its passed to every callback. You can share data using it.
 * @param[in] op	Observed change in path. XMLDIFF_OP type.
 * @param[in] old_node	Old configuration node. If op == XMLDIFF_ADD, it is NULL.
 * @param[in] new_node	New configuration node. if op == XMLDIFF_REM, it is NULL.
 * @param[out] error	If callback fails, it can return libnetconf error structure with a failure description.
 *
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
/* !DO NOT ALTER FUNCTION SIGNATURE! */
int callback_ss_sshd_config_options_ss_KerberosAuthentication(void **data, XMLDIFF_OP op, xmlNodePtr old_node, xmlNodePtr new_node, struct nc_err **error) {
	return EXIT_SUCCESS;
}

/**
 * @brief This callback will be run when node in path /ss:sshd_config_options/ss:KerberosGetAFSToken changes
 *
 * @param[in] data	Double pointer to void. Its passed to every callback. You can share data using it.
 * @param[in] op	Observed change in path. XMLDIFF_OP type.
 * @param[in] old_node	Old configuration node. If op == XMLDIFF_ADD, it is NULL.
 * @param[in] new_node	New configuration node. if op == XMLDIFF_REM, it is NULL.
 * @param[out] error	If callback fails, it can return libnetconf error structure with a failure description.
 *
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
/* !DO NOT ALTER FUNCTION SIGNATURE! */
int callback_ss_sshd_config_options_ss_KerberosGetAFSToken(void **data, XMLDIFF_OP op, xmlNodePtr old_node, xmlNodePtr new_node, struct nc_err **error) {
	return EXIT_SUCCESS;
}

/**
 * @brief This callback will be run when node in path /ss:sshd_config_options/ss:KerberosOrLocalPasswd changes
 *
 * @param[in] data	Double pointer to void. Its passed to every callback. You can share data using it.
 * @param[in] op	Observed change in path. XMLDIFF_OP type.
 * @param[in] old_node	Old configuration node. If op == XMLDIFF_ADD, it is NULL.
 * @param[in] new_node	New configuration node. if op == XMLDIFF_REM, it is NULL.
 * @param[out] error	If callback fails, it can return libnetconf error structure with a failure description.
 *
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
/* !DO NOT ALTER FUNCTION SIGNATURE! */
int callback_ss_sshd_config_options_ss_KerberosOrLocalPasswd(void **data, XMLDIFF_OP op, xmlNodePtr old_node, xmlNodePtr new_node, struct nc_err **error) {
	return EXIT_SUCCESS;
}

/**
 * @brief This callback will be run when node in path /ss:sshd_config_options/ss:KerberosTicketCleanup changes
 *
 * @param[in] data	Double pointer to void. Its passed to every callback. You can share data using it.
 * @param[in] op	Observed change in path. XMLDIFF_OP type.
 * @param[in] old_node	Old configuration node. If op == XMLDIFF_ADD, it is NULL.
 * @param[in] new_node	New configuration node. if op == XMLDIFF_REM, it is NULL.
 * @param[out] error	If callback fails, it can return libnetconf error structure with a failure description.
 *
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
/* !DO NOT ALTER FUNCTION SIGNATURE! */
int callback_ss_sshd_config_options_ss_KerberosTicketCleanup(void **data, XMLDIFF_OP op, xmlNodePtr old_node, xmlNodePtr new_node, struct nc_err **error) {
	return EXIT_SUCCESS;
}

/**
 * @brief This callback will be run when node in path /ss:sshd_config_options/ss:KexAlgorithms changes
 *
 * @param[in] data	Double pointer to void. Its passed to every callback. You can share data using it.
 * @param[in] op	Observed change in path. XMLDIFF_OP type.
 * @param[in] old_node	Old configuration node. If op == XMLDIFF_ADD, it is NULL.
 * @param[in] new_node	New configuration node. if op == XMLDIFF_REM, it is NULL.
 * @param[out] error	If callback fails, it can return libnetconf error structure with a failure description.
 *
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
/* !DO NOT ALTER FUNCTION SIGNATURE! */
int callback_ss_sshd_config_options_ss_KexAlgorithms(void **data, XMLDIFF_OP op, xmlNodePtr old_node, xmlNodePtr new_node, struct nc_err **error) {
	return EXIT_SUCCESS;
}

/**
 * @brief This callback will be run when node in path /ss:sshd_config_options/ss:KeyRegenerationInterval changes
 *
 * @param[in] data	Double pointer to void. Its passed to every callback. You can share data using it.
 * @param[in] op	Observed change in path. XMLDIFF_OP type.
 * @param[in] old_node	Old configuration node. If op == XMLDIFF_ADD, it is NULL.
 * @param[in] new_node	New configuration node. if op == XMLDIFF_REM, it is NULL.
 * @param[out] error	If callback fails, it can return libnetconf error structure with a failure description.
 *
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
/* !DO NOT ALTER FUNCTION SIGNATURE! */
int callback_ss_sshd_config_options_ss_KeyRegenerationInterval(void **data, XMLDIFF_OP op, xmlNodePtr old_node, xmlNodePtr new_node, struct nc_err **error) {
	return EXIT_SUCCESS;
}

/**
 * @brief This callback will be run when node in path /ss:sshd_config_options/ss:ListenAddress changes
 *
 * @param[in] data	Double pointer to void. Its passed to every callback. You can share data using it.
 * @param[in] op	Observed change in path. XMLDIFF_OP type.
 * @param[in] old_node	Old configuration node. If op == XMLDIFF_ADD, it is NULL.
 * @param[in] new_node	New configuration node. if op == XMLDIFF_REM, it is NULL.
 * @param[out] error	If callback fails, it can return libnetconf error structure with a failure description.
 *
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
/* !DO NOT ALTER FUNCTION SIGNATURE! */
int callback_ss_sshd_config_options_ss_ListenAddress(void **data, XMLDIFF_OP op, xmlNodePtr old_node, xmlNodePtr new_node, struct nc_err **error) {
	return EXIT_SUCCESS;
}

/**
 * @brief This callback will be run when node in path /ss:sshd_config_options/ss:LoginGraceTime changes
 *
 * @param[in] data	Double pointer to void. Its passed to every callback. You can share data using it.
 * @param[in] op	Observed change in path. XMLDIFF_OP type.
 * @param[in] old_node	Old configuration node. If op == XMLDIFF_ADD, it is NULL.
 * @param[in] new_node	New configuration node. if op == XMLDIFF_REM, it is NULL.
 * @param[out] error	If callback fails, it can return libnetconf error structure with a failure description.
 *
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
/* !DO NOT ALTER FUNCTION SIGNATURE! */
int callback_ss_sshd_config_options_ss_LoginGraceTime(void **data, XMLDIFF_OP op, xmlNodePtr old_node, xmlNodePtr new_node, struct nc_err **error) {
	return EXIT_SUCCESS;
}

/**
 * @brief This callback will be run when node in path /ss:sshd_config_options/ss:LogLevel changes
 *
 * @param[in] data	Double pointer to void. Its passed to every callback. You can share data using it.
 * @param[in] op	Observed change in path. XMLDIFF_OP type.
 * @param[in] old_node	Old configuration node. If op == XMLDIFF_ADD, it is NULL.
 * @param[in] new_node	New configuration node. if op == XMLDIFF_REM, it is NULL.
 * @param[out] error	If callback fails, it can return libnetconf error structure with a failure description.
 *
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
/* !DO NOT ALTER FUNCTION SIGNATURE! */
int callback_ss_sshd_config_options_ss_LogLevel(void **data, XMLDIFF_OP op, xmlNodePtr old_node, xmlNodePtr new_node, struct nc_err **error) {
	return EXIT_SUCCESS;
}

/**
 * @brief This callback will be run when node in path /ss:sshd_config_options/ss:MACs changes
 *
 * @param[in] data	Double pointer to void. Its passed to every callback. You can share data using it.
 * @param[in] op	Observed change in path. XMLDIFF_OP type.
 * @param[in] old_node	Old configuration node. If op == XMLDIFF_ADD, it is NULL.
 * @param[in] new_node	New configuration node. if op == XMLDIFF_REM, it is NULL.
 * @param[out] error	If callback fails, it can return libnetconf error structure with a failure description.
 *
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
/* !DO NOT ALTER FUNCTION SIGNATURE! */
int callback_ss_sshd_config_options_ss_MACs(void **data, XMLDIFF_OP op, xmlNodePtr old_node, xmlNodePtr new_node, struct nc_err **error) {
	return EXIT_SUCCESS;
}

/**
 * @brief This callback will be run when node in path /ss:sshd_config_options/ss:Match changes
 *
 * @param[in] data	Double pointer to void. Its passed to every callback. You can share data using it.
 * @param[in] op	Observed change in path. XMLDIFF_OP type.
 * @param[in] old_node	Old configuration node. If op == XMLDIFF_ADD, it is NULL.
 * @param[in] new_node	New configuration node. if op == XMLDIFF_REM, it is NULL.
 * @param[out] error	If callback fails, it can return libnetconf error structure with a failure description.
 *
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
/* !DO NOT ALTER FUNCTION SIGNATURE! */
int callback_ss_sshd_config_options_ss_Match(void **data, XMLDIFF_OP op, xmlNodePtr old_node, xmlNodePtr new_node, struct nc_err **error) {
	return EXIT_SUCCESS;
}

/**
 * @brief This callback will be run when node in path /ss:sshd_config_options/ss:MaxAuthTries changes
 *
 * @param[in] data	Double pointer to void. Its passed to every callback. You can share data using it.
 * @param[in] op	Observed change in path. XMLDIFF_OP type.
 * @param[in] old_node	Old configuration node. If op == XMLDIFF_ADD, it is NULL.
 * @param[in] new_node	New configuration node. if op == XMLDIFF_REM, it is NULL.
 * @param[out] error	If callback fails, it can return libnetconf error structure with a failure description.
 *
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
/* !DO NOT ALTER FUNCTION SIGNATURE! */
int callback_ss_sshd_config_options_ss_MaxAuthTries(void **data, XMLDIFF_OP op, xmlNodePtr old_node, xmlNodePtr new_node, struct nc_err **error) {
	return EXIT_SUCCESS;
}

/**
 * @brief This callback will be run when node in path /ss:sshd_config_options/ss:MaxSessions changes
 *
 * @param[in] data	Double pointer to void. Its passed to every callback. You can share data using it.
 * @param[in] op	Observed change in path. XMLDIFF_OP type.
 * @param[in] old_node	Old configuration node. If op == XMLDIFF_ADD, it is NULL.
 * @param[in] new_node	New configuration node. if op == XMLDIFF_REM, it is NULL.
 * @param[out] error	If callback fails, it can return libnetconf error structure with a failure description.
 *
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
/* !DO NOT ALTER FUNCTION SIGNATURE! */
int callback_ss_sshd_config_options_ss_MaxSessions(void **data, XMLDIFF_OP op, xmlNodePtr old_node, xmlNodePtr new_node, struct nc_err **error) {
	return EXIT_SUCCESS;
}

/**
 * @brief This callback will be run when node in path /ss:sshd_config_options/ss:MaxStartups changes
 *
 * @param[in] data	Double pointer to void. Its passed to every callback. You can share data using it.
 * @param[in] op	Observed change in path. XMLDIFF_OP type.
 * @param[in] old_node	Old configuration node. If op == XMLDIFF_ADD, it is NULL.
 * @param[in] new_node	New configuration node. if op == XMLDIFF_REM, it is NULL.
 * @param[out] error	If callback fails, it can return libnetconf error structure with a failure description.
 *
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
/* !DO NOT ALTER FUNCTION SIGNATURE! */
int callback_ss_sshd_config_options_ss_MaxStartups(void **data, XMLDIFF_OP op, xmlNodePtr old_node, xmlNodePtr new_node, struct nc_err **error) {
	return EXIT_SUCCESS;
}

/**
 * @brief This callback will be run when node in path /ss:sshd_config_options/ss:OS changes
 *
 * @param[in] data	Double pointer to void. Its passed to every callback. You can share data using it.
 * @param[in] op	Observed change in path. XMLDIFF_OP type.
 * @param[in] old_node	Old configuration node. If op == XMLDIFF_ADD, it is NULL.
 * @param[in] new_node	New configuration node. if op == XMLDIFF_REM, it is NULL.
 * @param[out] error	If callback fails, it can return libnetconf error structure with a failure description.
 *
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
/* !DO NOT ALTER FUNCTION SIGNATURE! */
int callback_ss_sshd_config_options_ss_OS(void **data, XMLDIFF_OP op, xmlNodePtr old_node, xmlNodePtr new_node, struct nc_err **error) {
	return EXIT_SUCCESS;
}

/**
 * @brief This callback will be run when node in path /ss:sshd_config_options/ss:PasswordAuthentication changes
 *
 * @param[in] data	Double pointer to void. Its passed to every callback. You can share data using it.
 * @param[in] op	Observed change in path. XMLDIFF_OP type.
 * @param[in] old_node	Old configuration node. If op == XMLDIFF_ADD, it is NULL.
 * @param[in] new_node	New configuration node. if op == XMLDIFF_REM, it is NULL.
 * @param[out] error	If callback fails, it can return libnetconf error structure with a failure description.
 *
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
/* !DO NOT ALTER FUNCTION SIGNATURE! */
int callback_ss_sshd_config_options_ss_PasswordAuthentication(void **data, XMLDIFF_OP op, xmlNodePtr old_node, xmlNodePtr new_node, struct nc_err **error) {
	return EXIT_SUCCESS;
}

/**
 * @brief This callback will be run when node in path /ss:sshd_config_options/ss:PermitEmptyPasswords changes
 *
 * @param[in] data	Double pointer to void. Its passed to every callback. You can share data using it.
 * @param[in] op	Observed change in path. XMLDIFF_OP type.
 * @param[in] old_node	Old configuration node. If op == XMLDIFF_ADD, it is NULL.
 * @param[in] new_node	New configuration node. if op == XMLDIFF_REM, it is NULL.
 * @param[out] error	If callback fails, it can return libnetconf error structure with a failure description.
 *
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
/* !DO NOT ALTER FUNCTION SIGNATURE! */
int callback_ss_sshd_config_options_ss_PermitEmptyPasswords(void **data, XMLDIFF_OP op, xmlNodePtr old_node, xmlNodePtr new_node, struct nc_err **error) {
	return EXIT_SUCCESS;
}

/**
 * @brief This callback will be run when node in path /ss:sshd_config_options/ss:PermitOpen changes
 *
 * @param[in] data	Double pointer to void. Its passed to every callback. You can share data using it.
 * @param[in] op	Observed change in path. XMLDIFF_OP type.
 * @param[in] old_node	Old configuration node. If op == XMLDIFF_ADD, it is NULL.
 * @param[in] new_node	New configuration node. if op == XMLDIFF_REM, it is NULL.
 * @param[out] error	If callback fails, it can return libnetconf error structure with a failure description.
 *
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
/* !DO NOT ALTER FUNCTION SIGNATURE! */
int callback_ss_sshd_config_options_ss_PermitOpen(void **data, XMLDIFF_OP op, xmlNodePtr old_node, xmlNodePtr new_node, struct nc_err **error) {
	return EXIT_SUCCESS;
}

/**
 * @brief This callback will be run when node in path /ss:sshd_config_options/ss:PermitRootLogin changes
 *
 * @param[in] data	Double pointer to void. Its passed to every callback. You can share data using it.
 * @param[in] op	Observed change in path. XMLDIFF_OP type.
 * @param[in] old_node	Old configuration node. If op == XMLDIFF_ADD, it is NULL.
 * @param[in] new_node	New configuration node. if op == XMLDIFF_REM, it is NULL.
 * @param[out] error	If callback fails, it can return libnetconf error structure with a failure description.
 *
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
/* !DO NOT ALTER FUNCTION SIGNATURE! */
int callback_ss_sshd_config_options_ss_PermitRootLogin(void **data, XMLDIFF_OP op, xmlNodePtr old_node, xmlNodePtr new_node, struct nc_err **error) {
	return EXIT_SUCCESS;
}

/**
 * @brief This callback will be run when node in path /ss:sshd_config_options/ss:PermitTunnel changes
 *
 * @param[in] data	Double pointer to void. Its passed to every callback. You can share data using it.
 * @param[in] op	Observed change in path. XMLDIFF_OP type.
 * @param[in] old_node	Old configuration node. If op == XMLDIFF_ADD, it is NULL.
 * @param[in] new_node	New configuration node. if op == XMLDIFF_REM, it is NULL.
 * @param[out] error	If callback fails, it can return libnetconf error structure with a failure description.
 *
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
/* !DO NOT ALTER FUNCTION SIGNATURE! */
int callback_ss_sshd_config_options_ss_PermitTunnel(void **data, XMLDIFF_OP op, xmlNodePtr old_node, xmlNodePtr new_node, struct nc_err **error) {
	return EXIT_SUCCESS;
}

/**
 * @brief This callback will be run when node in path /ss:sshd_config_options/ss:PermitTTY changes
 *
 * @param[in] data	Double pointer to void. Its passed to every callback. You can share data using it.
 * @param[in] op	Observed change in path. XMLDIFF_OP type.
 * @param[in] old_node	Old configuration node. If op == XMLDIFF_ADD, it is NULL.
 * @param[in] new_node	New configuration node. if op == XMLDIFF_REM, it is NULL.
 * @param[out] error	If callback fails, it can return libnetconf error structure with a failure description.
 *
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
/* !DO NOT ALTER FUNCTION SIGNATURE! */
int callback_ss_sshd_config_options_ss_PermitTTY(void **data, XMLDIFF_OP op, xmlNodePtr old_node, xmlNodePtr new_node, struct nc_err **error) {
	return EXIT_SUCCESS;
}

/**
 * @brief This callback will be run when node in path /ss:sshd_config_options/ss:PermitUserEnvironment changes
 *
 * @param[in] data	Double pointer to void. Its passed to every callback. You can share data using it.
 * @param[in] op	Observed change in path. XMLDIFF_OP type.
 * @param[in] old_node	Old configuration node. If op == XMLDIFF_ADD, it is NULL.
 * @param[in] new_node	New configuration node. if op == XMLDIFF_REM, it is NULL.
 * @param[out] error	If callback fails, it can return libnetconf error structure with a failure description.
 *
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
/* !DO NOT ALTER FUNCTION SIGNATURE! */
int callback_ss_sshd_config_options_ss_PermitUserEnvironment(void **data, XMLDIFF_OP op, xmlNodePtr old_node, xmlNodePtr new_node, struct nc_err **error) {
	return EXIT_SUCCESS;
}

/**
 * @brief This callback will be run when node in path /ss:sshd_config_options/ss:PidFile changes
 *
 * @param[in] data	Double pointer to void. Its passed to every callback. You can share data using it.
 * @param[in] op	Observed change in path. XMLDIFF_OP type.
 * @param[in] old_node	Old configuration node. If op == XMLDIFF_ADD, it is NULL.
 * @param[in] new_node	New configuration node. if op == XMLDIFF_REM, it is NULL.
 * @param[out] error	If callback fails, it can return libnetconf error structure with a failure description.
 *
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
/* !DO NOT ALTER FUNCTION SIGNATURE! */
int callback_ss_sshd_config_options_ss_PidFile(void **data, XMLDIFF_OP op, xmlNodePtr old_node, xmlNodePtr new_node, struct nc_err **error) {
	return EXIT_SUCCESS;
}

/**
 * @brief This callback will be run when node in path /ss:sshd_config_options/ss:Port changes
 *
 * @param[in] data	Double pointer to void. Its passed to every callback. You can share data using it.
 * @param[in] op	Observed change in path. XMLDIFF_OP type.
 * @param[in] old_node	Old configuration node. If op == XMLDIFF_ADD, it is NULL.
 * @param[in] new_node	New configuration node. if op == XMLDIFF_REM, it is NULL.
 * @param[out] error	If callback fails, it can return libnetconf error structure with a failure description.
 *
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
/* !DO NOT ALTER FUNCTION SIGNATURE! */
int callback_ss_sshd_config_options_ss_Port(void **data, XMLDIFF_OP op, xmlNodePtr old_node, xmlNodePtr new_node, struct nc_err **error) {
	return EXIT_SUCCESS;
}

/**
 * @brief This callback will be run when node in path /ss:sshd_config_options/ss:PrintLastLog changes
 *
 * @param[in] data	Double pointer to void. Its passed to every callback. You can share data using it.
 * @param[in] op	Observed change in path. XMLDIFF_OP type.
 * @param[in] old_node	Old configuration node. If op == XMLDIFF_ADD, it is NULL.
 * @param[in] new_node	New configuration node. if op == XMLDIFF_REM, it is NULL.
 * @param[out] error	If callback fails, it can return libnetconf error structure with a failure description.
 *
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
/* !DO NOT ALTER FUNCTION SIGNATURE! */
int callback_ss_sshd_config_options_ss_PrintLastLog(void **data, XMLDIFF_OP op, xmlNodePtr old_node, xmlNodePtr new_node, struct nc_err **error) {
	return EXIT_SUCCESS;
}

/**
 * @brief This callback will be run when node in path /ss:sshd_config_options/ss:PrintMotd changes
 *
 * @param[in] data	Double pointer to void. Its passed to every callback. You can share data using it.
 * @param[in] op	Observed change in path. XMLDIFF_OP type.
 * @param[in] old_node	Old configuration node. If op == XMLDIFF_ADD, it is NULL.
 * @param[in] new_node	New configuration node. if op == XMLDIFF_REM, it is NULL.
 * @param[out] error	If callback fails, it can return libnetconf error structure with a failure description.
 *
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
/* !DO NOT ALTER FUNCTION SIGNATURE! */
int callback_ss_sshd_config_options_ss_PrintMotd(void **data, XMLDIFF_OP op, xmlNodePtr old_node, xmlNodePtr new_node, struct nc_err **error) {
	return EXIT_SUCCESS;
}

/**
 * @brief This callback will be run when node in path /ss:sshd_config_options/ss:Protocol changes
 *
 * @param[in] data	Double pointer to void. Its passed to every callback. You can share data using it.
 * @param[in] op	Observed change in path. XMLDIFF_OP type.
 * @param[in] old_node	Old configuration node. If op == XMLDIFF_ADD, it is NULL.
 * @param[in] new_node	New configuration node. if op == XMLDIFF_REM, it is NULL.
 * @param[out] error	If callback fails, it can return libnetconf error structure with a failure description.
 *
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
/* !DO NOT ALTER FUNCTION SIGNATURE! */
int callback_ss_sshd_config_options_ss_Protocol(void **data, XMLDIFF_OP op, xmlNodePtr old_node, xmlNodePtr new_node, struct nc_err **error) {
	return EXIT_SUCCESS;
}

/**
 * @brief This callback will be run when node in path /ss:sshd_config_options/ss:PubkeyAuthentication changes
 *
 * @param[in] data	Double pointer to void. Its passed to every callback. You can share data using it.
 * @param[in] op	Observed change in path. XMLDIFF_OP type.
 * @param[in] old_node	Old configuration node. If op == XMLDIFF_ADD, it is NULL.
 * @param[in] new_node	New configuration node. if op == XMLDIFF_REM, it is NULL.
 * @param[out] error	If callback fails, it can return libnetconf error structure with a failure description.
 *
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
/* !DO NOT ALTER FUNCTION SIGNATURE! */
int callback_ss_sshd_config_options_ss_PubkeyAuthentication(void **data, XMLDIFF_OP op, xmlNodePtr old_node, xmlNodePtr new_node, struct nc_err **error) {
	return EXIT_SUCCESS;
}

/**
 * @brief This callback will be run when node in path /ss:sshd_config_options/ss:RekeyLimit changes
 *
 * @param[in] data	Double pointer to void. Its passed to every callback. You can share data using it.
 * @param[in] op	Observed change in path. XMLDIFF_OP type.
 * @param[in] old_node	Old configuration node. If op == XMLDIFF_ADD, it is NULL.
 * @param[in] new_node	New configuration node. if op == XMLDIFF_REM, it is NULL.
 * @param[out] error	If callback fails, it can return libnetconf error structure with a failure description.
 *
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
/* !DO NOT ALTER FUNCTION SIGNATURE! */
int callback_ss_sshd_config_options_ss_RekeyLimit(void **data, XMLDIFF_OP op, xmlNodePtr old_node, xmlNodePtr new_node, struct nc_err **error) {
	return EXIT_SUCCESS;
}

/**
 * @brief This callback will be run when node in path /ss:sshd_config_options/ss:RevokedKeys changes
 *
 * @param[in] data	Double pointer to void. Its passed to every callback. You can share data using it.
 * @param[in] op	Observed change in path. XMLDIFF_OP type.
 * @param[in] old_node	Old configuration node. If op == XMLDIFF_ADD, it is NULL.
 * @param[in] new_node	New configuration node. if op == XMLDIFF_REM, it is NULL.
 * @param[out] error	If callback fails, it can return libnetconf error structure with a failure description.
 *
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
/* !DO NOT ALTER FUNCTION SIGNATURE! */
int callback_ss_sshd_config_options_ss_RevokedKeys(void **data, XMLDIFF_OP op, xmlNodePtr old_node, xmlNodePtr new_node, struct nc_err **error) {
	return EXIT_SUCCESS;
}

/**
 * @brief This callback will be run when node in path /ss:sshd_config_options/ss:RhostsRSAAuthentication changes
 *
 * @param[in] data	Double pointer to void. Its passed to every callback. You can share data using it.
 * @param[in] op	Observed change in path. XMLDIFF_OP type.
 * @param[in] old_node	Old configuration node. If op == XMLDIFF_ADD, it is NULL.
 * @param[in] new_node	New configuration node. if op == XMLDIFF_REM, it is NULL.
 * @param[out] error	If callback fails, it can return libnetconf error structure with a failure description.
 *
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
/* !DO NOT ALTER FUNCTION SIGNATURE! */
int callback_ss_sshd_config_options_ss_RhostsRSAAuthentication(void **data, XMLDIFF_OP op, xmlNodePtr old_node, xmlNodePtr new_node, struct nc_err **error) {
	return EXIT_SUCCESS;
}

/**
 * @brief This callback will be run when node in path /ss:sshd_config_options/ss:RSAAuthentication changes
 *
 * @param[in] data	Double pointer to void. Its passed to every callback. You can share data using it.
 * @param[in] op	Observed change in path. XMLDIFF_OP type.
 * @param[in] old_node	Old configuration node. If op == XMLDIFF_ADD, it is NULL.
 * @param[in] new_node	New configuration node. if op == XMLDIFF_REM, it is NULL.
 * @param[out] error	If callback fails, it can return libnetconf error structure with a failure description.
 *
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
/* !DO NOT ALTER FUNCTION SIGNATURE! */
int callback_ss_sshd_config_options_ss_RSAAuthentication(void **data, XMLDIFF_OP op, xmlNodePtr old_node, xmlNodePtr new_node, struct nc_err **error) {
	return EXIT_SUCCESS;
}

/**
 * @brief This callback will be run when node in path /ss:sshd_config_options/ss:ServerKeyBits changes
 *
 * @param[in] data	Double pointer to void. Its passed to every callback. You can share data using it.
 * @param[in] op	Observed change in path. XMLDIFF_OP type.
 * @param[in] old_node	Old configuration node. If op == XMLDIFF_ADD, it is NULL.
 * @param[in] new_node	New configuration node. if op == XMLDIFF_REM, it is NULL.
 * @param[out] error	If callback fails, it can return libnetconf error structure with a failure description.
 *
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
/* !DO NOT ALTER FUNCTION SIGNATURE! */
int callback_ss_sshd_config_options_ss_ServerKeyBits(void **data, XMLDIFF_OP op, xmlNodePtr old_node, xmlNodePtr new_node, struct nc_err **error) {
	return EXIT_SUCCESS;
}

/**
 * @brief This callback will be run when node in path /ss:sshd_config_options/ss:StrictModes changes
 *
 * @param[in] data	Double pointer to void. Its passed to every callback. You can share data using it.
 * @param[in] op	Observed change in path. XMLDIFF_OP type.
 * @param[in] old_node	Old configuration node. If op == XMLDIFF_ADD, it is NULL.
 * @param[in] new_node	New configuration node. if op == XMLDIFF_REM, it is NULL.
 * @param[out] error	If callback fails, it can return libnetconf error structure with a failure description.
 *
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
/* !DO NOT ALTER FUNCTION SIGNATURE! */
int callback_ss_sshd_config_options_ss_StrictModes(void **data, XMLDIFF_OP op, xmlNodePtr old_node, xmlNodePtr new_node, struct nc_err **error) {
	return EXIT_SUCCESS;
}

/**
 * @brief This callback will be run when node in path /ss:sshd_config_options/ss:Subsystem changes
 *
 * @param[in] data	Double pointer to void. Its passed to every callback. You can share data using it.
 * @param[in] op	Observed change in path. XMLDIFF_OP type.
 * @param[in] old_node	Old configuration node. If op == XMLDIFF_ADD, it is NULL.
 * @param[in] new_node	New configuration node. if op == XMLDIFF_REM, it is NULL.
 * @param[out] error	If callback fails, it can return libnetconf error structure with a failure description.
 *
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
/* !DO NOT ALTER FUNCTION SIGNATURE! */
int callback_ss_sshd_config_options_ss_Subsystem(void **data, XMLDIFF_OP op, xmlNodePtr old_node, xmlNodePtr new_node, struct nc_err **error) {
	return EXIT_SUCCESS;
}

/**
 * @brief This callback will be run when node in path /ss:sshd_config_options/ss:SyslogFacility changes
 *
 * @param[in] data	Double pointer to void. Its passed to every callback. You can share data using it.
 * @param[in] op	Observed change in path. XMLDIFF_OP type.
 * @param[in] old_node	Old configuration node. If op == XMLDIFF_ADD, it is NULL.
 * @param[in] new_node	New configuration node. if op == XMLDIFF_REM, it is NULL.
 * @param[out] error	If callback fails, it can return libnetconf error structure with a failure description.
 *
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
/* !DO NOT ALTER FUNCTION SIGNATURE! */
int callback_ss_sshd_config_options_ss_SyslogFacility(void **data, XMLDIFF_OP op, xmlNodePtr old_node, xmlNodePtr new_node, struct nc_err **error) {
	return EXIT_SUCCESS;
}

/**
 * @brief This callback will be run when node in path /ss:sshd_config_options/ss:TCPKeepAlive changes
 *
 * @param[in] data	Double pointer to void. Its passed to every callback. You can share data using it.
 * @param[in] op	Observed change in path. XMLDIFF_OP type.
 * @param[in] old_node	Old configuration node. If op == XMLDIFF_ADD, it is NULL.
 * @param[in] new_node	New configuration node. if op == XMLDIFF_REM, it is NULL.
 * @param[out] error	If callback fails, it can return libnetconf error structure with a failure description.
 *
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
/* !DO NOT ALTER FUNCTION SIGNATURE! */
int callback_ss_sshd_config_options_ss_TCPKeepAlive(void **data, XMLDIFF_OP op, xmlNodePtr old_node, xmlNodePtr new_node, struct nc_err **error) {
	return EXIT_SUCCESS;
}

/**
 * @brief This callback will be run when node in path /ss:sshd_config_options/ss:TrustedUserCAKeys changes
 *
 * @param[in] data	Double pointer to void. Its passed to every callback. You can share data using it.
 * @param[in] op	Observed change in path. XMLDIFF_OP type.
 * @param[in] old_node	Old configuration node. If op == XMLDIFF_ADD, it is NULL.
 * @param[in] new_node	New configuration node. if op == XMLDIFF_REM, it is NULL.
 * @param[out] error	If callback fails, it can return libnetconf error structure with a failure description.
 *
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
/* !DO NOT ALTER FUNCTION SIGNATURE! */
int callback_ss_sshd_config_options_ss_TrustedUserCAKeys(void **data, XMLDIFF_OP op, xmlNodePtr old_node, xmlNodePtr new_node, struct nc_err **error) {
	return EXIT_SUCCESS;
}

/**
 * @brief This callback will be run when node in path /ss:sshd_config_options/ss:UseDNS changes
 *
 * @param[in] data	Double pointer to void. Its passed to every callback. You can share data using it.
 * @param[in] op	Observed change in path. XMLDIFF_OP type.
 * @param[in] old_node	Old configuration node. If op == XMLDIFF_ADD, it is NULL.
 * @param[in] new_node	New configuration node. if op == XMLDIFF_REM, it is NULL.
 * @param[out] error	If callback fails, it can return libnetconf error structure with a failure description.
 *
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
/* !DO NOT ALTER FUNCTION SIGNATURE! */
int callback_ss_sshd_config_options_ss_UseDNS(void **data, XMLDIFF_OP op, xmlNodePtr old_node, xmlNodePtr new_node, struct nc_err **error) {
	return EXIT_SUCCESS;
}

/**
 * @brief This callback will be run when node in path /ss:sshd_config_options/ss:UseLogin changes
 *
 * @param[in] data	Double pointer to void. Its passed to every callback. You can share data using it.
 * @param[in] op	Observed change in path. XMLDIFF_OP type.
 * @param[in] old_node	Old configuration node. If op == XMLDIFF_ADD, it is NULL.
 * @param[in] new_node	New configuration node. if op == XMLDIFF_REM, it is NULL.
 * @param[out] error	If callback fails, it can return libnetconf error structure with a failure description.
 *
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
/* !DO NOT ALTER FUNCTION SIGNATURE! */
int callback_ss_sshd_config_options_ss_UseLogin(void **data, XMLDIFF_OP op, xmlNodePtr old_node, xmlNodePtr new_node, struct nc_err **error) {
	return EXIT_SUCCESS;
}

/**
 * @brief This callback will be run when node in path /ss:sshd_config_options/ss:UsePAM changes
 *
 * @param[in] data	Double pointer to void. Its passed to every callback. You can share data using it.
 * @param[in] op	Observed change in path. XMLDIFF_OP type.
 * @param[in] old_node	Old configuration node. If op == XMLDIFF_ADD, it is NULL.
 * @param[in] new_node	New configuration node. if op == XMLDIFF_REM, it is NULL.
 * @param[out] error	If callback fails, it can return libnetconf error structure with a failure description.
 *
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
/* !DO NOT ALTER FUNCTION SIGNATURE! */
int callback_ss_sshd_config_options_ss_UsePAM(void **data, XMLDIFF_OP op, xmlNodePtr old_node, xmlNodePtr new_node, struct nc_err **error) {
	return EXIT_SUCCESS;
}

/**
 * @brief This callback will be run when node in path /ss:sshd_config_options/ss:UsePrivilegeSeparation changes
 *
 * @param[in] data	Double pointer to void. Its passed to every callback. You can share data using it.
 * @param[in] op	Observed change in path. XMLDIFF_OP type.
 * @param[in] old_node	Old configuration node. If op == XMLDIFF_ADD, it is NULL.
 * @param[in] new_node	New configuration node. if op == XMLDIFF_REM, it is NULL.
 * @param[out] error	If callback fails, it can return libnetconf error structure with a failure description.
 *
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
/* !DO NOT ALTER FUNCTION SIGNATURE! */
int callback_ss_sshd_config_options_ss_UsePrivilegeSeparation(void **data, XMLDIFF_OP op, xmlNodePtr old_node, xmlNodePtr new_node, struct nc_err **error) {
	return EXIT_SUCCESS;
}

/**
 * @brief This callback will be run when node in path /ss:sshd_config_options/ss:VersionAddendum changes
 *
 * @param[in] data	Double pointer to void. Its passed to every callback. You can share data using it.
 * @param[in] op	Observed change in path. XMLDIFF_OP type.
 * @param[in] old_node	Old configuration node. If op == XMLDIFF_ADD, it is NULL.
 * @param[in] new_node	New configuration node. if op == XMLDIFF_REM, it is NULL.
 * @param[out] error	If callback fails, it can return libnetconf error structure with a failure description.
 *
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
/* !DO NOT ALTER FUNCTION SIGNATURE! */
int callback_ss_sshd_config_options_ss_VersionAddendum(void **data, XMLDIFF_OP op, xmlNodePtr old_node, xmlNodePtr new_node, struct nc_err **error) {
	return EXIT_SUCCESS;
}

/**
 * @brief This callback will be run when node in path /ss:sshd_config_options/ss:X11DisplayOffset changes
 *
 * @param[in] data	Double pointer to void. Its passed to every callback. You can share data using it.
 * @param[in] op	Observed change in path. XMLDIFF_OP type.
 * @param[in] old_node	Old configuration node. If op == XMLDIFF_ADD, it is NULL.
 * @param[in] new_node	New configuration node. if op == XMLDIFF_REM, it is NULL.
 * @param[out] error	If callback fails, it can return libnetconf error structure with a failure description.
 *
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
/* !DO NOT ALTER FUNCTION SIGNATURE! */
int callback_ss_sshd_config_options_ss_X11DisplayOffset(void **data, XMLDIFF_OP op, xmlNodePtr old_node, xmlNodePtr new_node, struct nc_err **error) {
	return EXIT_SUCCESS;
}

/**
 * @brief This callback will be run when node in path /ss:sshd_config_options/ss:X11Forwarding changes
 *
 * @param[in] data	Double pointer to void. Its passed to every callback. You can share data using it.
 * @param[in] op	Observed change in path. XMLDIFF_OP type.
 * @param[in] old_node	Old configuration node. If op == XMLDIFF_ADD, it is NULL.
 * @param[in] new_node	New configuration node. if op == XMLDIFF_REM, it is NULL.
 * @param[out] error	If callback fails, it can return libnetconf error structure with a failure description.
 *
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
/* !DO NOT ALTER FUNCTION SIGNATURE! */
int callback_ss_sshd_config_options_ss_X11Forwarding(void **data, XMLDIFF_OP op, xmlNodePtr old_node, xmlNodePtr new_node, struct nc_err **error) {
	return EXIT_SUCCESS;
}

/**
 * @brief This callback will be run when node in path /ss:sshd_config_options/ss:X11UseLocalhost changes
 *
 * @param[in] data	Double pointer to void. Its passed to every callback. You can share data using it.
 * @param[in] op	Observed change in path. XMLDIFF_OP type.
 * @param[in] old_node	Old configuration node. If op == XMLDIFF_ADD, it is NULL.
 * @param[in] new_node	New configuration node. if op == XMLDIFF_REM, it is NULL.
 * @param[out] error	If callback fails, it can return libnetconf error structure with a failure description.
 *
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
/* !DO NOT ALTER FUNCTION SIGNATURE! */
int callback_ss_sshd_config_options_ss_X11UseLocalhost(void **data, XMLDIFF_OP op, xmlNodePtr old_node, xmlNodePtr new_node, struct nc_err **error) {
	return EXIT_SUCCESS;
}

/**
 * @brief This callback will be run when node in path /ss:sshd_config_options/ss:XAuthLocation changes
 *
 * @param[in] data	Double pointer to void. Its passed to every callback. You can share data using it.
 * @param[in] op	Observed change in path. XMLDIFF_OP type.
 * @param[in] old_node	Old configuration node. If op == XMLDIFF_ADD, it is NULL.
 * @param[in] new_node	New configuration node. if op == XMLDIFF_REM, it is NULL.
 * @param[out] error	If callback fails, it can return libnetconf error structure with a failure description.
 *
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
/* !DO NOT ALTER FUNCTION SIGNATURE! */
int callback_ss_sshd_config_options_ss_XAuthLocation(void **data, XMLDIFF_OP op, xmlNodePtr old_node, xmlNodePtr new_node, struct nc_err **error) {
	return EXIT_SUCCESS;
}

/*
 * Structure transapi_config_callbacks provide mapping between callback and path in configuration datastore.
 * It is used by libnetconf library to decide which callbacks will be run.
 * DO NOT alter this structure
 */
struct transapi_data_callbacks sshdc_clbks =  {
	.callbacks_count = 84,
	.data = NULL,
	.callbacks = {
		{.path = "/ss:sshd_config_options/ss:AcceptEnv", .func = callback_ss_sshd_config_options_ss_AcceptEnv},
		{.path = "/ss:sshd_config_options/ss:AddressFamily", .func = callback_ss_sshd_config_options_ss_AddressFamily},
		{.path = "/ss:sshd_config_options/ss:AllowAgentForwarding", .func = callback_ss_sshd_config_options_ss_AllowAgentForwarding},
		{.path = "/ss:sshd_config_options/ss:AllowGroups", .func = callback_ss_sshd_config_options_ss_AllowGroups},
		{.path = "/ss:sshd_config_options/ss:AllowTcpForwarding", .func = callback_ss_sshd_config_options_ss_AllowTcpForwarding},
		{.path = "/ss:sshd_config_options/ss:AllowUsers", .func = callback_ss_sshd_config_options_ss_AllowUsers},
		{.path = "/ss:sshd_config_options/ss:AuthenticationMethods", .func = callback_ss_sshd_config_options_ss_AuthenticationMethods},
		{.path = "/ss:sshd_config_options/ss:AuthorizedKeysCommand", .func = callback_ss_sshd_config_options_ss_AuthorizedKeysCommand},
		{.path = "/ss:sshd_config_options/ss:AuthorizedKeysCommandUser", .func = callback_ss_sshd_config_options_ss_AuthorizedKeysCommandUser},
		{.path = "/ss:sshd_config_options/ss:AuthorizedKeysFile", .func = callback_ss_sshd_config_options_ss_AuthorizedKeysFile},
		{.path = "/ss:sshd_config_options/ss:AuthorizedPrincipalsFile", .func = callback_ss_sshd_config_options_ss_AuthorizedPrincipalsFile},
		{.path = "/ss:sshd_config_options/ss:Banner", .func = callback_ss_sshd_config_options_ss_Banner},
		{.path = "/ss:sshd_config_options/ss:ChallengeResponseAuthentication", .func = callback_ss_sshd_config_options_ss_ChallengeResponseAuthentication},
		{.path = "/ss:sshd_config_options/ss:ChrootDirectory", .func = callback_ss_sshd_config_options_ss_ChrootDirectory},
		{.path = "/ss:sshd_config_options/ss:Ciphers", .func = callback_ss_sshd_config_options_ss_Ciphers},
		{.path = "/ss:sshd_config_options/ss:ClientAliveCountMax", .func = callback_ss_sshd_config_options_ss_ClientAliveCountMax},
		{.path = "/ss:sshd_config_options/ss:ClientAliveInterval", .func = callback_ss_sshd_config_options_ss_ClientAliveInterval},
		{.path = "/ss:sshd_config_options/ss:Compression", .func = callback_ss_sshd_config_options_ss_Compression},
		{.path = "/ss:sshd_config_options/ss:DebianBanner", .func = callback_ss_sshd_config_options_ss_DebianBanner},
		{.path = "/ss:sshd_config_options/ss:DenyGroups", .func = callback_ss_sshd_config_options_ss_DenyGroups},
		{.path = "/ss:sshd_config_options/ss:DenyUsers", .func = callback_ss_sshd_config_options_ss_DenyUsers},
		{.path = "/ss:sshd_config_options/ss:ForceCommand", .func = callback_ss_sshd_config_options_ss_ForceCommand},
		{.path = "/ss:sshd_config_options/ss:GatewayPorts", .func = callback_ss_sshd_config_options_ss_GatewayPorts},
		{.path = "/ss:sshd_config_options/ss:GSSAPIAuthentication", .func = callback_ss_sshd_config_options_ss_GSSAPIAuthentication},
		{.path = "/ss:sshd_config_options/ss:GSSAPIKeyExchange", .func = callback_ss_sshd_config_options_ss_GSSAPIKeyExchange},
		{.path = "/ss:sshd_config_options/ss:GSSAPICleanupCredentials", .func = callback_ss_sshd_config_options_ss_GSSAPICleanupCredentials},
		{.path = "/ss:sshd_config_options/ss:GSSAPIStrictAcceptorCheck", .func = callback_ss_sshd_config_options_ss_GSSAPIStrictAcceptorCheck},
		{.path = "/ss:sshd_config_options/ss:GSSAPIStoreCredentialsOnRekey", .func = callback_ss_sshd_config_options_ss_GSSAPIStoreCredentialsOnRekey},
		{.path = "/ss:sshd_config_options/ss:HostbasedAuthentication", .func = callback_ss_sshd_config_options_ss_HostbasedAuthentication},
		{.path = "/ss:sshd_config_options/ss:HostbasedUsesNameFromPacketOnly", .func = callback_ss_sshd_config_options_ss_HostbasedUsesNameFromPacketOnly},
		{.path = "/ss:sshd_config_options/ss:HostCertificate", .func = callback_ss_sshd_config_options_ss_HostCertificate},
		{.path = "/ss:sshd_config_options/ss:HostKey", .func = callback_ss_sshd_config_options_ss_HostKey},
		{.path = "/ss:sshd_config_options/ss:HostKeyAgent", .func = callback_ss_sshd_config_options_ss_HostKeyAgent},
		{.path = "/ss:sshd_config_options/ss:IgnoreRhosts", .func = callback_ss_sshd_config_options_ss_IgnoreRhosts},
		{.path = "/ss:sshd_config_options/ss:IgnoreUserKnownHosts", .func = callback_ss_sshd_config_options_ss_IgnoreUserKnownHosts},
		{.path = "/ss:sshd_config_options/ss:IPQoS", .func = callback_ss_sshd_config_options_ss_IPQoS},
		{.path = "/ss:sshd_config_options/ss:KbdInteractiveAuthentication", .func = callback_ss_sshd_config_options_ss_KbdInteractiveAuthentication},
		{.path = "/ss:sshd_config_options/ss:KerberosAuthentication", .func = callback_ss_sshd_config_options_ss_KerberosAuthentication},
		{.path = "/ss:sshd_config_options/ss:KerberosGetAFSToken", .func = callback_ss_sshd_config_options_ss_KerberosGetAFSToken},
		{.path = "/ss:sshd_config_options/ss:KerberosOrLocalPasswd", .func = callback_ss_sshd_config_options_ss_KerberosOrLocalPasswd},
		{.path = "/ss:sshd_config_options/ss:KerberosTicketCleanup", .func = callback_ss_sshd_config_options_ss_KerberosTicketCleanup},
		{.path = "/ss:sshd_config_options/ss:KexAlgorithms", .func = callback_ss_sshd_config_options_ss_KexAlgorithms},
		{.path = "/ss:sshd_config_options/ss:KeyRegenerationInterval", .func = callback_ss_sshd_config_options_ss_KeyRegenerationInterval},
		{.path = "/ss:sshd_config_options/ss:ListenAddress", .func = callback_ss_sshd_config_options_ss_ListenAddress},
		{.path = "/ss:sshd_config_options/ss:LoginGraceTime", .func = callback_ss_sshd_config_options_ss_LoginGraceTime},
		{.path = "/ss:sshd_config_options/ss:LogLevel", .func = callback_ss_sshd_config_options_ss_LogLevel},
		{.path = "/ss:sshd_config_options/ss:MACs", .func = callback_ss_sshd_config_options_ss_MACs},
		{.path = "/ss:sshd_config_options/ss:Match", .func = callback_ss_sshd_config_options_ss_Match},
		{.path = "/ss:sshd_config_options/ss:MaxAuthTries", .func = callback_ss_sshd_config_options_ss_MaxAuthTries},
		{.path = "/ss:sshd_config_options/ss:MaxSessions", .func = callback_ss_sshd_config_options_ss_MaxSessions},
		{.path = "/ss:sshd_config_options/ss:MaxStartups", .func = callback_ss_sshd_config_options_ss_MaxStartups},
		{.path = "/ss:sshd_config_options/ss:OS", .func = callback_ss_sshd_config_options_ss_OS},
		{.path = "/ss:sshd_config_options/ss:PasswordAuthentication", .func = callback_ss_sshd_config_options_ss_PasswordAuthentication},
		{.path = "/ss:sshd_config_options/ss:PermitEmptyPasswords", .func = callback_ss_sshd_config_options_ss_PermitEmptyPasswords},
		{.path = "/ss:sshd_config_options/ss:PermitOpen", .func = callback_ss_sshd_config_options_ss_PermitOpen},
		{.path = "/ss:sshd_config_options/ss:PermitRootLogin", .func = callback_ss_sshd_config_options_ss_PermitRootLogin},
		{.path = "/ss:sshd_config_options/ss:PermitTunnel", .func = callback_ss_sshd_config_options_ss_PermitTunnel},
		{.path = "/ss:sshd_config_options/ss:PermitTTY", .func = callback_ss_sshd_config_options_ss_PermitTTY},
		{.path = "/ss:sshd_config_options/ss:PermitUserEnvironment", .func = callback_ss_sshd_config_options_ss_PermitUserEnvironment},
		{.path = "/ss:sshd_config_options/ss:PidFile", .func = callback_ss_sshd_config_options_ss_PidFile},
		{.path = "/ss:sshd_config_options/ss:Port", .func = callback_ss_sshd_config_options_ss_Port},
		{.path = "/ss:sshd_config_options/ss:PrintLastLog", .func = callback_ss_sshd_config_options_ss_PrintLastLog},
		{.path = "/ss:sshd_config_options/ss:PrintMotd", .func = callback_ss_sshd_config_options_ss_PrintMotd},
		{.path = "/ss:sshd_config_options/ss:Protocol", .func = callback_ss_sshd_config_options_ss_Protocol},
		{.path = "/ss:sshd_config_options/ss:PubkeyAuthentication", .func = callback_ss_sshd_config_options_ss_PubkeyAuthentication},
		{.path = "/ss:sshd_config_options/ss:RekeyLimit", .func = callback_ss_sshd_config_options_ss_RekeyLimit},
		{.path = "/ss:sshd_config_options/ss:RevokedKeys", .func = callback_ss_sshd_config_options_ss_RevokedKeys},
		{.path = "/ss:sshd_config_options/ss:RhostsRSAAuthentication", .func = callback_ss_sshd_config_options_ss_RhostsRSAAuthentication},
		{.path = "/ss:sshd_config_options/ss:RSAAuthentication", .func = callback_ss_sshd_config_options_ss_RSAAuthentication},
		{.path = "/ss:sshd_config_options/ss:ServerKeyBits", .func = callback_ss_sshd_config_options_ss_ServerKeyBits},
		{.path = "/ss:sshd_config_options/ss:StrictModes", .func = callback_ss_sshd_config_options_ss_StrictModes},
		{.path = "/ss:sshd_config_options/ss:Subsystem", .func = callback_ss_sshd_config_options_ss_Subsystem},
		{.path = "/ss:sshd_config_options/ss:SyslogFacility", .func = callback_ss_sshd_config_options_ss_SyslogFacility},
		{.path = "/ss:sshd_config_options/ss:TCPKeepAlive", .func = callback_ss_sshd_config_options_ss_TCPKeepAlive},
		{.path = "/ss:sshd_config_options/ss:TrustedUserCAKeys", .func = callback_ss_sshd_config_options_ss_TrustedUserCAKeys},
		{.path = "/ss:sshd_config_options/ss:UseDNS", .func = callback_ss_sshd_config_options_ss_UseDNS},
		{.path = "/ss:sshd_config_options/ss:UseLogin", .func = callback_ss_sshd_config_options_ss_UseLogin},
		{.path = "/ss:sshd_config_options/ss:UsePAM", .func = callback_ss_sshd_config_options_ss_UsePAM},
		{.path = "/ss:sshd_config_options/ss:UsePrivilegeSeparation", .func = callback_ss_sshd_config_options_ss_UsePrivilegeSeparation},
		{.path = "/ss:sshd_config_options/ss:VersionAddendum", .func = callback_ss_sshd_config_options_ss_VersionAddendum},
		{.path = "/ss:sshd_config_options/ss:X11DisplayOffset", .func = callback_ss_sshd_config_options_ss_X11DisplayOffset},
		{.path = "/ss:sshd_config_options/ss:X11Forwarding", .func = callback_ss_sshd_config_options_ss_X11Forwarding},
		{.path = "/ss:sshd_config_options/ss:X11UseLocalhost", .func = callback_ss_sshd_config_options_ss_X11UseLocalhost},
		{.path = "/ss:sshd_config_options/ss:XAuthLocation", .func = callback_ss_sshd_config_options_ss_XAuthLocation}
	}
};

/*
 * RPC callbacks
 * Here follows set of callback functions run every time RPC specific for this device arrives.
 * You can safely modify the bodies of all function as well as add new functions for better lucidity of code.
 * Every function takes an libxml2 list of inputs as an argument.
 * If input was not set in RPC message argument is set to NULL. To retrieve each argument, preferably use get_rpc_node().
 */

/*
 * Structure transapi_rpc_callbacks provides mapping between callbacks and RPC messages.
 * It is used by libnetconf library to decide which callbacks will be run when RPC arrives.
 * DO NOT alter this structure
 */
struct transapi_rpc_callbacks sshdc_rpc_clbks = {
	.callbacks_count = 0,
	.callbacks = {
	}
};

/* overall structure providing content of this module to the libnetconf */
struct transapi sshdc_transapi = {
    .version = 6,
    .init = sshdc_transapi_init,
    .close = sshdc_transapi_close,
    .get_state = sshdc_get_state_data,
    .clbks_order = TRANSAPI_CLBCKS_ORDER_DEFAULT,
    .data_clbks = &sshdc_clbks,
    .rpc_clbks = &sshdc_rpc_clbks,
    .ns_mapping = sshdc_namespace_mapping,
    .config_modified = &sshdc_config_modified,
    .erropt = &sshdc_erropt,
    .file_clbks = NULL
};
