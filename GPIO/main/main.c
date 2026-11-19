#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "led_strip.h"

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
    led_strip_config_t strip_config = {
        .strip_gpio_num = GPIO_LED,
        .max_leds = LED_COUNT, 
        .led_model = LED_MODEL_WS2812, 
        .color_component_format = LED_STRIP_COLOR_COMPONENT_FMT_GRB,
        .flags = {
            .invert_out = false
        }
    };

    led_strip_rmt_config_t rmt_config = {
        .clk_src = RMT_CLK_SRC_DEFAULT,
        .resolution_hz = 10 * 1000 * 1000,
        .mem_block_symbols = 64,
        .flags = {
            .with_dma = false
        }
    };

    led_strip_handle_t led_strip;

    ESP_ERROR_CHECK(
        led_strip_new_rmt_device(
            &strip_config,
            &rmt_config,
            &led_strip
        )
    );
   
    while (1)
    {
        // Đỏ
        led_strip_set_pixel(led_strip, 0, 255, 0, 0);
        led_strip_refresh(led_strip);
        vTaskDelay(pdMS_TO_TICKS(1000));

        // Xanh lá
        led_strip_set_pixel(led_strip, 0, 0, 255, 0);
        led_strip_refresh(led_strip);
        vTaskDelay(pdMS_TO_TICKS(1000));

        // Xanh dương
        led_strip_set_pixel(led_strip, 0, 0, 0, 255);
        led_strip_refresh(led_strip);
        vTaskDelay(pdMS_TO_TICKS(1000));

        // Tắt LED
        led_strip_clear(led_strip);
        led_strip_refresh(led_strip);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
