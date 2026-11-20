#include <stdio.h>
#include <stdbool.h>
#include "button.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static volatile bool s_led_enabled = false;

bool button_is_led_enabled(void)
{
    return s_led_enabled;
}

static void handle_button(void *p)
{
    bool laststatus = 1;

    while (1)
    {
        bool currentstatus = gpio_get_level(BUTTON_PIN);

        // Phát hiện lúc nhấn nút (HIGH -> LOW)
        if (laststatus == 1 && currentstatus == 0)
        {
            s_led_enabled = !s_led_enabled;
            printf("Button pressed! LED state: %s\n", s_led_enabled ? "ON" : "OFF");
        }

        laststatus = currentstatus;
        vTaskDelay(pdMS_TO_TICKS(20));
    }
}

void button_init(void)
{
    gpio_config_t button_conf = {0};
    button_conf.pin_bit_mask = (1ULL << BUTTON_PIN);
    button_conf.mode = GPIO_MODE_INPUT;
    button_conf.pull_up_en = GPIO_PULLUP_ENABLE;
    button_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    button_conf.intr_type = GPIO_INTR_DISABLE;
    gpio_config(&button_conf);

    xTaskCreate(handle_button, "handle_button", 2048, NULL, 2, NULL);
}