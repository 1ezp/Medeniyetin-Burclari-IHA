// ---------------------GUARD------------------------
#ifndef PIDTaskGaurd
#define PIDTaskGaurd
// --------------------------------------------------


long long int previousPIDMillis = 0;
long long int targetTimoutMillis = 0;

double setpointX;                       // PID values
double setpointY;
double outputX;
double outputY;

#define KP 0.02
#define KI 0.003
#define KD 0.001

double dt = 1;

double prevErrorX = 0;                     // PID variables
double integralX = 0;

double prevErrorY = 0;
double integralY = 0;

bool isPIDTaskOpen = true;
bool shouldCalculate = true;

extern bool isPID;
extern bool targetLostOverride;

void calculateSetpoint(){

    setpointX = data[6] / 2.0;
    setpointY = data[7] / 2.0;
}

void calculatePIDForX(){

    double error = setpointX - data[4];

    double propotional = error;

    integralX += error * dt;

    double derevetive = (error - prevErrorX) / dt;

    prevErrorX = error;

    outputX = (KP * propotional) + (KI * integralX) + (KD * derevetive);

    if(outputX > 30){

        outputX = 30;
    }
    else if(outputX < -30){

        outputX = -30;
    }

    currentXAngle += outputX;

    if(currentXAngle > 120){

        currentXAngle = 120;
    }
    else if(currentXAngle < 60){

        currentXAngle = 60;
    }

}

void calculatePIDForY() {

    double error = setpointY - data[5];

    double propotional = error;

    integralY += error * dt;

    double derevetive = (error - prevErrorY) / dt;

    prevErrorY = error;

    outputY = (KP * propotional) + (KI * integralY) + (KD * derevetive);

    if(outputY > 30){

        outputY = 30;
    }
    else if(outputY < -30){

        outputY = -30;
    }

    currentYAngle += outputY;

    if(currentYAngle > 120){

        currentYAngle = 120;
    }
    else if(currentYAngle < 60){

        currentYAngle = 60;
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
    calculateSetpoint();

    while(isPID){

        if(data[4] != -1){

            targetTimoutMillis = esp_timer_get_time() / 1000;
            shouldCalculate = true;
        }
        else{

            shouldCalculate = false;
        }

        if(((esp_timer_get_time() / 1000) - targetTimoutMillis) >= 500){

            targetLostOverride = true;
            break;
        }

        dt = ((esp_timer_get_time() / 1000.0) - previousPIDMillis) / 500.0;
        previousPIDMillis = esp_timer_get_time() / 1000;

        if(shouldCalculate){

            calculatePIDForX();
            calculatePIDForY();
            ESP_ERROR_CHECK(mcpwm_comparator_set_compare_value(rlComparator, example_angle_to_compare(currentXAngle)));
            ESP_ERROR_CHECK(mcpwm_comparator_set_compare_value(udComparator, example_angle_to_compare(currentYAngle)));
        }

        printf("%f,%f\n", outputX, outputY);
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

