idf_component_register(SRCS "gpio_random_led.c"
                       PRIV_REQUIRES spi_flash esp_driver_gpio
                       INCLUDE_DIRS "")
