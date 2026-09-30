idf_component_register(SRCS "web_queue_rgb.c"
                       PRIV_REQUIRES esp_driver_gpio nvs_flash esp_wifi esp_event esp_netif esp_http_server
                       INCLUDE_DIRS "")
