// --------------------Libraries---------------------

// C
#include <stdio.h>
#include <stdlib.h>
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
#include "driver/uart.h"
// #include "esp_adc/adc_oneshot.h"
// #include "esp_adc/adc_continuous.h"
// Servo
#include "driver/mcpwm_prelude.h"
#include "driver/adc.h"
#include "math.h"

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

static uint8_t peer_mac [ESP_NOW_ETH_ALEN] = {0x48, 0x27, 0xe2, 0xfc, 0x30, 0x7c};  // Transmitter mac

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

        // ESP_LOGI(TAG, "Send Failed");
    }
}

// ----------

typedef struct {
    float gpsLatLng[2];
    short int targetLocation[2];
} my_data_t;

my_data_t dataToSend;

char data[3] = {'C', 'C', 'A'};

bool isManual = true;
bool isPixhawlk = false;
bool isPID = false;
bool isShutdown = false;

bool isTarget = true;               // When the AI camera has the target's location

long long int timeoutMillis = 0;

static esp_err_t esp_now_send_data(const uint8_t *peer_addr, const uint8_t *data, size_t len){

    esp_now_send(peer_addr, data, len);
    return ESP_OK;
}

void checkMode();
void recv_cb(const esp_now_recv_info_t * esp_now_info, const uint8_t *bilgi, int data_len){

    // ESP_LOGI(TAG, "Data Received: " MACSTR " %s", MAC2STR(esp_now_info->src_addr), bilgi);
    memcpy(data, bilgi, sizeof(data));
    timeoutMillis =  esp_timer_get_time() / 1000;
    checkMode();
}

// ----------

// --------------------------------------------------

// ------------------setPlaneMode--------------------

void checkMode(){

    if(data[0] == 'C' || data[0] == 'A' || data[0] == 'B'){

        isManual = true;
        isPixhawlk = false;
        isPID = false;
        isShutdown = false;
    }
    else if(data[0] == 'D'){

        isManual = false;
        isPixhawlk = true;
        isPID = false;
        isShutdown = false;
    }
    else if(data[0] == 'E'){

        isManual = false;
        isPixhawlk = false;
        isPID = true;
        isShutdown = false;
    }
    else if(data[0] == 'F'){

        isManual = false;
        isPixhawlk = false;
        isPID = false;
        isShutdown = true;
    }
}

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

// Task locking
bool isManualTaskOpen = true;

// X, Y angles
short int currentXAngle = 0;
short int currentYAngle = 0;

// Sensetivity
long long int previousRlMillis = 0;
long long int previousUdMillis = 0;

long long int sensetivityX = 0;
long long int sensetivityY = 0;

#define sensitivityTimeout 75
#define servoPillTimeout 10

// PWM timers
bool didntAssignTimer = true;

// Speed Motor
double speed = 0;

#define motorTimerNum            LEDC_TIMER_2
#define motorMode                LEDC_LOW_SPEED_MODE
#define motorChannelNum          LEDC_CHANNEL_2
#define motorDutyRes             LEDC_TIMER_10_BIT
#define motorFreq                (4000)

int motorDuty = (256);
#define motorOutputPin       (5)

// Pre-declaring
mcpwm_timer_handle_t rlTimer = NULL;
mcpwm_oper_handle_t rlOper = NULL;
mcpwm_cmpr_handle_t rlComparator = NULL;
mcpwm_gen_handle_t rlGenerator = NULL;

mcpwm_timer_handle_t udTimer = NULL;
mcpwm_oper_handle_t udOper = NULL;
mcpwm_cmpr_handle_t udComparator = NULL;
mcpwm_gen_handle_t udGenerator = NULL;

