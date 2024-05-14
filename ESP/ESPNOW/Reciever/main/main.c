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
// #include "esp_adc/adc_oneshot.h"
// #include "esp_adc/adc_continuous.h"
// Servo
#include "driver/mcpwm_prelude.h"
#include "driver/adc.h"

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

int data[2] = {0, 0};

bool isManual = true;
bool isPixhawlk = false;
bool isPID = false;

void recv_cb(const esp_now_recv_info_t * esp_now_info, const uint8_t *bilgi, int data_len){

    // ESP_LOGI(TAG, "Data Received: " MACSTR " %s", MAC2STR(esp_now_info->src_addr), bilgi);
    memcpy(data, bilgi, sizeof(data));
}

// ----------

// --------------------------------------------------


// ---------------------Servo------------------------

#define SERVO_MIN_PULSEWIDTH_US     500  // Minimum pulse width in microsecond
#define SERVO_MAX_PULSEWIDTH_US     2500  // Maximum pulse width in microsecond
#define SERVO_MIN_DEGREE            -90   // Minimum angle
#define SERVO_MAX_DEGREE            90    // Maximum angle

#define SERVO_PULSE_GPIO_RL             15        // GPIO connects to the PWM signal line
#define SERVO_PULSE_GPIO_UD             16        // GPIO connects to the PWM signal line
#define SERVO_TIMEBASE_RESOLUTION_HZ 1000000  // 1MHz, 1us per tick
#define SERVO_TIMEBASE_PERIOD        20000    // 20000 ticks, 20ms

static inline uint32_t example_angle_to_compare(int angle){

    return (angle - SERVO_MIN_DEGREE) * (SERVO_MAX_PULSEWIDTH_US - SERVO_MIN_PULSEWIDTH_US) / (SERVO_MAX_DEGREE - SERVO_MIN_DEGREE) + SERVO_MIN_PULSEWIDTH_US;
}

// --------------------------------------------------


// ------------------ServoTask-----------------------

bool isManualTaskOpen = true;

short int currentXAngle = 0;
short int currentYAngle = 0;

long long int previousRlMillis = 0;
long long int previousUdMillis = 0;

long long int sensetivityX = 0;
long long int sensetivityY = 0;

#define sensitivityTimeout 75
#define servoPillTimeout 100

