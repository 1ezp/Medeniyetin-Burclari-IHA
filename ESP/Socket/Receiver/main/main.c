// C
#include <stdio.h>
// freeRTOS
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
// Task
#include <esp_log.h>
// Communication
#include <esp_wifi.h>
#include <nvs_flash.h>
#include <lwip/sockets.h>
// Electric
#include <driver/gpio.h>
// Project Files
#include "Project/initPins.c"
#include "Project/initWifi.c"
#include "Project/initSocket.c"

void app_main() {

  init_pins();
  xTaskCreate(init_wifi, "init_wifi", 1024*3, NULL, 1, NULL);
}
