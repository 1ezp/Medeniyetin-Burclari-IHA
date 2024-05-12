# idf.py

## Building Project
idf.py set-target esp32s3
idf.py menuconfig
idf.py build

## Monitor
idf.py monitor
CTRL+]

# CMakeLists.txt

## main

idf_component_register(SRCS "main.c"
                        INCLUDE_DIRS "")

## home

cmake_minimum_required(VERSION 3.16)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(PROJECT_NAME)


# Kconfig.projbuild

menu "WIFI"

    config SSID
        string "SSID"
        default "myssid"

    config "PASSWORD"
        string "PASSWORD"
        default "mypassword"

endmenu


When using these inside the main.c

```cpp
#include "sdkconfig.h"

CONFIG_PASSWORD
CONFIG_SSID

```

# Helpful Commands

printenv ENV_Variable


# Programming

## ALL LIBRARIES

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

## Timing

```cpp
esp_timer_get_time() / 1000
```

## Easier Functions

```cpp
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
```

## Task

```cpp
xTaskCreate(vTask1, "vTask1", 2048, NULL, 1, NULL, 0);
//                             ^          ^        ^
//                             |__Memory  |        |___________Core Number
//                                        |_____ Priorety

SemaphoreHandle_t vTask1Semaphore = NULL;

vTask1Semaphore = xSemaphoreCreateBinary();

void vTask1(void *pvParameters){

    xSemaphoreGive(vTask1Semaphore);
    vTaskDelete(NULL);
}

if(xSemaphoreTake(vTask1Semaphore, portMAX_DELAY)){

    printf("vTask1 Executed\n");
}
```

In semaphore you can either make xSemaphoreCreateBinary or xSemaphoreCreateMutex

The diffrence is that Mutex will lock the Semaphore, by taking when the execution has started, and giving when finished.
If not finished and then taken by another task, It will wait until unlocked then execute.

While in Binary, when it tries to takes and the task has not given yet, it will wait until given



## GPIO

```cpp
#include "driver/gpio.h"

gpio_set_direction(LEDPIN, GPIO_MODE_OUTPUT);
gpio_set_level(LEDPIN, 1);
gpio_set_level(LEDPIN, 0);

```

## ADC (analogRead)

Check the pdf for the GPIO pins and the corresponding channel number (page 1447), check the oneshot for the programming channel number term

```cpp
#include "driver/adc.h"

// Create adc1 or adc2 handle
adc_oneshot_unit_handle_t adc1_handle;

// Make the config for the adc
adc_oneshot_unit_init_cfg_t init_config1 = {

    .unit_id = ADC_UNIT_1,
    .ulp_mode = ADC_ULP_MODE_DISABLE,
};

// Assign the config to the handler
ESP_ERROR_CHECK(adc_oneshot_new_unit(&init_config1, &adc1_handle));

// Make the config for the expected electricity
adc_oneshot_chan_cfg_t potConfig = {

    .atten          = ADC_ATTEN_DB_12,
    .bitwidth       = ADC_BITWIDTH_12
};
ESP_ERROR_CHECK(adc_oneshot_config_channel(adc1_handle, ADC_CHANNEL_5, &potConfig));

// Assign the read to raw
adc_oneshot_read(adc1_handle, ADC_CHANNEL_5, &raw);

```


## LEDC (PWM)

```cpp
#include "driver/ledc.h"
#include "esp_err.h"

#define led1TimerNum            LEDC_TIMER_0
#define led1Mode                LEDC_LOW_SPEED_MODE
#define led1ChannelNum          LEDC_CHANNEL_0
#define led1DutyRes             LEDC_TIMER_8_BIT
#define led1Freq                (4000)

int led1Duty = (256);
#define led1OutputPin       (13)

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


```


## Servo

```cpp
#include "driver/mcpwm_prelude.h"
#include "driver/adc.h"

#define SERVO_MIN_PULSEWIDTH_US     500  // Minimum pulse width in microsecond
#define SERVO_MAX_PULSEWIDTH_US     2500  // Maximum pulse width in microsecond
#define SERVO_MIN_DEGREE            -90   // Minimum angle
#define SERVO_MAX_DEGREE            90    // Maximum angle

#define SERVO_PULSE_GPIO             4        // GPIO connects to the PWM signal line
#define SERVO_TIMEBASE_RESOLUTION_HZ 1000000  // 1MHz, 1us per tick
#define SERVO_TIMEBASE_PERIOD        20000    // 20000 ticks, 20ms

static inline uint32_t example_angle_to_compare(int angle){

    return (angle - SERVO_MIN_DEGREE) * (SERVO_MAX_PULSEWIDTH_US - SERVO_MIN_PULSEWIDTH_US) / (SERVO_MAX_DEGREE - SERVO_MIN_DEGREE) + SERVO_MIN_PULSEWIDTH_US;
}


// Create timer and operator

mcpwm_timer_handle_t timer = NULL;
mcpwm_timer_config_t timer_config = {
    .group_id = 0,
    .clk_src = MCPWM_TIMER_CLK_SRC_DEFAULT,
    .resolution_hz = SERVO_TIMEBASE_RESOLUTION_HZ,
    .period_ticks = SERVO_TIMEBASE_PERIOD,
    .count_mode = MCPWM_TIMER_COUNT_MODE_UP,
};
ESP_ERROR_CHECK(mcpwm_new_timer(&timer_config, &timer));

mcpwm_oper_handle_t oper = NULL;
mcpwm_operator_config_t operator_config = {
    .group_id = 0, // operator must be in the same group to the timer
};
ESP_ERROR_CHECK(mcpwm_new_operator(&operator_config, &oper));

// Connect timer and operator
ESP_ERROR_CHECK(mcpwm_operator_connect_timer(oper, timer));

// Create comparator and generator from the operator

mcpwm_cmpr_handle_t comparator = NULL;
mcpwm_comparator_config_t comparator_config = {
    .flags.update_cmp_on_tez = true,
};
ESP_ERROR_CHECK(mcpwm_new_comparator(oper, &comparator_config, &comparator));

mcpwm_gen_handle_t generator = NULL;
mcpwm_generator_config_t generator_config = {
    .gen_gpio_num = SERVO_PULSE_GPIO,
};
ESP_ERROR_CHECK(mcpwm_new_generator(oper, &generator_config, &generator));

// Set generator action on timer and compare event

// Go high on counter empty
ESP_ERROR_CHECK(mcpwm_generator_set_action_on_timer_event(generator,
                                                          MCPWM_GEN_TIMER_EVENT_ACTION(MCPWM_TIMER_DIRECTION_UP, MCPWM_TIMER_EVENT_EMPTY, MCPWM_GEN_ACTION_HIGH)));
// Go low on compare threshold
ESP_ERROR_CHECK(mcpwm_generator_set_action_on_compare_event(generator,
                                                            MCPWM_GEN_COMPARE_EVENT_ACTION(MCPWM_TIMER_DIRECTION_UP, comparator, MCPWM_GEN_ACTION_LOW)));

// Enable and start timer
ESP_ERROR_CHECK(mcpwm_timer_enable(timer));
ESP_ERROR_CHECK(mcpwm_timer_start_stop(timer, MCPWM_TIMER_START_NO_STOP));


// Writing Command
ESP_ERROR_CHECK(mcpwm_comparator_set_compare_value(comparator, example_angle_to_compare(angle)));
```
