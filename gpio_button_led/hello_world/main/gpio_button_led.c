#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define LED_GPIO     4
#define BUTTON_GPIO  3   // change this to the pin your button is on

void app_main(void)
{
    // LED pin: output
    gpio_reset_pin(LED_GPIO);
    gpio_set_direction(LED_GPIO, GPIO_MODE_OUTPUT);

    // Button pin: input, external pull-down, so no internal pull
    gpio_reset_pin(BUTTON_GPIO);
    gpio_set_direction(BUTTON_GPIO, GPIO_MODE_INPUT);
    gpio_set_pull_mode(BUTTON_GPIO, GPIO_FLOATING);

    while (1) {
        if (gpio_get_level(BUTTON_GPIO) == 1) {   // 1 = pressed (active-high)
            gpio_set_level(LED_GPIO, 1);          // LED on
        } else {
            gpio_set_level(LED_GPIO, 0);          // LED off
        }
        vTaskDelay(pdMS_TO_TICKS(20));            // 20 ms pause between checks
    }
}