void servoWrite(void *pvParameters){

    // -------Task---------

    isManualTaskOpen = false;

    // --------------------

    // ------rlServo-------

    mcpwm_timer_handle_t rlTimer = NULL;
    mcpwm_timer_config_t rlTimer_config = {
        .group_id = 0,
        .clk_src = MCPWM_TIMER_CLK_SRC_DEFAULT,
        .resolution_hz = SERVO_TIMEBASE_RESOLUTION_HZ,
        .period_ticks = SERVO_TIMEBASE_PERIOD,
        .count_mode = MCPWM_TIMER_COUNT_MODE_UP,
    };
    ESP_ERROR_CHECK(mcpwm_new_timer(&rlTimer_config, &rlTimer));

    mcpwm_oper_handle_t rlOper = NULL;
    mcpwm_operator_config_t rlOper_config = {
        .group_id = 0, // operator must be in the same group to the timer
    };
    ESP_ERROR_CHECK(mcpwm_new_operator(&rlOper_config, &rlOper));

    ESP_ERROR_CHECK(mcpwm_operator_connect_timer(rlOper, rlTimer));

    mcpwm_cmpr_handle_t rlComparator = NULL;
    mcpwm_comparator_config_t rlComparator_config = {
        .flags.update_cmp_on_tez = true,
    };
    ESP_ERROR_CHECK(mcpwm_new_comparator(rlOper, &rlComparator_config, &rlComparator));

    mcpwm_gen_handle_t rlGenerator = NULL;
    mcpwm_generator_config_t rlGenerator_config = {
        .gen_gpio_num = SERVO_PULSE_GPIO_RL,
    };
    ESP_ERROR_CHECK(mcpwm_new_generator(rlOper, &rlGenerator_config, &rlGenerator));

    ESP_ERROR_CHECK(mcpwm_generator_set_action_on_timer_event(rlGenerator,
                                                              MCPWM_GEN_TIMER_EVENT_ACTION(MCPWM_TIMER_DIRECTION_UP, MCPWM_TIMER_EVENT_EMPTY, MCPWM_GEN_ACTION_HIGH)));
    ESP_ERROR_CHECK(mcpwm_generator_set_action_on_compare_event(rlGenerator,
                                                                MCPWM_GEN_COMPARE_EVENT_ACTION(MCPWM_TIMER_DIRECTION_UP, rlComparator, MCPWM_GEN_ACTION_LOW)));

    ESP_ERROR_CHECK(mcpwm_timer_enable(rlTimer));
    ESP_ERROR_CHECK(mcpwm_timer_start_stop(rlTimer, MCPWM_TIMER_START_NO_STOP));

    // --------------------

    // ------udServo-------

    mcpwm_timer_handle_t udTimer = NULL;
    mcpwm_timer_config_t udTimer_config = {
        .group_id = 1,
        .clk_src = MCPWM_TIMER_CLK_SRC_DEFAULT,
        .resolution_hz = SERVO_TIMEBASE_RESOLUTION_HZ,
        .period_ticks = SERVO_TIMEBASE_PERIOD,
        .count_mode = MCPWM_TIMER_COUNT_MODE_UP,
    };
    ESP_ERROR_CHECK(mcpwm_new_timer(&udTimer_config, &udTimer));

    mcpwm_oper_handle_t udOper = NULL;
    mcpwm_operator_config_t udOper_config = {
        .group_id = 1, // operator must be in the same group to the timer
    };
    ESP_ERROR_CHECK(mcpwm_new_operator(&udOper_config, &udOper));

    ESP_ERROR_CHECK(mcpwm_operator_connect_timer(udOper, udTimer));

    mcpwm_cmpr_handle_t udComparator = NULL;
    mcpwm_comparator_config_t udComparator_config = {
        .flags.update_cmp_on_tez = true,
    };
    ESP_ERROR_CHECK(mcpwm_new_comparator(udOper, &udComparator_config, &udComparator));

    mcpwm_gen_handle_t udGenerator = NULL;
    mcpwm_generator_config_t udGenerator_config = {
        .gen_gpio_num = SERVO_PULSE_GPIO_UD,
    };
    ESP_ERROR_CHECK(mcpwm_new_generator(udOper, &udGenerator_config, &udGenerator));

    ESP_ERROR_CHECK(mcpwm_generator_set_action_on_timer_event(udGenerator,
                                                              MCPWM_GEN_TIMER_EVENT_ACTION(MCPWM_TIMER_DIRECTION_UP, MCPWM_TIMER_EVENT_EMPTY, MCPWM_GEN_ACTION_HIGH)));
    ESP_ERROR_CHECK(mcpwm_generator_set_action_on_compare_event(udGenerator,
                                                                MCPWM_GEN_COMPARE_EVENT_ACTION(MCPWM_TIMER_DIRECTION_UP, udComparator, MCPWM_GEN_ACTION_LOW)));

    ESP_ERROR_CHECK(mcpwm_timer_enable(udTimer));
    ESP_ERROR_CHECK(mcpwm_timer_start_stop(udTimer, MCPWM_TIMER_START_NO_STOP));

    // --------------------

    // -------Manual-------

    sensetivityX = (esp_timer_get_time() / 1000);
    sensetivityY = (esp_timer_get_time() / 1000);

    while(isManual){

    // ---------X----------

        // When the joystick is in the middle
        if(data[0] == 0){

            if((esp_timer_get_time() / 1000) - previousRlMillis >= servoPillTimeout){

                if(currentXAngle < 0){

                    currentXAngle+=5;
                }
                else if(currentXAngle > 0){

                    currentXAngle-=5;
                }

                previousRlMillis = (esp_timer_get_time() / 1000);
            }
        }

        // When the joystick is in the right
        else if(data[0] == 1){

            previousRlMillis = esp_timer_get_time() / 1000;

            if((esp_timer_get_time() / 1000) - sensetivityX >= sensitivityTimeout){

                currentXAngle+=5;
                sensetivityX = (esp_timer_get_time() / 1000);
            }
        }

        // When the joystick is in the left
        else if(data[0] == 2){

            previousRlMillis = esp_timer_get_time() / 1000;

            if((esp_timer_get_time() / 1000) - sensetivityX >= sensitivityTimeout){

                currentXAngle-=5;
                sensetivityX = (esp_timer_get_time() / 1000);
            }
        }

        // --------------------

        // ---------Y----------

        // When the joystick is in the middle
        if(data[1] == 0){

            if((esp_timer_get_time() / 1000) - previousUdMillis >= servoPillTimeout){

                if(currentYAngle < 0){

                    currentYAngle+=5;
                }
                else if(currentYAngle > 0){

                    currentYAngle-=5;
                }

                previousUdMillis = (esp_timer_get_time() / 1000);
            }
        }

        // When the joystick is in the bottom
        else if(data[1] == 1){

            previousUdMillis = esp_timer_get_time() / 1000;

            if((esp_timer_get_time() / 1000) - sensetivityY >= sensitivityTimeout){

                currentYAngle-=5;
                sensetivityY = (esp_timer_get_time() / 1000);
            }
        }

        // When the joystick is in the top
        else if(data[1] == 2){

            previousUdMillis = esp_timer_get_time() / 1000;

            if((esp_timer_get_time() / 1000) - sensetivityY >= sensitivityTimeout){

                currentYAngle+=5;
                sensetivityY = (esp_timer_get_time() / 1000);
            }
        }

        // --------------------

        // -------Range---------

        if(currentXAngle > 70){

            currentXAngle = 70;
        }
        else if(currentXAngle < -70){

            currentXAngle = -70;
        }
        if(currentYAngle > 70){

            currentYAngle = 70;
        }
        else if(currentYAngle < -70){

            currentYAngle = -70;
        }

        // --------------------

        // -------Write--------

        ESP_ERROR_CHECK(mcpwm_comparator_set_compare_value(rlComparator, example_angle_to_compare(currentXAngle)));
        ESP_ERROR_CHECK(mcpwm_comparator_set_compare_value(udComparator, example_angle_to_compare(currentYAngle)));
        delay(10);

        // --------------------

    }

    // --------------------

    // --------Task---------

    isManualTaskOpen = true;
    vTaskDelete(NULL);

    // --------------------
}

// --------------------------------------------------


// ---------------------Main-------------------------

#define pixhawlkPin 4

void app_main(void){

    ESP_ERROR_CHECK(init_wifi());
    ESP_ERROR_CHECK(init_esp_now());
    ESP_ERROR_CHECK(register_peer(peer_mac));

    // --------GPIO--------

    gpio_set_direction(pixhawlkPin, GPIO_MODE_OUTPUT);

    // --------------------

    while(true){

        // -------Manual-------

        if(isManual){

            gpio_set_level(pixhawlkPin, 0);

            if(isManualTaskOpen){

                previousRlMillis = esp_timer_get_time() / 1000;
                xTaskCreate(servoWrite, "servoWrite", 4096, NULL, 1, NULL);
            }
        }

        // -------Auto---------

        else if(isPixhawlk){

            isManualTaskOpen = true;
        }

        // --------------------

        // --------PID---------

        else if(isPID){

            isManualTaskOpen = true;
        }

        // --------------------

        delay(10);
    }
}

// --------------------------------------------------
