idf_component_register(SRCS "web_queue_rgb.c"
                       PRIV_REQUIRES spi_flash esp_driver_gpio led_strip esp_http_server esp_wifi
                       INCLUDE_DIRS "")
