#ifndef GPIO
#define GPIO

#define MAX_GPIO 4

int gpio_init();
/* All gpio are outputs. We do not need stringer tests */
int gpio_set(int pos, int val);

int gpio_deinit();

#endif
