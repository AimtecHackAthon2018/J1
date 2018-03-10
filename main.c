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
	char buf[BUFSIZE] = {0}; /* message buf */
	printf("Hello this is my small udp server\n");

	printf("%d - my buff --0x%x- \n", ret, buf[0]);
	gpio_init();

	if(udp_init() != 0){
		perror("Error occuers\n");
		return 1;
	}

	while(1){
		ret = recieve_udpdata(buf, BUFSIZE);
		if(ret < 0)
			printf("Error while reading from buffer\n");

		if(ret > 30)
			printf("%d - my buff \n", ret); 
		if(ret > 30)
			printf("%d - my buff --0x%x- \n", ret, buf[0]);
		gpio_set(PFORWARD, 0);
		gpio_set(PBACKWARD, 0);
		gpio_set(PLEFT, 0);
		gpio_set(PRIGHT, 0);

		if(ret > 29){
			printf("%d - my buff --0x%x- \n", ret, buf[0]);
			switch(buf[0]){
				case FORWARD_LEFT:
					gpio_set(PFORWARD, 1);
					gpio_set(PLEFT, 1);
					break;
				case FORWARD_STR:
					gpio_set(PFORWARD, 1);
					break;
				case FORWARD_RIGHT:
					gpio_set(PFORWARD, 1);
					gpio_set(PRIGHT, 1);
					break;
				case BACKWARD_LEFT:
					gpio_set(PBACKWARD, 1);
					gpio_set(PLEFT, 1);
					break;
				case BACKWARD_STR:
					gpio_set(PBACKWARD, 1);
					break;
				case BACKWARD_RIGHT:
					gpio_set(PBACKWARD, 1);
					gpio_set(PRIGHT, 1);
					break;
			default:
					printf("No given ret value!\n");
			}
			printf("xx\n");
		}
	}
}
