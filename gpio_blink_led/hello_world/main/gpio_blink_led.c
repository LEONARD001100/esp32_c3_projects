#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define GPIO_LED GPIO_NUM_4

void app_main(void)
{
    printf("started\n");

    gpio_reset_pin(GPIO_LED);
    gpio_set_direction(GPIO_LED, GPIO_MODE_OUTPUT);

    int status = 0;                      

    while (1) {
        status = !status;                 
        gpio_set_level(GPIO_LED, status);
        printf("status %d\n", status);

        if (status == 1) {
            printf("led on\n");
        } else {
            printf("led off\n");
        }

        printf("delay\n");
        vTaskDelay(pdMS_TO_TICKS(1000));  
    }
}
