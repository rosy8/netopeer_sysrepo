#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include <srd.h>

#define MSGLENFIELDWIDTH 7
#define NP_SYSREPO_IFC_DS "urn:ietf:params:xml:ns:yang:ietf-interfaces"

void createListeningSocket(int* listenfd, int myPort) {
	const int optVal = 1;
	const socklen_t optLen = sizeof(optVal);
	int sock;
	struct sockaddr_in servaddr;

	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == -1) {
		printf("Error in creating listening socket.\n");
		*listenfd = -1;
	} else {
		if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (void*)&optVal, optLen) != 0) {
			printf("Could not set socket SO_REUSEADDR option (%s).\n", strerror(errno));
			*listenfd = -1;
			return;
		}

		bzero(&servaddr, sizeof(servaddr));
		servaddr.sin_family = AF_INET;
		servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
		servaddr.sin_port = htons(myPort);
		if (bind(sock, (struct sockaddr*)&servaddr, sizeof(servaddr))) {
			printf("Fatal Error: Could not bind to the server port %d. May be it is in use or in TIME_WAIT state.\n", myPort);
			printf("Use 'netstat -nap | grep %d' command to see its status.\n", myPort);
			*listenfd = -1;
		} else {
			*listenfd = sock;
		}
	}
}

int acceptClients(int listenfd) {
   int iResult;
   fd_set rfds;
   int s;

   FD_ZERO(&rfds);
   FD_SET(listenfd, &rfds);
   iResult = select(listenfd+1, &rfds, (fd_set *) 0, (fd_set *) 0, NULL); // Last param == NULL means No Timeout
   if (iResult > 0) {
      s =  accept(listenfd, NULL, NULL);
      return s;
   } else {
      return -1; // error
   }
}

void signal_handler(int sig) {
	switch (sig) {
	case SIGHUP:
		printf("SIGHUP received\n");
		break;
	default:
		exit(EXIT_FAILURE);
		break;
	}
}

