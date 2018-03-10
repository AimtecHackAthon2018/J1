#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>

#include <linux/i2c-dev.h>
//#include <i2c/smbus.h>

#include "gpio.h"

#define IN  0
#define OUT 1
 
#define LOW  0
#define HIGH 1
 
#define PIN  24 /* P1-18 */
#define POUT 4  /* P1-07 */
/*
 * https://www.element14.com/community/servlet/JiveServlet/previewBody/73950-102-11-339300/pi3_gpio.png
 */

uint8_t val = 0;
int file;

int pinmap[MAX_GPIO] = {24, 4, 5, 6};
  
int i2c_reg_write(uint8_t address, uint8_t data){
// 	struct i2c_rwdr_ioctl_data data = {0};
// 	data.nmsgs = 2;
// 	struct i2c_msg msgs[2];
// 
// 	msgs[0].addr = address;
// 	msgs[0].len = 2;
// 	msgs[0].flags = 0;
// 	msgs[0].buf = &dataAddr;
// 
// 	data.msgs = msgs;
// 
// 	ioctl(file, I2C_RDWR, msgset);

	uint8_t bufx[2];
	bufx[0] = address;
	bufx[1] = data;
	if (write(file, &bufx, 2) != 2) {
		exit(3);
	}
}

static int gpio_write(int pin, int value) {
	/* IPOL to val 8b*/
	i2c_reg_write(0x1,0xff);
	return 0;
}

static int gpio_direction(int pin, int dir) {
	/* IODIR to 000000 8b */
	i2c_reg_write(0x0, 0x0f);
	return 0;
}

int gpio_init(){
	char filename[20];
  
	snprintf(filename, 19, "/dev/i2c-%d", 1);
	file = open(filename, O_RDWR);
	if (file < 0) {
		printf("file i2c init error\n");
		return -1;
  }

	int addr = 0x20; /* The I2C address */

	if (ioctl(file, I2C_SLAVE, addr) < 0) {
		printf("i2c init error\n");
		return 1;
	}
	return 0;
}

int gpio_set(int pos, int value){
	if (-1 == gpio_write(pinmap[pos], pos))
	 	return -1;
	return 0;
}

int gpio_deinit(){
}
 
// static int
// GPIORead(int pin)
// {
// #define VALUE_MAX 30
// 	char path[VALUE_MAX];
// 	char value_str[3];
// 	int fd;
//  
// 	snprintf(path, VALUE_MAX, "/sys/class/gpio/gpio%d/value", pin);
// 	fd = open(path, O_RDONLY);
// 	if (-1 == fd) {
// 		fprintf(stderr, "Failed to open gpio value for reading!\n");
// 		return(-1);
// 	}
//  
// 	if (-1 == read(fd, value_str, 3)) {
// 		fprintf(stderr, "Failed to read value!\n");
// 		return(-1);
// 	}
//  
// 	close(fd);
//  
// 	return(atoi(value_str));
// }
 
// int
// main(int argc, char *argv[])
// {
// 	int repeat = 10;
//  
// 	/*
// 	 * Enable GPIO pins
// 	 */
// 	if (-1 == GPIOExport(POUT) || -1 == GPIOExport(PIN))
// 		return(1);
//  
// 	/*
// 	 * Set GPIO directions
// 	 */
// 	if (-1 == GPIODirection(POUT, OUT) || -1 == GPIODirection(PIN, IN))
// 		return(2);
//  
// 	do {
// 		/*
// 		 * Write GPIO value
// 		 */
// 		if (-1 == GPIOWrite(POUT, repeat % 2))
// 			return(3);
//  
// 		/*
// 		 * Read GPIO value
// 		 */
// 		printf("I'm reading %d in GPIO %d\n", GPIORead(PIN), PIN);
//  
// 		usleep(500 * 1000);
// 	}
// 	while (repeat--);
//  
// 	/*
// 	 * Disable GPIO pins
// 	 */
// 	if (-1 == GPIOUnexport(POUT) || -1 == GPIOUnexport(PIN))
// 		return(4);
//  
// 	return(0);
// }
