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
#include "driver/spi_master.h"
// #include "driver/i2c_master.h"
// #include "i2c_eeprom.h"
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

    // Use 802.11b for better range
    esp_wifi_set_protocol(WIFI_IF_STA, WIFI_PROTOCOL_11B);

    // Set long range mode
    esp_wifi_set_protocol(WIFI_IF_STA, WIFI_PROTOCOL_LR);

    // Set Wi-Fi transmission power to maximum
    esp_wifi_set_max_tx_power(84);

    // Set the lowest phy rate for maximum range
    esp_wifi_config_espnow_rate(WIFI_IF_STA, WIFI_PHY_RATE_LORA_250K);

    // Set power saving to none
    esp_wifi_set_ps(WIFI_PS_NONE);

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

bool targetLostOverride = false;

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

        targetLostOverride = false;
    }
    else if(data[0] == 'D'){

        isManual = false;
        isPixhawlk = true;
        isPID = false;
        isShutdown = false;

        targetLostOverride = false;
    }
    else if(data[0] == 'F'){

        isManual = false;
        isPixhawlk = false;
        isPID = false;
        isShutdown = true;

        targetLostOverride = false;
    }
    else if(data[0] == 'E' && !targetLostOverride){

        isManual = false;
        isPixhawlk = false;
        isPID = true;
        isShutdown = false;
    }
    else if(data[0] == 'G'){

        isManual = false;
        isPixhawlk = false;
        isPID = true;
        isShutdown = false;

        targetLostOverride = false;

    }
}

// --------------------------------------------------


// ---------------------Servo------------------------

#define SERVO_MIN_PULSEWIDTH_US     500  // Minimum pulse width in microsecond
#define SERVO_MAX_PULSEWIDTH_US     2500  // Maximum pulse width in microsecond
#define SERVO_MIN_DEGREE            -90   // Minimum angle
#define SERVO_MAX_DEGREE            90    // Maximum angle

#define SERVO_PULSE_GPIO_RL             21        // GPIO connects to the PWM signal line
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
#define servoPillTimeout 50

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

