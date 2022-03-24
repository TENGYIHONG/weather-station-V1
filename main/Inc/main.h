#ifndef _ESP_HTTP_CLIENT_EXAMPLE_H
#define _ESP_HTTP_CLIENT_EXAMPLE_H 1

#define MAX_HTTP_RECV_BUFFER 512
#define MAX_HTTP_OUTPUT_BUFFER 2048
esp_err_t _http_event_handler(esp_http_client_event_t *evt);

static void http_test_task(void *pvParameters);

#endif