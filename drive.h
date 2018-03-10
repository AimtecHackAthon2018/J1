#ifndef DRIVE
#define DRIVE

typedef enum {
	PFORWARD = 0,
	PBACKWARD= 1,
	PLEFT = 2,
	PRIGHT = 3,
} pdirection;
typedef enum {
	HALT = 0x61,
	FORWARD_LEFT = 0x62,
	FORWARD_STR = 0x63,
	FORWARD_RIGHT = 0x64,
	BACKWARD_LEFT = 0x65,
	BACKWARD_STR = 0x66,
	BACKWARD_RIGHT = 0x67,
} direction;

#endif