void assignServoTimers(){

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

void servoWrite(void *pvParameters){

    // -------Task---------

    isManualTaskOpen = false;

    // -------Timer--------

    if(didntAssignTimer){

        assignServoTimers();
    }

    // --------------------

    // -------Manual-------

    sensetivityX = (esp_timer_get_time() / 1000);
    sensetivityY = (esp_timer_get_time() / 1000);

    while(isManual){

    // ---------X----------

        // When the joystick is in the middle
        if(data[0] == 'C'){

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

                currentXAngle-=5;
                sensetivityX = (esp_timer_get_time() / 1000);
            }
        }

        // When the joystick is in the left
        else if(data[0] == 'B'){

            previousRlMillis = esp_timer_get_time() / 1000;

            if((esp_timer_get_time() / 1000) - sensetivityX >= sensitivityTimeout){

                currentXAngle+=5;
                sensetivityX = (esp_timer_get_time() / 1000);
            }
        }

        // --------------------

        // ---------Y----------

        // When the joystick is in the middle
        if(data[1] == 'C'){

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

        ESP_ERROR_CHECK(mcpwm_comparator_set_compare_value(rlComparator, example_angle_to_compare(currentXAngle)));
        ESP_ERROR_CHECK(mcpwm_comparator_set_compare_value(udComparator, example_angle_to_compare(currentYAngle)));
        analogWrite(motorMode, motorChannelNum, speed);
        delay(10);

        // --------------------
    }

    // --------------------

    // --------Task---------

    currentXAngle = 0;
    currentYAngle = 0;
    ESP_ERROR_CHECK(mcpwm_comparator_set_compare_value(rlComparator, example_angle_to_compare(currentXAngle)));
    ESP_ERROR_CHECK(mcpwm_comparator_set_compare_value(udComparator, example_angle_to_compare(currentYAngle)));
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

// For Camera
bool isWritingCameraBusy = false;

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

        while(!isWritingGpsBusy && !isWritingCameraBusy){

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


// --------------------Camera------------------------

#define PIN_NUM_MISO 12
#define PIN_NUM_MOSI 13
#define PIN_NUM_CLK  14
#define PIN_NUM_CS   11

void parseTarget(uint8_t *recvbuf);
void cameraRead() {

    spi_device_handle_t handle_tx;
    spi_device_handle_t handle_rx;
    spi_bus_config_t buscfg = {
        .mosi_io_num = PIN_NUM_MOSI,
        .miso_io_num = PIN_NUM_MISO,
        .sclk_io_num = PIN_NUM_CLK,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1
    };

    spi_device_interface_config_t devcfg_tx = {
        .command_bits = 0,
        .address_bits = 0,
        .dummy_bits = 0,
        .clock_speed_hz = 2000000,
        .duty_cycle_pos = 128, // 50% duty cycle
        .mode = 0,
        .spics_io_num = PIN_NUM_CS,
        .cs_ena_posttrans = 3, // Keep the CS low 3 cycles after transaction
        .queue_size = 3
    };

    spi_device_interface_config_t devcfg_rx = {
        .command_bits = 0,
        .address_bits = 0,
        .dummy_bits = 0,
        .clock_speed_hz = 2000000,
        .duty_cycle_pos = 128, // 50% duty cycle
        .mode = 0,
        .spics_io_num = PIN_NUM_CS,
        .cs_ena_posttrans = 3, // Keep the CS low 3 cycles after transaction
        .queue_size = 3
    };

    uint8_t blockRequest[] = {0xae, 0xc1, 0x20, 0x02, 0xff, 0xff};
    uint8_t recvbuf[128];

    spi_transaction_t t_tx;
    spi_transaction_t t_rx;
    memset(&t_tx, 0, sizeof(t_tx));
    memset(&t_rx, 0, sizeof(t_rx));

    esp_err_t ret;

    // Initialize SPI bus
    ret = spi_bus_initialize(SPI3_HOST, &buscfg, SPI_DMA_CH_AUTO);
    assert(ret == ESP_OK);

    // Add transmit device
    ret = spi_bus_add_device(SPI3_HOST, &devcfg_tx, &handle_tx);
    assert(ret == ESP_OK);

    // Add receive device
    ret = spi_bus_add_device(SPI3_HOST, &devcfg_rx, &handle_rx);
    assert(ret == ESP_OK);

    while (true) {

        memset(recvbuf, 0, sizeof(recvbuf));

        // Prepare transmit transaction
        t_tx.length = sizeof(blockRequest) * 8; // Total bits to be sent
        t_tx.tx_buffer = blockRequest;

        // Prepare receive transaction
        t_rx.length = sizeof(recvbuf) * 8; // Total bits expected to be received
        t_rx.rxlength = t_rx.length; // Ensure rxlength matches length
        t_rx.rx_buffer = recvbuf;

        // Transmit and receive
        ret = spi_device_transmit(handle_tx, &t_tx);
        assert(ret == ESP_OK);
        ret = spi_device_transmit(handle_rx, &t_rx);
        assert(ret == ESP_OK);

        parseTarget(recvbuf);

        delay(50);
    }
}

void parseTarget(uint8_t *recvbuf){

    bool pattern_found = false;

    for (int i = 0; i < 128; i++){

        if (recvbuf[i] == 0xaf && recvbuf[i + 1] == 0xc1) {

            if(recvbuf[i+2] == 0x21 && recvbuf[i+3] != 0x00){

                isWritingCameraBusy = true;

                if(recvbuf[i+9] == 0x01){

                    dataToSend.targetLocation[0] = (int)recvbuf[i + 8] + 255;
                }
                else{

                    dataToSend.targetLocation[0] = (int)recvbuf[i + 8];
                }

                dataToSend.targetLocation[1] = (int)recvbuf[i + 10];

                pattern_found = true;
                isWritingCameraBusy = false;
                break;
            }
            else{

                break;
            }
        }
    }

    if (!pattern_found) {

        dataToSend.targetLocation[0] = -1;
        dataToSend.targetLocation[1] = -1;
    }
}

// --------------------------------------------------


// ---------------------PID--------------------------

long long int previousPIDMillis = 0;
long long int targetTimoutMillis = 0;

#define setpointX 157.5                      // PID values
#define setpointY 103.5
double outputX;
double outputY;

#define KP 0.02
#define KI 0.005
#define KD 0.002

double dt = 1;

double prevErrorX = 0;                     // PID variables
double integralX = 0;

double prevErrorY = 0;
double integralY = 0;

bool isPIDTaskOpen = true;
bool shouldCalculate = true;

void calculatePIDForX(){

    double error = setpointX - dataToSend.targetLocation[0];

    double propotional = error;

    integralX += error * dt;

    double derevetive = (error - prevErrorX) / dt;

    prevErrorX = error;

    outputX = (KP * propotional) + (KI * integralX) + (KD * derevetive);

    if(outputX > 100){

        outputX = 100;
    }
    else if(outputX < -100){

        outputX = -100;
    }

    currentXAngle += outputX;

    if(currentXAngle > 90){

        currentXAngle = 90;
    }
    else if(currentXAngle < -90){

        currentXAngle = -90;
    }

}

void calculatePIDForY() {

    double error = setpointY - dataToSend.targetLocation[1];

    double propotional = error;

    integralY += error * dt;

    double derevetive = (error - prevErrorY) / dt;

    prevErrorY = error;

    outputY = (KP * propotional) + (KI * integralY) + (KD * derevetive);

    if(outputY > 100){

        outputY = 100;
    }
    else if(outputY < -100){

        outputY = -100;
    }

    currentYAngle += outputY;

    if(currentYAngle > 90){

        currentYAngle = 90;
    }
    else if(currentYAngle < -90){

        currentYAngle = -90;
    }
}

void resetValues(){

    targetTimoutMillis = esp_timer_get_time() / 1000;
    previousPIDMillis = 0;
    dt = 1;

    prevErrorX = 0;
    integralX = 0;

    prevErrorY = 0;
    integralY = 0;

    outputX = 0;
    outputY = 0;
}

void PIDTask(){

    isPIDTaskOpen = false;

    currentXAngle = 0;
    currentYAngle = 0;
    resetValues();

    if(didntAssignTimer){

        assignServoTimers();
    }

    while(isPID){

        if(dataToSend.targetLocation[0] != -1){

            targetTimoutMillis = esp_timer_get_time() / 1000;
            shouldCalculate = true;
        }
        else{

            shouldCalculate = false;
        }

        if(((esp_timer_get_time() / 1000) - targetTimoutMillis) >= 4000){

            isManual = false;
            isPixhawlk = true;
            isPID = false;
            isShutdown = false;

            targetLostOverride = true;

            break;
        }

        dt = ((esp_timer_get_time() / 1000) - previousPIDMillis) / 1000.0;
        previousPIDMillis = esp_timer_get_time() / 1000;

        if(shouldCalculate){

            calculatePIDForX();
            calculatePIDForY();
            ESP_ERROR_CHECK(mcpwm_comparator_set_compare_value(rlComparator, example_angle_to_compare(currentXAngle)));
            ESP_ERROR_CHECK(mcpwm_comparator_set_compare_value(udComparator, example_angle_to_compare(currentYAngle)));
        }

        delay(25);
    }

    currentXAngle = 0;
    currentYAngle = 0;
    ESP_ERROR_CHECK(mcpwm_comparator_set_compare_value(rlComparator, example_angle_to_compare(currentXAngle)));
    ESP_ERROR_CHECK(mcpwm_comparator_set_compare_value(udComparator, example_angle_to_compare(currentYAngle)));

    isPIDTaskOpen = true;
    vTaskDelete(NULL);
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

    // -------Camera-------

    xTaskCreate(cameraRead, "cameraRead", 1024*3, NULL, 1, NULL);

    // --------------------


    while(true){

        // -------Manual-------

        if(isManual){

            gpio_set_level(pixhawlkPin, 0);
            gpio_set_level(shutdownPin, 0);

            if(isManualTaskOpen){

                previousRlMillis = esp_timer_get_time() / 1000;
                previousUdMillis = esp_timer_get_time() / 1000;
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

            shouldCalculate = true;

            if(isPIDTaskOpen){

                xTaskCreate(PIDTask, "PIDTask", 1024*3, NULL, 1, NULL);
            }
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

            currentXAngle = 0;
            currentYAngle = 0;
        }

        // --------------------

        delay(10);
    }
}

// --------------------------------------------------
