#ifndef LED_H
#define LED_H

#include "driver/gpio.h"

#define GPIO_LED    GPIO_NUM_48
#define LED_COUNT   1

void setup_led(void);

#endif