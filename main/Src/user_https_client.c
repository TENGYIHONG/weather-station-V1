#include <string.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "esp_event.h"
#include "esp_netif.h"
#include "protocol_examples_common.h"
#include "esp_tls.h"

#include "esp_http_client.h"
#include "user_cjson.h"
#include"user_https_client.h"
#include"main.h"

extern const char *TAG ;
extern const char howsmyssl_com_root_cert_pem_start[] asm("_binary_howsmyssl_com_root_cert_pem_start");
extern const char howsmyssl_com_root_cert_pem_end[]   asm("_binary_howsmyssl_com_root_cert_pem_end");

extern const char DigiCertGlobalRootCA_pem_start[] asm("_binary_DigiCertGlobalRootCA_pem_start");
extern const char DigiCertGlobalRootCA_pem_end[]   asm("_binary_DigiCertGlobalRootCA_pem_end");

extern const char ip_pem_start[] asm("_binary_ip_pem_start");
extern const char ip_pem_end[]   asm("_binary_ip_pem_end");

 void  url(char *url,char *a,char *b,char *c)
{
    // static char *URL = "https://restapi.amap.com/v3/weather/weatherInfo?key=";
    // static char *KEY = "67da34b443561bfad4e9d89b0a5a52d3";
    // static char *city  = "&city=500118";

    //char size = (sizeof(a) + sizeof(b) + sizeof(c));

    sprintf(url,"%s%s%s",a,b,c);
    ESP_LOGI(TAG,"%s",url);
    // return *str3;

}

void http_rest_with_url(void)
{
    char local_response_buffer[MAX_HTTP_OUTPUT_BUFFER] = {0};

     esp_http_client_config_t config = {
        .url = "https://api.seniverse.com/v3/weather/now.json?key=SVZ93p_n3ujVRyXWB&location=chongqing&language=zh-Hans&unit=c",
        //.url = "https://restapi.amap.com/v3/weather/weatherInfo?key=67da34b443561bfad4e9d89b0a5a52d3&city=500118",
        .cert_pem =DigiCertGlobalRootCA_pem_start,
        .event_handler = _http_event_handler,
        .user_data = local_response_buffer,        // Pass address of local buffer to get response
    };

    esp_http_client_handle_t client = esp_http_client_init(&config);

    // GET
    esp_err_t err = esp_http_client_perform(client);
    if (err == ESP_OK) {
        ESP_LOGI(TAG, "HTTP GET Status = %d, content_length = %d",
                esp_http_client_get_status_code(client),
                esp_http_client_get_content_length(client));
    } else {
        ESP_LOGE(TAG, "HTTP GET request failed: %s", esp_err_to_name(err));
    }
    ESP_LOG_BUFFER_HEX(TAG, local_response_buffer, strlen(local_response_buffer));

    printf("\r\n/*打印心知天气json原始数据*/\r\n");
    printf("local_response_buffer:%s ", local_response_buffer); /*打印心知天气json原始数据*/

    

    // printf("\r\n/*解析心知天气json原始数据*/\r\n");
	 user_parse_seniverse_json(local_response_buffer); /*解析心知天气json原始数据*/

    // printf("\r\n/*解析心知天气json原始数据*/\r\n");
    // cJSON *root = NULL;
	// root = cJSON_Parse(local_response_buffer);         /*json_data 为心知天气的原始数据*/ 
	// printf("%s\n\n", cJSON_Print(root));   /*将完整的数据以JSON格式打印出来*/
    esp_http_client_cleanup(client);
}

void http_rest_with_url_ip(void)
{
    char local_response_buffer[MAX_HTTP_OUTPUT_BUFFER] = {0};

     esp_http_client_config_t config = {
        .url = "https://restapi.amap.com/v3/ip?&output=json&key=13a9c03771436d4e776cb32255dd2347",
        //.url = "https://restapi.amap.com/v3/weather/weatherInfo?key=67da34b443561bfad4e9d89b0a5a52d3&city=500118",
        //.cert_pem = howsmyssl_com_root_cert_pem_start,
        .cert_pem =ip_pem_start,
        .event_handler = _http_event_handler,
        .user_data = local_response_buffer,        // Pass address of local buffer to get response
    };

    esp_http_client_handle_t client = esp_http_client_init(&config);

    // GET
    esp_err_t err = esp_http_client_perform(client);
    if (err == ESP_OK) {
        ESP_LOGI(TAG, "HTTP GET Status = %d, content_length = %d",
                esp_http_client_get_status_code(client),
                esp_http_client_get_content_length(client));
    } else {
        ESP_LOGE(TAG, "HTTP GET request failed: %s", esp_err_to_name(err));
    }
    ESP_LOG_BUFFER_HEX(TAG, local_response_buffer, strlen(local_response_buffer));

    printf("\r\n/*打印IP json原始数据*/\r\n");
    printf("local_response_buffer:%s ", local_response_buffer); /*打印心知天气json原始数据*/
    esp_http_client_cleanup(client);
}