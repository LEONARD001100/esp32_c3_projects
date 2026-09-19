#include <stdio.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define LED_GPIO GPIO_NUM_4

void app_main(void)
{
    // Configure GPIO4 as an output
    gpio_set_direction(LED_GPIO, GPIO_MODE_OUTPUT);

    while (1)
    {
        // GPIO4 = HIGH
        gpio_set_level(LED_GPIO, 1);

        // Wait 1 second
        vTaskDelay(pdMS_TO_TICKS(1000));

        // GPIO4 = LOW
        gpio_set_level(LED_GPIO, 0);

        // Wait 1 second
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}