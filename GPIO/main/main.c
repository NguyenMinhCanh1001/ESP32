#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "led_strip.h"
#include "button.h"
#include "led.h"

#define GPIO_LED    48
#define LED_COUNT 1
void led_donsac(){
 gpio_config_t io_conf ={};
    io_conf.pin_bit_mask = (1ULL << GPIO_NUM_48) ;          /*!< GPIO pin: set with bit mask, each bit maps to a GPIO */
    io_conf.mode = GPIO_MODE_OUTPUT;               /*!< GPIO mode: set input/output mode                     */
    io_conf.pull_up_en = GPIO_PULLUP_DISABLE;       /*!< GPIO pull-up                                         */
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;   /*!< GPIO pull-down                                       */
    io_conf.intr_type = GPIO_INTR_DISABLE ;      /*!< GPIO interrupt type  */
    gpio_config(&io_conf);
    while(1)
    {
        gpio_set_level(GPIO_NUM_48, 1);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        gpio_set_level(GPIO_NUM_48, 0);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}
void app_main(void)
{ 
   
   button_init();
   setup_led();
}
