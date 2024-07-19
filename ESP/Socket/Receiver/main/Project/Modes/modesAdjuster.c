// ---------------------GUARD------------------------
#ifndef ModesAdjuster
#define ModesAdjuster
// --------------------------------------------------

bool isPID = false;
bool targetLostOverride = false;

extern bool isManualTaskOpen;
extern bool isPIDTaskOpen;

extern bool shouldCalculate;

extern bool isWifiConnected;
extern bool isSocketConnected;

void adjustMode(const int* data){

    if(!isWifiConnected || !isSocketConnected){

        digitalWrite(pixhawlkPin, 1);
        digitalWrite(shutdownPin, 0);
        resetControllersPins();
    }
    else{

        switch(data[0]){

            case 0:

                isPID = false;
                targetLostOverride = false;

                digitalWrite(pixhawlkPin, 0);
                digitalWrite(shutdownPin, 0);

                if(isManualTaskOpen){

                    xTaskCreate(manualTask, "manualTask", 1024*3, NULL, 1, NULL);
                }
                break;
            case 1:

                isPID = false;
                targetLostOverride = false;

                digitalWrite(pixhawlkPin, 1);
                digitalWrite(shutdownPin, 0);
                resetControllersPins();
                break;
            case 3:
                isPID = false;
                targetLostOverride = false;

                digitalWrite(pixhawlkPin, 0);
                digitalWrite(shutdownPin, 1);
                break;
            default:
            if((data[0] == 2 && !targetLostOverride) || data[0] == 4){
                isPID = true;
                targetLostOverride = false;

                shouldCalculate = true;

                digitalWrite(pixhawlkPin, 0);
                digitalWrite(shutdownPin, 0);

                if(isPIDTaskOpen){

                    xTaskCreate(PIDTask, "PIDTask", 1024*3, NULL, 1, NULL);
                }
            }
            break;
        }

        if(targetLostOverride){

            digitalWrite(pixhawlkPin, 1);
            digitalWrite(shutdownPin, 0);
            resetControllersPins();
        }
    }
}



// ---------------------GUARD------------------------
#endif
// --------------------------------------------------
