#include <stdio.h>
#include <stdbool.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "led_strip.h"
#include "led.h"
#include "button.h"

static led_strip_handle_t s_led_strip = NULL;

static void handle_leds(void *p)
{
    while (1)
    {
        if (button_is_led_enabled())
        {
            // Bật LED RGB (ví dụ xanh dương: R=0, G=0, B=255)
            led_strip_set_pixel(s_led_strip, 0, 0, 0, 255);
            led_strip_refresh(s_led_strip);
        }
        else
        {
            // Tắt LED RGB
            led_strip_clear(s_led_strip);
            led_strip_refresh(s_led_strip);
        }

        vTaskDelay(pdMS_TO_TICKS(50));
    }
}

void setup_led(void)
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

    ESP_ERROR_CHECK(
        led_strip_new_rmt_device(
            &strip_config,
            &rmt_config,
            &s_led_strip
        )
    );

    // Đảm bảo tắt LED lúc mới khởi tạo
    led_strip_clear(s_led_strip);
    led_strip_refresh(s_led_strip);

    xTaskCreate(handle_leds, "handle_leds", 2048, NULL, 2, NULL);
}