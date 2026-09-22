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


#define GPIO_LED1 GPIO_NUM_4
#define GPIO_LED2 GPIO_NUM_5

void app_main(void)
{	
	int status1=0;

	gpio_set_direction(GPIO_LED1,GPIO_MODE_OUTPUT);
	gpio_set_direction(GPIO_LED2,GPIO_MODE_OUTPUT);
	while(1){
		
		gpio_set_level(GPIO_LED1,status1);
		gpio_set_level(GPIO_LED2,!status1);
		status1=!status1;

	
		vTaskDelay(pdMS_TO_TICKS(1000));
	}
}
