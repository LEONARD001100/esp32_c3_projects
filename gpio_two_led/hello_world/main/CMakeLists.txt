idf_component_register(SRCS "gpio_two_led.c"
                       PRIV_REQUIRES spi_flash	esp_driver_gpio
                       INCLUDE_DIRS "")
