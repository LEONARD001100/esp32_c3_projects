idf_component_register(SRCS "rgb_webserver.c"
                       PRIV_REQUIRES nvs_flash esp_wifi esp_event esp_netif esp_http_server esp_driver_gpio
                       INCLUDE_DIRS "")
