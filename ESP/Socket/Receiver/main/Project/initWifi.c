// ---------------------GUARD------------------------
#ifndef initWifi
#define initWifi
// --------------------------------------------------



// Libraries
#include "initPins.c"

// Variables
#define STA_SSID "UBNT-IHA"
#define STA_PASSWORD "ihatakim"

// Tag
static const char *TAG = "WIFI";

// Wifi Handler
void wifi_event_handler(void* arg, esp_event_base_t event_base, int32_t event_id, void* event_data){

	if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED) {

		ESP_LOGI(TAG, "Disconnected from WiFi, attempting to reconnect...");
		esp_wifi_connect();
	}
}

// Main
void init_wifi(){

	// Initialize NVS
	ESP_ERROR_CHECK(nvs_flash_init());

	// Initialize the TCP/IP stack
	ESP_ERROR_CHECK(esp_netif_init());

	// Create default event loop
	ESP_ERROR_CHECK(esp_event_loop_create_default());

	// Initialize WiFi
	esp_netif_create_default_wifi_sta();
	wifi_init_config_t wifi_init_config = WIFI_INIT_CONFIG_DEFAULT();
	ESP_ERROR_CHECK(esp_wifi_init(&wifi_init_config));

	// Register event handler for WiFi events
	ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &wifi_event_handler, NULL, NULL));

	// Configure WiFi as station
	ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
	wifi_config_t sta_config = {

		.sta = {
			.ssid = STA_SSID,
			.password = STA_PASSWORD
		}
	};
	ESP_ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_STA, &sta_config));
	ESP_ERROR_CHECK(esp_wifi_start());
	ESP_ERROR_CHECK(esp_wifi_connect());

	while(true){

		// Check WiFi connection status
		wifi_ap_record_t ap_info;
		if(esp_wifi_sta_get_ap_info(&ap_info) == ESP_OK){

            // Connected to WiFi, set GPIO21 high
			digitalWrite(DID_WE_CONNECT_PIN_NUM, 1);
		}
        else{

			// Not connected to WiFi, set GPIO21 low and attempt to reconnect
			digitalWrite(DID_WE_CONNECT_PIN_NUM, 0);
			ESP_LOGI(TAG, "Attempting to reconnect to WiFi...");
			esp_wifi_connect();
		}
		vTaskDelay(pdMS_TO_TICKS(25));
	}
}



// ---------------------GUARD------------------------
#endif
// --------------------------------------------------
