idf_component_register(SRCS "wifi_connect_test.c"
                       PRIV_REQUIRES nvs_flash esp_wifi esp_event esp_netif esp_driver_gpio
                       INCLUDE_DIRS "")
