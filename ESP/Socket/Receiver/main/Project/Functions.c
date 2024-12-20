// ---------------------GUARD------------------------
#ifndef Functions
#define Functions
// --------------------------------------------------


// Data
int data[8] = {1, 1, 1, 1, 1, 1, 0, 0};

void analogWrite(int mode, int channel, int value){

    ESP_ERROR_CHECK(ledc_set_duty(mode, channel, value));
    ESP_ERROR_CHECK(ledc_update_duty(mode, channel));
}

void delay(int ms){ vTaskDelay(ms / portTICK_PERIOD_MS); }

void digitalWrite(int pin, int state){ gpio_set_level(pin, state); }

void extractNumbers(const char* input, int* num1, int* num2, int* num3, int* num4, int* num5, int* num6, int* num7, int* num8){if(sscanf(input, "%d:%d:%d:%d:%d:%d:%d:%d", num1, num2, num3, num4, num5, num6, num7, num8) == 8){}else{ *num1 = 1; }}

void resetControllersPins(){ ESP_ERROR_CHECK(mcpwm_comparator_set_compare_value(rlComparator, example_angle_to_compare(90))); ESP_ERROR_CHECK(mcpwm_comparator_set_compare_value(udComparator, example_angle_to_compare(90))); analogWrite(motorMode, motorChannelNum, 0); }

// ---------------------GUARD------------------------
#endif
// --------------------------------------------------
