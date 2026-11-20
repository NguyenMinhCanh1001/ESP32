#ifndef BUTTON_H
#define BUTTON_H

#include "driver/gpio.h"

#define BUTTON_PIN GPIO_NUM_0  // Define the GPIO pin for the button

void button_init(void);
bool button_is_led_enabled(void);

#endif