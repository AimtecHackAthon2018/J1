/* 
 * udpserver.c - A simple UDP echo server 
 * usage: udpserver <port>
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "udpserver.h"

int sockfd; /* socket */

/* Communicate with last server only :] */
struct sockaddr_in clientaddr; /* client addr */
int clientlen = sizeof(clientaddr);

int udp_init(){
	int optval; /* flag value for setsockopt */
	struct sockaddr_in serveraddr; /* server's addr */
	int portno; /* port to listen on */
  
	portno = PORT; 

	/* 
	* socket: create the parent socket 
	*/
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd < 0){
		perror("ERROR opening socket");
		return 1;
	}

	/* setsockopt: Handy debugging trick that lets 
	 * us rerun the server immediately after we kill it; 
	 * otherwise we have to wait about 20 secs. 
	 * Eliminates "ERROR on binding: Address already in use" error. 
	 */
	optval = 1;
	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, 
			(const void *)&optval , sizeof(int));

	/*
	 * build the server's Internet address
	 */
	bzero((char *) &serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons((unsigned short)portno);

	/* 
	 * bind: associate the parent socket with a port 
	 */
	if (bind(sockfd, (struct sockaddr *) &serveraddr, 
				sizeof(serveraddr)) < 0){
		perror("ERROR on binding");
		return 2;
	}

	printf("%s bind successful.\n", __FUNCTION__);
	return 0;
}

int recieve_udpdata(char * buf, int len){
	int n; /* message byte size */
	char *hostaddrp; /* dotted decimal host addr string */
	struct hostent *hostp; /* client host info */

	/*
	 * recvfrom: receive a UDP datagram from a client
	 */
	bzero(buf, len);
	n = recvfrom(sockfd, buf, len, 0,
			(struct sockaddr *) &clientaddr, &clientlen);
	if (n < 0)
		perror("ERROR in recvfrom");

	hostaddrp = inet_ntoa(clientaddr.sin_addr);
	if (hostaddrp == NULL)
		perror("ERROR on inet_ntoa\n");
	printf("server received datagram from (%s)\n", 
			hostaddrp);
	printf("server received %d/%d bytes: %s\n", strlen(buf), n, buf);
}

/* XXX: We don't need that function right now */
int sendto_udpserver(){
	char buf[BUFSIZE]; /* message buf */
	int n; /* message byte size */
	/* 
	 * sendto: echo the input back to the client 
	 */
	n = sendto(sockfd, buf, strlen(buf), 0, 
			(struct sockaddr *) &clientaddr, clientlen);
	if (n < 0) 
		perror("ERROR in sendto");
}
