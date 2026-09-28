#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "led_strip.h"
#include "freertos/queue.h"
#include "esp_random.h"

#define RGB_LED_GPIO 8
#define LED_COUNT    1

static led_strip_handle_t strip;
QueueHandle_t number_queue;
void led_task(void *param)
{
	printf("Led_task\n");
	int received_number;
	while(1){
		printf("lt_loop\n");
		xQueueReceive(number_queue,&received_number,portMAX_DELAY);
		printf("Received number : %d\n",received_number);
		if (received_number % 2 ==0){
			led_strip_set_pixel(strip, 0, 32, 0, 0);
			led_strip_refresh(strip);
			printf("Red\n");
			vTaskDelay(pdMS_TO_TICKS(1000));
			led_strip_clear(strip);
			led_strip_refresh(strip);
			vTaskDelay(pdMS_TO_TICKS(1000));
		}else{
			led_strip_set_pixel(strip, 0, 0, 32, 0);
			led_strip_refresh(strip);
			printf("Green\n");
			vTaskDelay(pdMS_TO_TICKS(1000));
			led_strip_clear(strip);
			led_strip_refresh(strip);
			vTaskDelay(pdMS_TO_TICKS(1000));
		}
	}
}


int get_random_number(int min,int max)
{
	return (esp_random() % (max-min+1)) + min;
}

void random_task(void *param)
{
	printf("random_task\n");
	while(1){
		printf("rt_loop\n");
		int number= get_random_number(1,10);
		printf("Genetated a random number : %d",number);

		xQueueSend(number_queue,&number,portMAX_DELAY);
		vTaskDelay(pdMS_TO_TICKS(500));
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
	number_queue = xQueueCreate(5, sizeof(int));
	xTaskCreate(random_task, "random_task", 2048, NULL, 5, NULL);
	xTaskCreate(led_task, "led_task", 2048, NULL, 5, NULL);
    	printf("Setup done, both tasks running independently\n");
}
