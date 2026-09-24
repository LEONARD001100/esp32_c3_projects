#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "led_strip.h"

#define RGB_LED_GPIO 8   
#define LED_COUNT    1   

void app_main(void)
{
    led_strip_config_t strip_config = {
        .strip_gpio_num = RGB_LED_GPIO,
        .max_leds = LED_COUNT,
    };

    led_strip_rmt_config_t rmt_config = {
        .resolution_hz = 10 * 1000 * 1000,  
    };

    led_strip_handle_t strip;
    ESP_ERROR_CHECK(led_strip_new_rmt_device(&strip_config, &rmt_config, &strip));

    while (1) {
        // Red
        led_strip_set_pixel(strip, 0, 32, 0, 0);   
        led_strip_refresh(strip);
        vTaskDelay(pdMS_TO_TICKS(200));

        // Green
        led_strip_set_pixel(strip, 0, 0, 32, 0);
        led_strip_refresh(strip);
        vTaskDelay(pdMS_TO_TICKS(200));

        // Blue
        led_strip_set_pixel(strip, 0, 0, 0, 32);
        led_strip_refresh(strip);
        vTaskDelay(pdMS_TO_TICKS(200));

        // Off
        led_strip_clear(strip);
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}
