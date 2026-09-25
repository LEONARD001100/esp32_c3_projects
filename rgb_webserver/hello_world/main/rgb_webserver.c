#include <stdio.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "nvs_flash.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_netif.h"
#include "esp_http_server.h"
#include "led_strip.h"

#define RGB_LED_GPIO 8
#define LED_COUNT    1

static led_strip_handle_t strip;

// --------------------------------------------------------> Wi-Fi setup 

static void wifi_event_handler(void* arg, esp_event_base_t event_base,
                                int32_t event_id, void* event_data)
{
    if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START) {
        esp_wifi_connect();
    } else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED) {
        printf("Disconnected, retrying...\n");
        esp_wifi_connect();
    } else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP) {
        ip_event_got_ip_t* event = (ip_event_got_ip_t*) event_data;
        printf("Got IP: " IPSTR "\n", IP2STR(&event->ip_info.ip));
    }
}

static void wifi_init(void)
{
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    esp_netif_create_default_wifi_sta();

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &wifi_event_handler, NULL, NULL));
    ESP_ERROR_CHECK(esp_event_handler_instance_register(IP_EVENT, IP_EVENT_STA_GOT_IP, &wifi_event_handler, NULL, NULL));

    wifi_config_t wifi_config = {
        .sta = {
            .ssid = "leo",
            .password = "34567890",
        },
    };

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &wifi_config));
    ESP_ERROR_CHECK(esp_wifi_start());
}

// --------------------------------------------------> The webpage,the plain HTML string 

static const char *html_page =
"<!DOCTYPE html><html><body style='font-family:sans-serif;text-align:center'>"
"<h2>ESP32 RGB Control</h2>"
"<p>R <input type='range' min='0' max='255' id='r' oninput='send()'></p>"
"<p>G <input type='range' min='0' max='255' id='g' oninput='send()'></p>"
"<p>B <input type='range' min='0' max='255' id='b' oninput='send()'></p>"
"<script>"
"function send(){"
"  var r=document.getElementById('r').value;"
"  var g=document.getElementById('g').value;"
"  var b=document.getElementById('b').value;"
"  fetch('/set?r='+r+'&g='+g+'&b='+b);"
"}"
"</script>"
"</body></html>";

// -------------------------------------------------------> Handler for "/" 

static esp_err_t root_get_handler(httpd_req_t *req)
{
    httpd_resp_send(req, html_page, HTTPD_RESP_USE_STRLEN);
    return ESP_OK;
}

// ---------- ------------------------> Handler for "/set?r=..&g=..&b=.."->sets the LED colour

static esp_err_t set_get_handler(httpd_req_t *req)
{
    char query[100];
    char val[16];
    int r = 0, g = 0, b = 0;

    if (httpd_req_get_url_query_str(req, query, sizeof(query)) == ESP_OK) {
        if (httpd_query_key_value(query, "r", val, sizeof(val)) == ESP_OK) r = atoi(val);
        if (httpd_query_key_value(query, "g", val, sizeof(val)) == ESP_OK) g = atoi(val);
        if (httpd_query_key_value(query, "b", val, sizeof(val)) == ESP_OK) b = atoi(val);
    }

    printf("Set colour: r=%d g=%d b=%d\n", r, g, b);

    led_strip_set_pixel(strip, 0, r, g, b);
    led_strip_refresh(strip);

    httpd_resp_send(req, "OK", HTTPD_RESP_USE_STRLEN);
    return ESP_OK;
}

// --------------------------------------> Starting the server and registering both handlers

static void start_webserver(void)
{
    httpd_handle_t server = NULL;
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();

    if (httpd_start(&server, &config) == ESP_OK) {
        httpd_uri_t root_uri = {
            .uri = "/",
            .method = HTTP_GET,
            .handler = root_get_handler,
        };
        httpd_register_uri_handler(server, &root_uri);

        httpd_uri_t set_uri = {
            .uri = "/set",
            .method = HTTP_GET,
            .handler = set_get_handler,
        };
        httpd_register_uri_handler(server, &set_uri);
    }
}

// -------------------------------------------------------------> Main

void app_main(void)
{
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    led_strip_config_t strip_config = {
        .strip_gpio_num = RGB_LED_GPIO,
        .max_leds = LED_COUNT,
    };
    led_strip_rmt_config_t rmt_config = {
        .resolution_hz = 10 * 1000 * 1000,
    };
    ESP_ERROR_CHECK(led_strip_new_rmt_device(&strip_config, &rmt_config, &strip));

    wifi_init();
    start_webserver();

    printf("Setup done. Open the C3's IP address in a browser.\n");
}
