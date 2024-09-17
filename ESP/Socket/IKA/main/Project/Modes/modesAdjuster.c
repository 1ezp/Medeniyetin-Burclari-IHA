// ---------------------GUARD------------------------
#ifndef ModesAdjuster
#define ModesAdjuster
// --------------------------------------------------

extern bool isWifiConnected;
extern bool isSocketTaskRunning;

void adjustMode(const int* data){

    if(!isWifiConnected || !isSocketTaskRunning){

        shutdownAllPins();
    }
    else{

        switch(data[0]){

            case 0:
                shutDownMovementPins();
                break;
            case 1:
                moveForward();
                break;
            case 2:
                moveBackward();
                break;
            case 3:
                moveRight();
                break;
            case 4:
                moveLeft();
                break;
        }

        switch(data[1]){

            case 0:
                shutDownTurretPins();
                returnServo();
                break;
            case 1:
                turretUp();
                break;
            case 2:
                turretDown();
                break;
            case 3:
                // turretRight();
                break;
            case 4:
                // turretLeft();
                break;
            case 5:
                shoot();
                break;
        }
    }
}



// ---------------------GUARD------------------------
#endif
// --------------------------------------------------
