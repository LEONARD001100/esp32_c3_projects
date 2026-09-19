#include <stdio.h>
#include "driver/gpio.h"

#define BUTTON_GPIO GPIO_NUM_4
#define LED_GPIO GPIO_NUM_5

void app_main(void)
{
	gpio_set_direction(BUTTON_GPIO,GPIO_MODE_INPUT);
	gpio_set_direction(LED_GPIO,GPIO_MODE_OUTPUT);

	while (1){
		int button_state=gpio_get_level(BUTTON_GPIO);
		if (button_state==1){
			gpio_set_level(LED_GPIO,1);
		}
		else{
			gpio_set_level(LED_GPIO,0);
		}
	}
}
