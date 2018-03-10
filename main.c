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
#include "gpio.h"
#include "drive.h"

int main(int argc, char **argv) {
	int changer = 1;
	int ret;
	char buf[BUFSIZE]; /* message buf */
	printf("Hello this is my small udp server\n");

	gpio_init();

	if(udp_init() != 0){
		perror("Error occuers\n");
		return 1;
	}

	while(1){
		ret = recieve_udpdata(buf, BUFSIZE);
		if(ret < 0)
			printf("Error while reading from buffer\n");

		switch(ret){
			case 32:
				gpio_set(FORWARD, changer % 2);
			case 31:
				gpio_set(BACKWARD, changer % 2);
			case 30:
				gpio_set(LEFT, changer % 2);
			case 29:
				gpio_set(RIGHT, changer % 2);
				changer++;
			default:
				printf("%d - my buff %s \n", ret, buf);
		}
	}

}
