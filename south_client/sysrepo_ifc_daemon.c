#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "../sysrepo_config.h"
#include "../srd.h"

#define MSGLENFIELDWIDTH 7

void createListeningSocket(int *listenfd, int myPort) {
	int sock;
	struct sockaddr_in servaddr;

	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == -1) {
	   printf ("Error in creating listening socket.\n");
	   *listenfd = -1;
	} else {
	   bzero(&servaddr, sizeof(servaddr));
	   servaddr.sin_family = AF_INET;
	   servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	   servaddr.sin_port =  htons(myPort);
	   if (bind(sock, (struct sockaddr *) &servaddr, sizeof(servaddr))){
		   printf ("Fatal Error: Could not bind to the server port %d. May be it is in use or in TIME_WAIT state.\n", myPort);
		   printf ("Use 'netstat -nap | grep %d' command to see its status.\n", myPort);
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
   if(iResult > 0){
      s =  accept(listenfd, NULL, NULL);
      return s;
   } else{
      return -1; // error
   }
}

int main() {
	int sockfd, n;
	char myOpDataStoreXML[3000];
	xmlDocPtr myOpDataStore;
	char sendline[1000];
	char xpath[100];
	char *buffPtr = NULL, *ds_list = NULL;
	int buffSize = 100;

	if (!srd_connect ("127.0.0.1", 3500, &sockfd)){
		printf ("Error in connecting to server 127.0.0.1 at port 3500\n");
		return EXIT_FAILURE;
	}

	if (!srd_listOpDataStores(sockfd, &ds_list)) {
		printf("Failed to get sysrepo datastores\n");
		srd_disconnect (sockfd);
		return EXIT_FAILURE;
	}

	if (strstr(ds_list, NP_SYSREPO_IFC_DS) == NULL) {
		if (srd_createOpDataStore(sockfd, NP_SYSREPO_IFC_DS) != 1) {
			printf("Failed to create a datastore\n");
			srd_disconnect (sockfd);
			return EXIT_FAILURE;
		}
	}
	free(ds_list);

	if (srd_useOpDataStore(sockfd, NP_SYSREPO_IFC_DS) != 1) {
		printf("Failed to use %s datastore\n", NP_SYSREPO_IFC_DS);
		srd_disconnect (sockfd);
		return EXIT_FAILURE;
	}

	printf ("Waiting for one sample request to apply XPath on one of my Operational Data Stores.....\n");
	fflush (stdout);
	// assume there is one operation data store 'op_01' is being maintained by this South Client.
	strcpy (myOpDataStoreXML, "<?xml version=\"1.0\" encoding=\"utf-8\"?><data xmlns=\"urn:ietf:params:xml:ns:netconf:base:1.0\"><interfaces xmlns=\"urn:ietf:params:xml:ns:yang:ietf-interfaces\"/><interfaces-state xmlns=\"urn:ietf:params:xml:ns:yang:ietf-interfaces\"><interface><name></name><type></type><admin-status></admin-status><oper-status></oper-status><last-change></last-change><if-index></if-index><phys-address></phys-address><higher-layer-if></higher-layer-if><lower-layer-if></lower-layer-if><speed></speed><statistics><discontinuity-time></discontinuity-time><in-octets></in-octets><in-unicast-pkts></in-unicast-pkts><in-broadcast-pkts></in-broadcast-pkts> <in-multicast-pkts></in-multicast-pkts><in-discards></in-discards> <in-errors></in-errors> <in-unknown-protos></in-unknown-protos> <out-octets></out-octets> <out-unicast-pkts></out-unicast-pkts> <out-broadcast-pkts></out-broadcast-pkts> <out-multicast-pkts></out-multicast-pkts> <out-discards></out-discards> <out-errors/> </statistics> </interface> </interfaces-state> </data>");
	myOpDataStore = xmlReadMemory (myOpDataStoreXML, strlen (myOpDataStoreXML), "noname.xml", NULL, 0);
	if (myOpDataStore == NULL){
		printf ("Local error: Failed to make DOM for my Op Data Store.\n");
		srd_disconnect (sockfd);
		exit (0);
	}

	// Need to give a socket to the SysrepoD on which this daemon will be listening on to receive Op Data Store related commands.
	char myIPAddress[100] = "127.0.0.1";
	int  myPort = 3510;
	int  listenfd, connfd;

	if (!srd_registerClientSocket (sockfd, myIPAddress, myPort)) { // register my socket info with SysrepoD
		printf ("Unable to tell SysrepoD about my listening port.\n");
		srd_disconnect (sockfd);
		xmlFreeDoc (myOpDataStore);
		exit (0);
	}
	// Start listening for connection request on 'myPort'
	createListeningSocket (&listenfd, myPort);
	if(listenfd != -1){
		printf("Listening on Port %d .....\n", myPort);
		listen(listenfd, SOMAXCONN); // SOMAXCONN defined by socket.h: Max # of clients
	} else {
		printf ("Error in listening for connections.\n");
		srd_disconnect (sockfd);
		xmlFreeDoc (myOpDataStore);
		exit (0);
	}

	while (1) {
		connfd = acceptClients (listenfd); // No Time out
		if(connfd > -1){
			printf("Received a connection request.\n");
			fflush (stdout);
		} else {
			// error
			printf ("Error in accepting a connection.\n");
			srd_disconnect (sockfd);
			xmlFreeDoc (myOpDataStore);
			exit (0);
		}
		buffPtr = (char *) malloc (buffSize);
		if (buffPtr == NULL){
			printf ("Local error: unable to allocate memory.\n");
			srd_disconnect (sockfd);
			xmlFreeDoc (myOpDataStore);
			close (connfd);
			close (listenfd);
			exit (0);
		}

		n = srd_recvServer (connfd, &buffPtr, &buffSize);
		if (n == 0){
				printf("Failed to receive data from sysrepod\n");
				usleep(100);
		} else {
			xmlDocPtr doc = NULL;
			xmlChar *command;
			xmlChar *param1, *param2;

			doc = xmlReadMemory(&(buffPtr[MSGLENFIELDWIDTH + 1]), strlen (&(buffPtr[MSGLENFIELDWIDTH + 1])), "noname.xml", NULL, 0);
			if (doc == NULL){
					sprintf (sendline, "<xml><error>XML Document not correct</error></xml>");
					srd_sendServer (connfd, sendline, strlen (sendline));
			} else {
				strcpy((char *)xpath, "/xml/command");
				command = srd_getFirstNodeValue(doc, (xmlChar *)xpath);
				if (command == NULL){
					sprintf (sendline, "<xml><error>No command found.</error></xml>");
					srd_sendServer(connfd, sendline, strlen (sendline));
				} else if (strcmp ((char *)command, "apply_xpathOpDataStore") == 0){
					// param1 contains Op Data Store Name, param2 contains XPath
					strcpy ((char *) xpath, "/xml/param1");
					param1 = srd_getFirstNodeValue(doc, (xmlChar *)xpath);
					if(param1 == NULL){
						sprintf (sendline, "<xml><error>Value for Op Data Store name not found</error></xml>");
						srd_sendServer(connfd, sendline, strlen(sendline));
					} else if (strcmp((char *)param1, NP_SYSREPO_IFC_DS) != 0){
						sprintf (sendline, "<xml><error>Unknown Operational Data Store name: %s</error></xml>", (char *)param1);
						xmlFree (param1);
						srd_sendServer (connfd, sendline, strlen (sendline));
					} else {
						strcpy ((char *) xpath, "/xml/param2");
						param2 = srd_getFirstNodeValue(doc, (xmlChar *)xpath);
						if(param2 == NULL){
							sprintf (sendline, "<xml><error>XPath not found</error></xml>");
							srd_sendServer(connfd, sendline, strlen(sendline));
						} else {
							// apply xpath and return results back to sysrepod
							srd_DOMHandleXPath (connfd, myOpDataStore, param2);
							xmlFree (param2);
						}
						xmlFree (param1);
					}
					free (command);
				}
				xmlFreeDoc (doc);
			}
		}
	}

	return EXIT_SUCCESS;
}
