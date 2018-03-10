#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>

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
int pinmap[MAX_GPIO] = {26, 13, 6, 19};

static int gpio_write(int pin, int value) {
	static const char s_values_str[] = "01";
 
#define VALUE_MAX 30
	char path[VALUE_MAX];
	int fd;
 
	snprintf(path, VALUE_MAX, "/sys/class/gpio/gpio%d/value", pin);
	printf("Exporting %d to %s value = %d!\n", pin, path, value);
	fd = open(path, O_WRONLY);
	if (-1 == fd) {
		fprintf(stderr, "Failed to open gpio %d value for writing!\n", pin);
		return(-1);
	}
 
	if (1 != write(fd, &s_values_str[LOW == value ? 0 : 1], 1)) {
		fprintf(stderr, "Failed to write value!\n");
		return(-1);
	}
 
	close(fd);
	return(0);
}

static int gpio_export(int pin) {
#define BUFFER_MAX 3
	char buffer[BUFFER_MAX];
	ssize_t bytes_written;
	int fd;
	printf("Exporting %d for writing!\n", pin);
 
	fd = open("/sys/class/gpio/export", O_WRONLY);
	if (-1 == fd) {
		fprintf(stderr, "Failed to open export %d for writing!\n", pin);
		return(-1);
	}
 
	bytes_written = snprintf(buffer, BUFFER_MAX, "%d", pin);
	write(fd, buffer, bytes_written);
	close(fd);
	return(0);
}
 
 
static int gpio_direction(int pin, int dir) {
	static const char s_directions_str[]  = "in\0out";
 
#define DIRECTION_MAX 35
	char path[DIRECTION_MAX];
	int fd;
 
	snprintf(path, DIRECTION_MAX, "/sys/class/gpio/gpio%d/direction", pin);
	printf("Exporting %d to %s!\n", pin, path);
	fd = open(path, O_WRONLY);
	if (-1 == fd) {
		fprintf(stderr, "Failed to open gpio direction %d for writing!\n", pin);
		return(-1);
	}
 
	if (-1 == write(fd, &s_directions_str[IN == dir ? 0 : 3], IN == dir ? 2 : 3)) {
		fprintf(stderr, "Failed to set direction!\n");
		return(-1);
	}
 
	close(fd);
	return(0);
}

int gpio_init(){
	char d = '1';
	for (int i = 0; i < MAX_GPIO; i++) {
		if (-1 == gpio_export(pinmap[i]))
			return(1);
		if (-1 == gpio_direction(pinmap[i], OUT))
			return(2);
	}
	return 0;
}

int gpio_set(int pos, int value){
	if (-1 == gpio_write(pinmap[pos], value))
	 	return -1;
	return 0;
}

int gpio_deinit(){
}

static int gpio_unexport(int pin) {
	char buffer[BUFFER_MAX];
	ssize_t bytes_written;
	int fd;
 
	fd = open("/sys/class/gpio/unexport", O_WRONLY);
	if (-1 == fd) {
		fprintf(stderr, "Failed to open unexport for writing!\n");
		return(-1);
	}
 
	bytes_written = snprintf(buffer, BUFFER_MAX, "%d", pin);
	write(fd, buffer, bytes_written);
	close(fd);
	return(0);
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
