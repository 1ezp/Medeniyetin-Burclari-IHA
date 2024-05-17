// --------------------Libraries---------------------

// C
#include <stdio.h>
// freeRTOS
#include <freertos/FreeRTOS.h>
#include <freertos/timers.h>
#include <freertos/task.h>
#include <freertos/semphr.h>
// Task
#include <esp_timer.h>
#include "esp_err.h"
#include "esp_log.h"
// Communication
#include "string.h"
#include "esp_now.h"
#include "esp_wifi.h"
#include "esp_netif.h"
#include "esp_mac.h"
#include "esp_event.h"
#include "nvs_flash.h"
// Electric
#include "driver/gpio.h"
#include "driver/ledc.h"
#include "esp_adc/adc_oneshot.h"
// #include "esp_adc/adc_continuous.h"
// Servo
// #include "driver/mcpwm_prelude.h"
// #include "driver/adc.h"

// --------------------------------------------------

// --------------------Functions---------------------

void delay(int milliseconds) {
    vTaskDelay(milliseconds / portTICK_PERIOD_MS);
}

void digitalWrite(int pin, bool state){
    gpio_set_level(pin, state);
}

void analogWrite(int mode, int channel, int value){

    ESP_ERROR_CHECK(ledc_set_duty(mode, channel, value));
    ESP_ERROR_CHECK(ledc_update_duty(mode, channel));
}

void lockSemaphore(SemaphoreHandle_t semaphore) {
    while (xSemaphoreTake(semaphore, 0) == pdPASS) {
        // Take the semaphore until it's not available
    }
}

