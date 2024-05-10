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
// #include "driver/adc.h"

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
```

## Task

```cpp
xTaskCreate(vTask1, "vTask1", 2048, NULL, 1, NULL);

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
