// ---------------------GUARD------------------------
#ifndef initSocket
#define initSocket
// --------------------------------------------------


// Variables
#define HOST_IP "192.168.1.21"
#define HOST_PORT 50
#define CONNECT_TIMEOUT_MS 25

bool isSocketTaskRunning = false;
bool isSocketConnected = false;

extern bool isWifiConnected;

char dataToSend[32];
extern float gpsLat;
extern float gpsLng;

// SocketTAG
static const char *SocketTAG = "Socket";

// Main
void socketTask(){

    // Lock the task
    isSocketTaskRunning = true;
    isSocketConnected = false;

    // Variables
    char rx_buffer[128];
    char host_ip[] = HOST_IP;
    int addr_family = 0;
    int ip_protocol = 0;

    while(isWifiConnected){

        // Socket Variables
        struct sockaddr_in dest_addr;
        dest_addr.sin_addr.s_addr = inet_addr(host_ip);
        dest_addr.sin_family = AF_INET;
        dest_addr.sin_port = htons(HOST_PORT);
        addr_family = AF_INET;
        ip_protocol = IPPROTO_IP;

        // Create Socket
        int sock = socket(addr_family, SOCK_STREAM, ip_protocol);
        // ESP_LOGI(SocketTAG, "Socket created, connecting...");

        // Set the socket to non-blocking mode
        int flags = fcntl(sock, F_GETFL, 0);
        fcntl(sock, F_SETFL, flags | O_NONBLOCK);

        // Connect to socket
        int err = connect(sock, (struct sockaddr *)&dest_addr, sizeof(dest_addr));
        if(err < 0 && errno != EINPROGRESS){

            // ESP_LOGE(SocketTAG, "Socket unable to connect: errno %d", errno);
            close(sock);
            delay(15);  // Wait before retrying
            continue;
        }

        // Wait for the socket to be writable, indicating a successful connection
        fd_set write_fds;
        FD_ZERO(&write_fds);
        FD_SET(sock, &write_fds);

        struct timeval tv;
        tv.tv_sec = 0;
        tv.tv_usec = CONNECT_TIMEOUT_MS * 1000;

        err = select(sock + 1, NULL, &write_fds, NULL, &tv);
        if(err <= 0){

            // ESP_LOGE(SocketTAG, "Socket connection timed out or error: errno %d", errno);
            close(sock);
            delay(15);  // Wait before retrying
            continue;
        }

        // Set the socket back to blocking mode
        flags = fcntl(sock, F_GETFL, 0);
        fcntl(sock, F_SETFL, flags & ~O_NONBLOCK);
        // ESP_LOGI(SocketTAG, "Successfully connected");

        while(true){

            isSocketConnected = true;

            // Update the dataToSend
            snprintf(dataToSend, sizeof(dataToSend), "%f:%f", gpsLat, gpsLng);

            // Send
            int err = send(sock, dataToSend, strlen(dataToSend), 0);
            if(err < 0){

                // ESP_LOGE(SocketTAG, "Error occurred during sending: errno %d", errno);
                break;
            }
            // ESP_LOGI(SocketTAG, "Message sent");

            // Receive
            int len = recv(sock, rx_buffer, sizeof(rx_buffer) - 1, 0);
            if(len < 0){

                // ESP_LOGE(SocketTAG, "recv failed: errno %d", errno);
                break;
            }
            else{

                rx_buffer[len] = 0; // Null-terminate the received data
                // ESP_LOGI(SocketTAG, "Received %d bytes: %s", len, rx_buffer);
                extractNumbers(rx_buffer, &data[0], &data[1], &data[2], &data[3], &data[4], &data[5]);
            }
            delay(25);
        }

        // Shutdown the socket if correctly configured, and recreate it
        if(sock != -1){

            shutdown(sock, 0);
            close(sock);
        }

        isSocketConnected = false;
    }

    // Disconnected from wifi, stop task
    vTaskDelete(NULL);
    isSocketTaskRunning = false;
    isSocketConnected = false;
}


// ---------------------GUARD------------------------
#endif
// --------------------------------------------------
