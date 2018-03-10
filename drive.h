#ifndef DRIVE
#define DRIVE

typedef enum {
	FORWARD = 1,
	BACKWARD = 1 << 1,
	LEFT = 1 << 2,
	RIGHT = 1 << 3
} direction;

#endif
