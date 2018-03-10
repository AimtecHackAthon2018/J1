#ifndef UDPSERVER
#define UDPSERVER

#define BUFSIZE 1024
#define PORT 8888
int udp_init();
int recieve_udpdata(char * buf, int len);

#endif