int main(void) {
	struct sigaction action;
	sigset_t block_mask;

	sigfillset(&block_mask);
	action.sa_handler = signal_handler;
	action.sa_mask = block_mask;
	action.sa_flags = 0;
	sigaction(SIGHUP, &action, NULL);

	int sockfd, n;
	char ds_xml[3000];
	xmlDocPtr ds_doc;
	char sendline[1000];
	char xpath[100];
	char *buffPtr = NULL, *ds_list = NULL;
	int buffSize = 100;

	if (!srd_connect("127.0.0.1", 3500, &sockfd)){
		printf("Error in connecting to server 127.0.0.1 at port 3500\n");
		return EXIT_FAILURE;
	}

	/* add and use OpDatastore */
	if (!srd_listOpDataStores(sockfd, &ds_list)) {
		printf("Failed to get sysrepo datastores\n");
		srd_disconnect(sockfd);
		return EXIT_FAILURE;
	}

	if (strstr(ds_list, NP_SYSREPO_IFC_DS "/interfaces-state") == NULL) {
		if (srd_createOpDataStore(sockfd, NP_SYSREPO_IFC_DS "/interfaces-state") != 1) {
			printf("Failed to create a datastore\n");
			srd_disconnect(sockfd);
			return EXIT_FAILURE;
		}
	}
	free(ds_list);

	if (srd_useOpDataStore(sockfd, NP_SYSREPO_IFC_DS "/interfaces-state") != 1) {
		printf("Failed to use %s datastore\n", NP_SYSREPO_IFC_DS "/interfaces-state");
		srd_disconnect(sockfd);
		return EXIT_FAILURE;
	}

	/* add and use Datastore */
	if (!srd_listDataStores(sockfd, &ds_list)) {
		printf("Failed to get sysrepo datastores\n");
		srd_disconnect(sockfd);
		return EXIT_FAILURE;
	}

	if (strstr(ds_list, NP_SYSREPO_IFC_DS "/interfaces") == NULL) {
		if (srd_createDataStore(sockfd, NP_SYSREPO_IFC_DS "/interfaces", "<data xmlns=\"urn:ietf:params:xml:ns:netconf:base:1.0\"><interfaces xmlns=\"urn:ietf:params:xml:ns:yang:ietf-interfaces\"/></data>", CHECK_DIR, CHECK_DIR) != 1) {
			printf("Failed to create a datastore\n");
			srd_disconnect(sockfd);
			return EXIT_FAILURE;
		}
	}
	free(ds_list);

	if (srd_setDataStore(sockfd, NP_SYSREPO_IFC_DS "/interfaces") != 1) {
		printf("Failed to use %s datastore\n", NP_SYSREPO_IFC_DS "/interfaces");
		srd_disconnect(sockfd);
		return EXIT_FAILURE;
	}

	strcpy(ds_xml, "<?xml version=\"1.0\" encoding=\"utf-8\"?><state xmlns=\"urn:ietf:params:xml:ns:netconf:base:1.0\"><interfaces-state xmlns=\"urn:ietf:params:xml:ns:yang:ietf-interfaces\"><interface><name></name><type></type><admin-status></admin-status><oper-status></oper-status><last-change></last-change><if-index></if-index><phys-address></phys-address><higher-layer-if></higher-layer-if><lower-layer-if></lower-layer-if><speed></speed><statistics><discontinuity-time></discontinuity-time><in-octets></in-octets><in-unicast-pkts></in-unicast-pkts><in-broadcast-pkts></in-broadcast-pkts> <in-multicast-pkts></in-multicast-pkts><in-discards></in-discards> <in-errors></in-errors> <in-unknown-protos></in-unknown-protos> <out-octets></out-octets> <out-unicast-pkts></out-unicast-pkts> <out-broadcast-pkts></out-broadcast-pkts> <out-multicast-pkts></out-multicast-pkts> <out-discards></out-discards> <out-errors/> </statistics> </interface> </interfaces-state> </state>");
	ds_doc = xmlReadMemory(ds_xml, strlen(ds_xml), "noname.xml", NULL, 0);
	if (ds_doc == NULL) {
		printf("Local error: Failed to make DOM for my Op Data Store.\n");
		srd_disconnect(sockfd);
		return EXIT_FAILURE;
	}

	printf("Waiting for requests.....\n");
	fflush(stdout);

	if (!srd_registerClientSignal(sockfd, getpid(), SIGHUP)) {
		printf("Failed to register signal on datastore.\n");
		srd_disconnect(sockfd);
		return EXIT_FAILURE;
	}

	// Need to give a socket to the SysrepoD on which this daemon will be listening on to receive Op Data Store related commands.
	char myIPAddress[100] = "127.0.0.1";
	int  myPort = 3510;
	int  listenfd, connfd;

	if (!srd_registerClientSocket (sockfd, myIPAddress, myPort)) { // register my socket info with SysrepoD
		printf ("Unable to tell SysrepoD about my listening port.\n");
		srd_disconnect(sockfd);
		xmlFreeDoc(ds_doc);
		return EXIT_FAILURE;
	}
	// Start listening for connection request on 'myPort'
	createListeningSocket(&listenfd, myPort);
	if (listenfd != -1) {
		printf("Listening on Port %d .....\n", myPort);
		listen(listenfd, SOMAXCONN); // SOMAXCONN defined by socket.h: Max # of clients
	} else {
		printf("Error in listening for connections.\n");
		srd_disconnect(sockfd);
		xmlFreeDoc(ds_doc);
		return EXIT_FAILURE;
	}

	while (1) {
		connfd = acceptClients(listenfd); // No Time out
		if (connfd > -1) {
			printf("Received a connection request.\n");
			fflush(stdout);
		} else {
			// error
			printf("Error in accepting a connection (%s).\n", strerror(errno));
			continue;
		}
		buffPtr = (char*)malloc(buffSize);
		if (buffPtr == NULL) {
			printf("Local error: unable to allocate memory.\n");
			srd_disconnect(sockfd);
			xmlFreeDoc(ds_doc);
			close(connfd);
			close(listenfd);
			return EXIT_FAILURE;
		}

		n = srd_recvServer(connfd, &buffPtr, &buffSize);
		if (n == 0){
			printf("Failed to receive data from sysrepod\n");
		} else {
			xmlDocPtr doc = NULL;
			xmlChar *command;
			xmlChar *param1, *param2;

			doc = xmlReadMemory(&(buffPtr[MSGLENFIELDWIDTH + 1]), strlen (&(buffPtr[MSGLENFIELDWIDTH + 1])), "noname.xml", NULL, 0);
			if (doc == NULL) {
					sprintf(sendline, "<xml><error>XML Document not correct</error></xml>");
					srd_sendServer(connfd, sendline, strlen (sendline));
			} else {
				strcpy((char*)xpath, "/xml/command");
				command = srd_getFirstNodeValue(doc, (xmlChar*)xpath);
				if (command == NULL) {
					sprintf(sendline, "<xml><error>No command found.</error></xml>");
					srd_sendServer(connfd, sendline, strlen(sendline));
				} else if (strcmp((char*)command, "apply_xpathOpDataStore") == 0) {
					// param1 contains Op Data Store Name, param2 contains XPath
					strcpy((char*)xpath, "/xml/param1");
					param1 = srd_getFirstNodeValue(doc, (xmlChar*)xpath);
					if (param1 == NULL) {
						sprintf(sendline, "<xml><error>Value for Op Data Store name not found</error></xml>");
						srd_sendServer(connfd, sendline, strlen(sendline));
					} else if (strcmp((char*)param1, NP_SYSREPO_IFC_DS "/interfaces-state") != 0) {
						sprintf(sendline, "<xml><error>Unknown Operational Data Store name: %s</error></xml>", (char*)param1);
						xmlFree(param1);
						srd_sendServer(connfd, sendline, strlen(sendline));
					} else {
						strcpy((char*)xpath, "/xml/param2");
						param2 = srd_getFirstNodeValue(doc, (xmlChar*)xpath);
						if (param2 == NULL) {
							sprintf(sendline, "<xml><error>XPath not found</error></xml>");
							srd_sendServer(connfd, sendline, strlen(sendline));
						} else {
							// apply xpath and return results back to sysrepod
							srd_DOMHandleXPath(connfd, ds_doc, param2);
							xmlFree(param2);
						}
						xmlFree(param1);
					}
					free(command);
				}
				xmlFreeDoc(doc);
			}
		}
	}

	return EXIT_SUCCESS;
}
