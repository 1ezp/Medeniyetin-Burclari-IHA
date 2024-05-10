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

void servoWrite(int mode, int channel, int value, int milliseconds){

    ESP_ERROR_CHECK(ledc_set_duty(mode, channel, value));
    ESP_ERROR_CHECK(ledc_update_duty(mode, channel));
    delay(milliseconds);
    ESP_ERROR_CHECK(ledc_stop(mode, channel, value));
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

static uint8_t peer_mac [ESP_NOW_ETH_ALEN] = {0x48, 0x27, 0xe2, 0xfc, 0x30, 0x76};  // Transmitter mac

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

        ESP_LOGI(TAG, "Send Success");
    }
    else{

        ESP_LOGI(TAG, "Send Failed");
    }
}

// ----------

static esp_err_t esp_now_send_data(const uint8_t *peer_addr, const uint8_t *data, size_t len){

    esp_now_send(peer_addr, data, len);
    return ESP_OK;
}

int brightness = 0;
bool firstReceive = false;

void recv_cb(const esp_now_recv_info_t * esp_now_info, const uint8_t *data, int data_len){

    ESP_LOGI(TAG, "Data Received: " MACSTR " %s", MAC2STR(esp_now_info->src_addr), data);
    firstReceive = true;
    brightness = data[0];
}

// ----------

// --------------------------------------------------

// --------------------Led1--------------------------

#define led1TimerNum            LEDC_TIMER_0
#define led1Mode                LEDC_LOW_SPEED_MODE
#define led1ChannelNum          LEDC_CHANNEL_0
#define led1DutyRes             LEDC_TIMER_8_BIT
#define led1Freq                (4000)

int led1Duty = (0);
#define led1OutputPin       (16)

static void led1Init(void){

    // led1 timer configuration
    ledc_timer_config_t led1Timer = {

        .speed_mode       = led1Mode,
        .duty_resolution  = led1DutyRes,
        .timer_num        = led1TimerNum,
        .freq_hz          = led1Freq,
        .clk_cfg          = LEDC_AUTO_CLK
    };
    ESP_ERROR_CHECK(ledc_timer_config(&led1Timer));

    // led1 channel configuration
    ledc_channel_config_t led1Channel = {
        .speed_mode     = led1Mode,
        .channel        = led1ChannelNum,
        .timer_sel      = led1TimerNum,
        .intr_type      = LEDC_INTR_DISABLE,
        .gpio_num       = led1OutputPin,
        .duty           = 0,
        .hpoint         = 0
    };
    ESP_ERROR_CHECK(ledc_channel_config(&led1Channel));
}

// --------------------------------------------------

// ---------------------Main-------------------------

void app_main(void){

    ESP_ERROR_CHECK(init_wifi());
    ESP_ERROR_CHECK(init_esp_now());
    ESP_ERROR_CHECK(register_peer(peer_mac));
    led1Init();

    while(true){

        if(firstReceive){

            analogWrite(led1Mode, led1ChannelNum, brightness);
        }

        delay(100);
    }
}

// --------------------------------------------------
