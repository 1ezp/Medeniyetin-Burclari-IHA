// ---------------------GUARD------------------------
#ifndef Movement
#define Movement
// --------------------------------------------------

#define leftForawrdChannel  LEDC_CHANNEL_0
#define leftRearChannel     LEDC_CHANNEL_1
#define rightForawrdChannel LEDC_CHANNEL_2
#define rightRearChannel    LEDC_CHANNEL_3

#define speedSensetivity 350

short int speed = 0;
long long int previousSpeedMillis = 0;

void adjustSpeed(bool direction){

    if((esp_timer_get_time() / 1000) - previousSpeedMillis >= speedSensetivity){

        previousSpeedMillis = esp_timer_get_time() / 1000;

        if(direction){

            switch(speed){

                case 0:
                    speed = 256;
                    break;
                case 256:
                    speed = 512;
                    break;
                case 512:
                    speed = 768;
                    break;
                case 768:
                    speed = 1023;
                    break;
                case 1023:
                    speed = 1023;
                    break;
            }
        }
        else{

            switch(speed){

                case 0:
                    speed = 0;
                    break;
                case 256:
                    speed = 0;
                    break;
                case 512:
                    speed = 256;
                    break;
                case 768:
                    speed = 512;
                    break;
                case 1023:
                    speed = 768;
                    break;
            }
        }
    }
}

void shutdownAllPins(){

    adjustSpeed(0);

    analogWrite(leftForawrdChannel, speed);
    analogWrite(leftRearChannel, speed);
    analogWrite(rightForawrdChannel, speed);
    analogWrite(rightRearChannel, speed);
    digitalWrite(udTurret1, 0);
    digitalWrite(udTurret2, 0);

}

void shutDownMovementPins(){

    adjustSpeed(0);

    analogWrite(leftForawrdChannel, speed);
    analogWrite(leftRearChannel, speed);
    analogWrite(rightForawrdChannel, speed);
    analogWrite(rightRearChannel, speed);
}

void shutDownTurretPins(){

    digitalWrite(udTurret1, 0);
    digitalWrite(udTurret2, 0);
}

void moveForward(){

    adjustSpeed(1);

    analogWrite(leftForawrdChannel, speed);
    analogWrite(leftRearChannel, 0);
    analogWrite(rightForawrdChannel, speed);
    analogWrite(rightRearChannel, 0);
}

void moveBackward(){

    adjustSpeed(1);

    analogWrite(leftForawrdChannel, 0);
    analogWrite(leftRearChannel, speed);
    analogWrite(rightForawrdChannel, 0);
    analogWrite(rightRearChannel, speed);
}

void moveRight(){

    adjustSpeed(1);

    analogWrite(leftForawrdChannel, speed);
    analogWrite(leftRearChannel, 0);
    analogWrite(rightForawrdChannel, 0);
    analogWrite(rightRearChannel, speed);
}

void moveLeft(){

    adjustSpeed(1);

    analogWrite(leftForawrdChannel, 0);
    analogWrite(leftRearChannel, speed);
    analogWrite(rightForawrdChannel, speed);
    analogWrite(rightRearChannel, 0);
}

void turretUp(){

    digitalWrite(udTurret1, 0);
    digitalWrite(udTurret2, 1);
}

void turretDown(){

    digitalWrite(udTurret1, 1);
    digitalWrite(udTurret2, 0);
}

// void turretRight(){

    // digitalWrite(rlTurret1, 1);
    // digitalWrite(rlTurret2, 0);
// }

// void turretLeft(){

    // digitalWrite(rlTurret1, 0);
    // digitalWrite(rlTurret2, 1);
// }

void shoot(){

    ESP_ERROR_CHECK(mcpwm_comparator_set_compare_value(Comparator, example_angle_to_compare(0)));
}

void returnServo(){

    ESP_ERROR_CHECK(mcpwm_comparator_set_compare_value(Comparator, example_angle_to_compare(90)));
}

// ---------------------GUARD------------------------
#endif
// --------------------------------------------------