int map(int x, int in_min, int in_max, int out_min, int out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

// --------------------------------------------------

// --------------------ESPNOW------------------------

#define ESP_CHANNEL 1

static uint8_t peer_mac [ESP_NOW_ETH_ALEN] = {0x48, 0x27, 0xe2, 0xfc, 0x2f, 0x18};  // Receiver Mac

static const char *TAG = "esp_now_init";

static esp_err_t init_wifi(void){

    wifi_init_config_t wifi_init_config = WIFI_INIT_CONFIG_DEFAULT();

    esp_netif_init();
    esp_event_loop_create_default();
    nvs_flash_init();

    esp_wifi_init(&wifi_init_config);
    esp_wifi_set_mode(WIFI_MODE_STA);
    esp_wifi_set_storage(WIFI_STORAGE_FLASH);

    esp_wifi_start();

    ESP_LOGI(TAG, "Wifi Init Completed");

    return ESP_OK;
}

void send_cb(const uint8_t *mac_addr, esp_now_send_status_t status);
void recv_cb(const esp_now_recv_info_t * esp_now_info, const uint8_t *data, int data_len);
static esp_err_t init_esp_now(){

    esp_now_init();
    esp_now_register_recv_cb(recv_cb);
    esp_now_register_send_cb(send_cb);

    ESP_LOGI(TAG, "ESP-NOW Completed");
    return ESP_OK;
}

static esp_err_t register_peer(uint8_t *peer_addr){

    esp_now_peer_info_t esp_now_peer_info = {};
    memcpy(esp_now_peer_info.peer_addr, peer_mac, ESP_NOW_ETH_ALEN);
    esp_now_peer_info.channel = ESP_CHANNEL;
    esp_now_peer_info.ifidx = ESP_IF_WIFI_STA;

    esp_now_add_peer(&esp_now_peer_info);

    return ESP_OK;
}

void send_cb(const uint8_t *mac_addr, esp_now_send_status_t status){

    if (status == ESP_NOW_SEND_SUCCESS){

        // ESP_LOGI(TAG, "Send Success");
    }
    else{

        ESP_LOGI(TAG, "Send Failed");
    }
}

// ----------

float data[2] = {-1, -1};
bool isTarget = false;

void fixLocation();

static esp_err_t esp_now_send_data(const uint8_t *peer_addr, const uint8_t *data, size_t len){

    esp_now_send(peer_addr, data, len);
    return ESP_OK;
}

void recv_cb(const esp_now_recv_info_t * esp_now_info, const uint8_t *bilgi, int data_len){

    // ESP_LOGI(TAG, "Data Received: " MACSTR " %s", MAC2STR(esp_now_info->src_addr), data);
    memcpy(data, bilgi, sizeof(data));
    if(data[0] < 0 && data[0] != -1){

        data[0] = data[0] * -1;
        isTarget = true;
    }
    else{

        isTarget = false;
    }

    fixLocation();
}

// ----------

// --------------------------------------------------

// -----------Calculate Manual Servo Value-----------

int calculate(int position){

    if(position >= 620 && position <= 780){             // 1.

        position = 0;
    }
    else if(position > 780 && position < 850){          // 2.

        position = 1;
    }
    else if(position < 620 && position > 550){          // 3.

        position = 2;
    }
    else if(position <= 550){                           // 4.

        position = 2;
    }
    else if(position >= 850){                           // 5.

        position = 1;
    }

    return position;
}

// --------------------------------------------------


// -------------------fixLocation--------------------

float real_lat = -1;
float real_lng = -1;

void fixLocation(){


    int degrees = (int)data[0] / 100;
    float minutes = data[0] - ((float) degrees * 100.0);
    real_lat = degrees + (minutes / 60.0);

    degrees = (int)data[1] / 100;
    minutes = data[1] - ((float) degrees * 100.0);
    real_lng = degrees + (minutes / 60.0);

    printf("lat: %f\t\tlng: %f\n", real_lat, real_lng);
}

// --------------------------------------------------


// ---------------------Main-------------------------

void app_main(void){

    ESP_ERROR_CHECK(init_wifi());
    ESP_ERROR_CHECK(init_esp_now());
    ESP_ERROR_CHECK(register_peer(peer_mac));

    // ----------Joystick----------

    int xRaw = 0;
    int yRaw = 0;

    adc_oneshot_unit_handle_t adc1_handle;
    adc_oneshot_unit_init_cfg_t init_config1 = {

        .unit_id = ADC_UNIT_1,
        .ulp_mode = ADC_ULP_MODE_DISABLE,
    };
    ESP_ERROR_CHECK(adc_oneshot_new_unit(&init_config1, &adc1_handle));

    adc_oneshot_chan_cfg_t joystickXvalueOneshotConfig = {

        .atten          = ADC_ATTEN_DB_12,
        .bitwidth       = ADC_BITWIDTH_12
    };
    ESP_ERROR_CHECK(adc_oneshot_config_channel(adc1_handle, ADC_CHANNEL_3, &joystickXvalueOneshotConfig));

    adc_oneshot_chan_cfg_t joystickYvalueOneshotConfig = {

        .atten          = ADC_ATTEN_DB_12,
        .bitwidth       = ADC_BITWIDTH_12
    };
    ESP_ERROR_CHECK(adc_oneshot_config_channel(adc1_handle, ADC_CHANNEL_4, &joystickYvalueOneshotConfig));

    // --------------------

    #define isTargetPIN 16

    int dataToSend[2] = {0, 0};
    gpio_set_direction(isTargetPIN, GPIO_MODE_OUTPUT);

    while(true){

        // Read Joystick
        adc_oneshot_read(adc1_handle, ADC_CHANNEL_3, &xRaw);
        adc_oneshot_read(adc1_handle, ADC_CHANNEL_4, &yRaw);

        dataToSend[0] = map(xRaw, 0, 4096, 0, 1024);
        dataToSend[1] = map(yRaw, 0, 4096, 0, 1024);

        dataToSend[0] = calculate(dataToSend[0]);
        dataToSend[1] = calculate(dataToSend[1]);

        if(isTarget){

            gpio_set_level(isTargetPIN, 1);
        }
        else{

            gpio_set_level(isTargetPIN, 0);
        }


        esp_now_send_data(peer_mac, (const uint8_t *)dataToSend, sizeof(dataToSend));
        delay(10);
    }
}

// --------------------------------------------------
