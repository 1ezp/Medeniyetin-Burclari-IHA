// ---------------------GUARD------------------------
#ifndef Functions
#define Functions
// --------------------------------------------------


// Data
int data[2] = {0, 0};

void delay(int ms){ vTaskDelay(ms / portTICK_PERIOD_MS); }

void digitalWrite(int pin, int state){ gpio_set_level(pin, state); }

void extractNumbers(const char* input, int* num1, int* num2){if(sscanf(input, "%d:%d", num1, num2) == 2){}else{ *num1 = 0; }}

// ---------------------GUARD------------------------
#endif
// --------------------------------------------------
