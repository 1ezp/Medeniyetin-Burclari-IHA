// ---------------------GUARD------------------------
#ifndef PIDTaskGaurd
#define PIDTaskGaurd
// --------------------------------------------------


long long int previousPIDMillis = 0;
long long int targetTimoutMillis = 0;

#define setpointX 157.5                      // PID values
#define setpointY 103.5
double outputX;
double outputY;

#define KP 0.02
#define KI 0.005
#define KD 0.002

double dt = 1;

double prevErrorX = 0;                     // PID variables
double integralX = 0;

double prevErrorY = 0;
double integralY = 0;

bool isPIDTaskOpen = true;
bool shouldCalculate = true;

extern bool isPID;
extern bool targetLostOverride;

void calculatePIDForX(){

    double error = setpointX - data[4];

    double propotional = error;

    integralX += error * dt;

    double derevetive = (error - prevErrorX) / dt;

    prevErrorX = error;

    outputX = (KP * propotional) + (KI * integralX) + (KD * derevetive);

    if(outputX > 100){

        outputX = 100;
    }
    else if(outputX < -100){

        outputX = -100;
    }

    currentXAngle += outputX;

    if(currentXAngle > 180){

        currentXAngle = 180;
    }
    else if(currentXAngle < 0){

        currentXAngle = 0;
    }

}

void calculatePIDForY() {

    double error = setpointY - data[5];

    double propotional = error;

    integralY += error * dt;

    double derevetive = (error - prevErrorY) / dt;

    prevErrorY = error;

    outputY = (KP * propotional) + (KI * integralY) + (KD * derevetive);

    if(outputY > 100){

        outputY = 100;
    }
    else if(outputY < -100){

        outputY = -100;
    }

    currentYAngle += outputY;

    if(currentYAngle > 180){

        currentYAngle = 180;
    }
    else if(currentYAngle < 0){

        currentYAngle = 0;
    }
}

void resetValues(){

    targetTimoutMillis = esp_timer_get_time() / 1000;
    previousPIDMillis = 0;
    dt = 1;

    prevErrorX = 0;
    integralX = 0;

    prevErrorY = 0;
    integralY = 0;

    outputX = 0;
    outputY = 0;
}

void PIDTask(){

    isPIDTaskOpen = false;

    currentXAngle = 0;
    currentYAngle = 0;
    resetValues();

    while(isPID){

        if(data[4] != -1){

            targetTimoutMillis = esp_timer_get_time() / 1000;
            shouldCalculate = true;
        }
        else{

            shouldCalculate = false;
        }

        if(((esp_timer_get_time() / 1000) - targetTimoutMillis) >= 4000){

            targetLostOverride = true;
            break;
        }

        dt = ((esp_timer_get_time() / 1000) - previousPIDMillis) / 1000.0;
        previousPIDMillis = esp_timer_get_time() / 1000;

        if(shouldCalculate){

            calculatePIDForX();
            calculatePIDForY();
            ESP_ERROR_CHECK(mcpwm_comparator_set_compare_value(rlComparator, example_angle_to_compare(currentXAngle)));
            ESP_ERROR_CHECK(mcpwm_comparator_set_compare_value(udComparator, example_angle_to_compare(currentYAngle)));
        }

        delay(25);
    }

    currentXAngle = 90;
    currentYAngle = 90;
    ESP_ERROR_CHECK(mcpwm_comparator_set_compare_value(rlComparator, example_angle_to_compare(currentXAngle)));
    ESP_ERROR_CHECK(mcpwm_comparator_set_compare_value(udComparator, example_angle_to_compare(currentYAngle)));

    isPIDTaskOpen = true;
    vTaskDelete(NULL);
}


// ---------------------GUARD------------------------
#endif
// --------------------------------------------------

