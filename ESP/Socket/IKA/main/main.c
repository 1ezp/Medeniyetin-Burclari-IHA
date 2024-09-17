// C
#include <stdio.h>
#include <math.h>
// freeRTOS
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
// Task
#include <esp_log.h>
#include <esp_timer.h>
// Communication
#include <esp_wifi.h>
#include <nvs_flash.h>
#include <lwip/sockets.h>
// Electric
#include <driver/gpio.h>
#include <driver/uart.h>
#include <driver/ledc.h>
// Servo
#include <driver/mcpwm_prelude.h>
#include <driver/adc.h>
// Project Files
#include "Project/Functions.c"
#include "Project/Pins/initServo.c"
#include "Project/Pins/initPwm.c"
#include "Project/Pins/initPins.c"
#include "Project/Modes/movement.c"
#include "Project/Modes/modesAdjuster.c"
#include "Project/Communication/initWifi.c"
#include "Project/Communication/initSocket.c"
#include "Project/GPS/initGps.c"

void app_main() {

    init_pins();
    xTaskCreate(wifiTask, "wifiTask", 1024*3, NULL, 1, NULL);       // Creates Socket Task 1024*4
    init_gps();
    xTaskCreate(gpsTask, "gpsTask", 1024*3, NULL, 1, NULL);

    shutdownAllPins();

    while(true){

        adjustMode(&data[0]);
        printf("%d,%d\n", data[0], data[1]);
        delay(25);
    }
}
