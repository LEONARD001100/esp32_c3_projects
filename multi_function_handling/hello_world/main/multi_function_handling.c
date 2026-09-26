#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void my_second_task(void *param)
{	
	while(1){
		printf("hello from second task\n");
		vTaskDelay(pdMS_TO_TICKS(1000));
	}
}


void app_main(void)
{
	xTaskCreate(my_second_task,"second_task",2048,NULL,5,NULL);

	while (1){
		printf("hello from the app main\n");
		vTaskDelay(pdMS_TO_TICKS(1000));
	}
}
