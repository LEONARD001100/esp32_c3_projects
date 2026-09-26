#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "led_strip.h"

#define RGB_LED_GPIO 8
#define LED_COUNT    1

static led_strip_handle_t strip;
void led_task(void *param)
{	
	while(1){
		led_strip_set_pixel(strip, 0, 32, 0, 0);
		led_strip_refresh(strip);
		vTaskDelay(pdMS_TO_TICKS(500));

		led_strip_clear(strip);
		vTaskDelay(pdMS_TO_TICKS(500));
	}
}


void counter_task(void *param)
{
	int count = 0;
	while (1) {
		printf("Counter: %d\n", count);
		count++;
		vTaskDelay(pdMS_TO_TICKS(300));
    }
}

void app_main(void)
{
    led_strip_config_t strip_config = {
        .strip_gpio_num = RGB_LED_GPIO,
        .max_leds = LED_COUNT,
    };
    led_strip_rmt_config_t rmt_config = {
        .resolution_hz = 10 * 1000 * 1000,
    };
    ESP_ERROR_CHECK(led_strip_new_rmt_device(&strip_config, &rmt_config, &strip));

    xTaskCreate(led_task, "led_task", 2048, NULL, 5, NULL);
    xTaskCreate(counter_task, "counter_task", 2048, NULL, 5, NULL);

    printf("Setup done, both tasks running independently\n");
}
