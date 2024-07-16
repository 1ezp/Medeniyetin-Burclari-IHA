// ---------------------GUARD------------------------
#ifndef initGps
#define initGps
// --------------------------------------------------

// Variables
float gpsLat = -1;
float gpsLng = -1;

float gpsLatTemp = -1;
float gpsLngTemp = -1;

static const int RX_BUF_SIZE = 2048;

#define TXD_PIN 17
#define RXD_PIN 16

float latitude, longitude;

void init_gps(){

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

void gpsTask(){

    uint8_t* data = (uint8_t*)malloc(RX_BUF_SIZE+1);

    while(true){

        const int rxBytes = uart_read_bytes(UART_NUM_1, data, RX_BUF_SIZE, 350 / portTICK_PERIOD_MS);
        if(rxBytes > 0){

            data[rxBytes] = 0;

            // Find GNGLL line
            char* gngll = strstr((const char*)data, "$GNGLL");

            if(gngll != NULL){

                // Extract latitude and longitude
                if(sscanf(gngll, "$GNGLL,%f,N,%f,E", &latitude, &longitude) == 2){

                    gpsLatTemp = latitude;
                    gpsLngTemp = longitude;
                    fixGps(gpsLatTemp, gpsLngTemp, &gpsLat, &gpsLng);
                }
                else{

                    gpsLat = -1;
                    gpsLng = -1;
                }
            }
            else{

                gpsLat = -1;
                gpsLng = -1;
            }

        }
        else{

            gpsLat = -1;
            gpsLng = -1;
        }

        delay(15);
    }

    free(data);
}


// ---------------------GUARD------------------------
#endif
// --------------------------------------------------
