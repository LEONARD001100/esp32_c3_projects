/*
 * SPDX-FileCopyrightText: 2010-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */

#include <stdio.h>
#include <inttypes.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_chip_info.h"
#include "esp_flash.h"
#include "esp_system.h"
#include "driver/gpio.h"
#include "esp_random.h"

#define GPIO_LED1 GPIO_NUM_1
#define GPIO_LED2 GPIO_NUM_2
#define GPIO_LED3 GPIO_NUM_3
#define GPIO_LED4 GPIO_NUM_4
#define GPIO_LED5 GPIO_NUM_5
#define GPIO_LED6 GPIO_NUM_6
#define GPIO_LED7 GPIO_NUM_7
#define GPIO_LED8 GPIO_NUM_8
#define GPIO_LED9 GPIO_NUM_9

void app_main(void)
{
	gpio_set_direction(GPIO_LED1,GPIO_MODE_OUTPUT);
	gpio_set_direction(GPIO_LED2,GPIO_MODE_OUTPUT);
	gpio_set_direction(GPIO_LED3,GPIO_MODE_OUTPUT);
	gpio_set_direction(GPIO_LED4,GPIO_MODE_OUTPUT);
	gpio_set_direction(GPIO_LED5,GPIO_MODE_OUTPUT);
	gpio_set_direction(GPIO_LED6,GPIO_MODE_OUTPUT);
	gpio_set_direction(GPIO_LED7,GPIO_MODE_OUTPUT);
	gpio_set_direction(GPIO_LED8,GPIO_MODE_OUTPUT);
	gpio_set_direction(GPIO_LED9,GPIO_MODE_OUTPUT);

	gpio_set_level(GPIO_LED1,0);
	gpio_set_level(GPIO_LED2,0);
	gpio_set_level(GPIO_LED3,0);
	gpio_set_level(GPIO_LED4,0);
	gpio_set_level(GPIO_LED5,0);
	gpio_set_level(GPIO_LED6,0);
	gpio_set_level(GPIO_LED7,0);
	gpio_set_level(GPIO_LED8,0);
	gpio_set_level(GPIO_LED9,0);

	srand(esp_random());

	while(1){
		int random=1+(esp_random() % 8);

		if (random==1){
			gpio_set_level(GPIO_LED1,1);
			vTaskDelay(pdMS_TO_TICKS(200));
			gpio_set_level(GPIO_LED1,0);
		}else if(random==2){
			gpio_set_level(GPIO_LED2,1);
			vTaskDelay(pdMS_TO_TICKS(200));
			gpio_set_level(GPIO_LED2,0);
		}else if(random==3){
			gpio_set_level(GPIO_LED3,1);
			vTaskDelay(pdMS_TO_TICKS(200));
			gpio_set_level(GPIO_LED3,0);
		}else if(random==4){
			gpio_set_level(GPIO_LED4,1);
			vTaskDelay(pdMS_TO_TICKS(200));
			gpio_set_level(GPIO_LED4,0);
		}else if(random==5){
			gpio_set_level(GPIO_LED5,1);
			vTaskDelay(pdMS_TO_TICKS(200));
			gpio_set_level(GPIO_LED5,0);
		}else if(random==6){
			gpio_set_level(GPIO_LED6,1);
			vTaskDelay(pdMS_TO_TICKS(200));
			gpio_set_level(GPIO_LED6,0);
		}else if(random==7){
			gpio_set_level(GPIO_LED7,1);
			vTaskDelay(pdMS_TO_TICKS(200));
			gpio_set_level(GPIO_LED7,0);
		}else if(random==8){
			gpio_set_level(GPIO_LED8,1);
			vTaskDelay(pdMS_TO_TICKS(200));
			gpio_set_level(GPIO_LED8,0);
		}else{
			gpio_set_level(GPIO_LED9,1);
			vTaskDelay(pdMS_TO_TICKS(200));
			gpio_set_level(GPIO_LED9,0);
		}
		vTaskDelay(pdMS_TO_TICKS(200));
	}

}
