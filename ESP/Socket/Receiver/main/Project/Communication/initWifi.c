// ---------------------GUARD------------------------
#ifndef initWifi
#define initWifi
// --------------------------------------------------


void socketTask();

// Variables
#define STA_SSID "UBNT-IHA"
#define STA_PASSWORD "ihatakim"
#define STATIC_IP "192.168.10.50"
#define GATEWAY_IP "192.168.10.1"
#define NETMASK "255.255.255.0"

bool isWifiConnected = false;
extern bool isSocketTaskRunning;

// WifiTAG
static const char *WifiTAG = "WIFI";

// Wifi Handler
void wifi_event_handler(void* arg, esp_event_base_t event_base, int32_t event_id, void* event_data){

	if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED){
		// ESP_LOGI(WifiTAG, "Disconnected from WiFi, attempting to reconnect...");
		esp_wifi_connect();
	}
}

// Main
void wifiTask(){

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

	// Set static IP configuration
	esp_netif_t *netif = esp_netif_get_handle_from_ifkey("WIFI_STA_DEF");
	esp_netif_ip_info_t ip_info;
	esp_netif_str_to_ip4(STATIC_IP, &ip_info.ip);
	esp_netif_str_to_ip4(GATEWAY_IP, &ip_info.gw);
	esp_netif_str_to_ip4(NETMASK, &ip_info.netmask);
	ESP_ERROR_CHECK(esp_netif_dhcpc_stop(netif)); // Stop DHCP client
	ESP_ERROR_CHECK(esp_netif_set_ip_info(netif, &ip_info)); // Set static IP

	ESP_ERROR_CHECK(esp_wifi_start());
	ESP_ERROR_CHECK(esp_wifi_connect());

	while(true){

		// Check WiFi connection status
		wifi_ap_record_t ap_info;
		if(esp_wifi_sta_get_ap_info(&ap_info) == ESP_OK){

            // Connected to WiFi, start socket
			isWifiConnected = true;
			if(!isSocketTaskRunning){
				xTaskCreate(socketTask, "socketTask", 1024*4, NULL, 1, NULL);
			}
		} else {

			// Not connected to WiFi, attempt to reconnect
			// ESP_LOGI(WifiTAG, "Attempting to reconnect to WiFi...");
			isWifiConnected = false;
			esp_wifi_connect();
		}
		delay(25);
	}
}

// ---------------------GUARD------------------------
#endif
// --------------------------------------------------
