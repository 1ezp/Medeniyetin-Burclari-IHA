// ---------------------GUARD------------------------
#ifndef ManualTask
#define ManualTask
// --------------------------------------------------

bool isManualTaskOpen = true;

short int currentXAngle = 90;
short int currentYAngle = 90;

void manualTask(){

    isManualTaskOpen = false;

    while(data[0] == 0){

        currentXAngle = data[1];
        currentYAngle = data[2];

        ESP_ERROR_CHECK(mcpwm_comparator_set_compare_value(rlComparator, example_angle_to_compare(currentXAngle)));
        ESP_ERROR_CHECK(mcpwm_comparator_set_compare_value(udComparator, example_angle_to_compare(currentYAngle)));
        analogWrite(motorMode, motorChannelNum, data[3]);
        delay(10);
    }

    currentXAngle = 90;
    currentYAngle = 90;

    ESP_ERROR_CHECK(mcpwm_comparator_set_compare_value(rlComparator, example_angle_to_compare(90)));
    ESP_ERROR_CHECK(mcpwm_comparator_set_compare_value(udComparator, example_angle_to_compare(90)));
    analogWrite(motorMode, motorChannelNum, 0);

    isManualTaskOpen = true;
    vTaskDelete(NULL);
}

// ---------------------GUARD------------------------
#endif
// --------------------------------------------------
