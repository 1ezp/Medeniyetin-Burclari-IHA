// ---------------------GUARD------------------------
#ifndef Functions
#define Functions
// --------------------------------------------------


// Data
int data[2] = {0, 0};

void delay(int ms){ vTaskDelay(ms / portTICK_PERIOD_MS); }

void digitalWrite(int pin, int state){ gpio_set_level(pin, state); }

void extractNumbers(const char* input, int* num1, int* num2){if(sscanf(input, "%d:%d", num1, num2) == 2){}else{ *num1 = 0; }}

void fixGps(float latTmp, float lngTmp, float* lat, float* lng){

    int degrees = (int)latTmp / 100;
    float minutes = latTmp - ((float) degrees * 100.0);
    *lat = degrees + (minutes / 60.0);

    degrees = (int)lngTmp / 100;
    minutes = lngTmp - ((float) degrees * 100.0);
    *lng = degrees + (minutes / 60.0);
}

// ---------------------GUARD------------------------
#endif
// --------------------------------------------------