void servoWrite(void *pvParameters){

    // -------Task---------

    isManualTaskOpen = false;

    // --------------------

    if(didntAssignTimer){

        didntAssignTimer = false;

        // ------rlServo-------

        mcpwm_timer_config_t rlTimer_config = {
            .group_id = 0,
            .clk_src = MCPWM_TIMER_CLK_SRC_DEFAULT,
            .resolution_hz = SERVO_TIMEBASE_RESOLUTION_HZ,
            .period_ticks = SERVO_TIMEBASE_PERIOD,
            .count_mode = MCPWM_TIMER_COUNT_MODE_UP,
        };
        ESP_ERROR_CHECK(mcpwm_new_timer(&rlTimer_config, &rlTimer));

        mcpwm_operator_config_t rlOper_config = {
            .group_id = 0, // operator must be in the same group to the timer
        };
        ESP_ERROR_CHECK(mcpwm_new_operator(&rlOper_config, &rlOper));

        ESP_ERROR_CHECK(mcpwm_operator_connect_timer(rlOper, rlTimer));

        mcpwm_comparator_config_t rlComparator_config = {
            .flags.update_cmp_on_tez = true,
        };
        ESP_ERROR_CHECK(mcpwm_new_comparator(rlOper, &rlComparator_config, &rlComparator));

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

        mcpwm_timer_config_t udTimer_config = {
            .group_id = 1,
            .clk_src = MCPWM_TIMER_CLK_SRC_DEFAULT,
            .resolution_hz = SERVO_TIMEBASE_RESOLUTION_HZ,
            .period_ticks = SERVO_TIMEBASE_PERIOD,
            .count_mode = MCPWM_TIMER_COUNT_MODE_UP,
        };
        ESP_ERROR_CHECK(mcpwm_new_timer(&udTimer_config, &udTimer));

        mcpwm_operator_config_t udOper_config = {
            .group_id = 1, // operator must be in the same group to the timer
        };
        ESP_ERROR_CHECK(mcpwm_new_operator(&udOper_config, &udOper));

        ESP_ERROR_CHECK(mcpwm_operator_connect_timer(udOper, udTimer));

        mcpwm_comparator_config_t udComparator_config = {
            .flags.update_cmp_on_tez = true,
        };
        ESP_ERROR_CHECK(mcpwm_new_comparator(udOper, &udComparator_config, &udComparator));

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
    }

    // --------------------

    // -------Manual-------

    sensetivityX = (esp_timer_get_time() / 1000);
    sensetivityY = (esp_timer_get_time() / 1000);

    while(isManual){

    // ---------X----------

        // When the joystick is in the middle
        if(data[0] == 'C' && data[1] == 'C'){

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
        else if(data[0] == 'A'){

            previousRlMillis = esp_timer_get_time() / 1000;

            if((esp_timer_get_time() / 1000) - sensetivityX >= sensitivityTimeout){

                currentXAngle+=5;
                sensetivityX = (esp_timer_get_time() / 1000);
            }
        }

        // When the joystick is in the left
        else if(data[0] == 'B'){

            previousRlMillis = esp_timer_get_time() / 1000;

            if((esp_timer_get_time() / 1000) - sensetivityX >= sensitivityTimeout){

                currentXAngle-=5;
                sensetivityX = (esp_timer_get_time() / 1000);
            }
        }

        // --------------------

        // ---------Y----------

        // When the joystick is in the middle
        if(data[1] == 'C' && data[1] == 'C'){

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
        else if(data[1] == 'B'){

            previousUdMillis = esp_timer_get_time() / 1000;

            if((esp_timer_get_time() / 1000) - sensetivityY >= sensitivityTimeout){

                currentYAngle-=5;
                sensetivityY = (esp_timer_get_time() / 1000);
            }
        }

        // When the joystick is in the top
        else if(data[1] == 'A'){

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

        // --------------------

        if(data[2] != 'A'){

            double rangePerChar = 1024.0 / 26.0;
            int charIndex = data[2] - 'A' + 1;
            speed = charIndex * rangePerChar;
            speed = (int)round(speed);
        }
        else{

            speed = 0.0;
        }

        // --------------------

        // -------Write--------

        printf("%f\n", speed);
        ESP_ERROR_CHECK(mcpwm_comparator_set_compare_value(rlComparator, example_angle_to_compare(currentXAngle)));
        ESP_ERROR_CHECK(mcpwm_comparator_set_compare_value(udComparator, example_angle_to_compare(currentYAngle)));
        analogWrite(motorMode, motorChannelNum, speed);
        delay(10);

        // --------------------
    }

    // --------------------

    // --------Task---------

    analogWrite(motorMode, motorChannelNum, 0);
    isManualTaskOpen = true;
    vTaskDelete(NULL);

    // --------------------
}

// --------------------------------------------------


// ---------------------GPS--------------------------

static const int RX_BUF_SIZE = 2048;

#define TXD_PIN 17
#define RXD_PIN 18

float latitude, longitude;

bool isWritingGpsBusy = false;

void gpsInit(){

    const uart_config_t gps_uart_config = {

        .baud_rate = 9600,
        .data_bits = UART_DATA_8_BITS,
        .parity    = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_APB
    };

    uart_driver_install(UART_NUM_1, RX_BUF_SIZE*2, 0, 0, NULL, 0);
    uart_param_config(UART_NUM_1, &gps_uart_config);
    uart_set_pin(UART_NUM_1, TXD_PIN, RXD_PIN, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
}

void gpsRead(){

    uint8_t* data = (uint8_t*)malloc(RX_BUF_SIZE+1);

    while(true){

        const int rxBytes = uart_read_bytes(UART_NUM_1, data, RX_BUF_SIZE, 350 / portTICK_PERIOD_MS);
        if(rxBytes > 0){

            data[rxBytes] = 0;

            // Find GNGLL line
            char* gngll = strstr((const char*)data, "$GNGLL");

            if(gngll != NULL){

                isWritingGpsBusy = true;
                delay(15);

                // Extract latitude and longitude
                if(sscanf(gngll, "$GNGLL,%f,N,%f,E", &latitude, &longitude) == 2){

                    dataToSend.gpsLatLng[0] = latitude;
                    dataToSend.gpsLatLng[1] = longitude;
                }
                else{

                    dataToSend.gpsLatLng[0] = -1;
                    dataToSend.gpsLatLng[1] = -1;
                }

                isWritingGpsBusy = false;
                delay(15);
            }
        }
    }

    free(data);
}

// --------------------------------------------------


// -------------------SendingTask---------------------

void sendGps(){

    while(true){

        while(!isWritingGpsBusy){

            esp_now_send_data(peer_mac, (const uint8_t *)&dataToSend, sizeof(dataToSend));
            delay(10);
        }

        delay(10);
    }
}

// --------------------------------------------------


// --------------------PinSetup----------------------

#define pixhawlkPin 4
#define shutdownPin 6

void initPins(){

    gpio_config_t io_conf;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = (1ULL << pixhawlkPin) | (1ULL << shutdownPin);
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 0;
    gpio_config(&io_conf);
}

static void motorInit(void){

    // motor timer configuration
    ledc_timer_config_t motorTimer = {

        .speed_mode       = motorMode,
        .duty_resolution  = motorDutyRes,
        .timer_num        = motorTimerNum,
        .freq_hz          = motorFreq,
        .clk_cfg          = LEDC_AUTO_CLK
    };
    ESP_ERROR_CHECK(ledc_timer_config(&motorTimer));

    // motor channel configuration
    ledc_channel_config_t motorChannel = {
        .speed_mode     = motorMode,
        .channel        = motorChannelNum,
        .timer_sel      = motorTimerNum,
        .intr_type      = LEDC_INTR_DISABLE,
        .gpio_num       = motorOutputPin,
        .duty           = 0,
        .hpoint         = 0
    };
    ESP_ERROR_CHECK(ledc_channel_config(&motorChannel));
}

// --------------------------------------------------


// ---------------------Main-------------------------

void app_main(void){

    ESP_ERROR_CHECK(init_wifi());
    ESP_ERROR_CHECK(init_esp_now());
    ESP_ERROR_CHECK(register_peer(peer_mac));
    initPins();
    motorInit();

    dataToSend.gpsLatLng[0] = -1;
    dataToSend.gpsLatLng[1] = -1;
    dataToSend.targetLocation[0] = -1;
    dataToSend.targetLocation[1] = -1;


    // --------GPS---------

    gpsInit();
    xTaskCreate(gpsRead, "gpsRead", 1024*2, NULL, 1, NULL);

    // --------------------

    xTaskCreate(sendGps, "sendGps", 1024*2, NULL, 1, NULL);

    // --------------------

    while(true){

        // -------Manual-------

        if(isManual){

            gpio_set_level(pixhawlkPin, 0);
            gpio_set_level(shutdownPin, 0);

            if(isManualTaskOpen){

                previousRlMillis = esp_timer_get_time() / 1000;
                xTaskCreate(servoWrite, "servoWrite", 1024*3, NULL, 1, NULL);
            }
        }

        // -------Auto---------

        else if(isPixhawlk){

            gpio_set_level(pixhawlkPin, 1);
            gpio_set_level(shutdownPin, 0);
        }

        // --------------------

        // --------PID---------

        else if(isPID){

            gpio_set_level(pixhawlkPin, 0);
            gpio_set_level(shutdownPin, 0);
        }

        // --------------------

        // ------Shutdown------

        else if(isShutdown){

            gpio_set_level(pixhawlkPin, 0);
            gpio_set_level(shutdownPin, 1);
        }

        // --------------------

        // ------Timeout-------

        if((esp_timer_get_time() / 1000) - timeoutMillis >= 100){

            if(isManual){

                isManual = false;
                isPixhawlk = true;
                isPID = false;
                isShutdown = false;
            }
        }

        // --------------------

        delay(10);
    }
}

// --------------------------------------------------
