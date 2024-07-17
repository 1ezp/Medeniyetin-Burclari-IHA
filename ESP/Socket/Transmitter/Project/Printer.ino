// ---------------------GUARD------------------------
#ifndef initPrinter
#define initPrinter
// --------------------------------------------------


extern short int flyingMode;
extern short int ikaMode;
extern short int turretMode;

void printFlyingMode(int mode){

    readAndFix();
    Serial.print(mode);
    Serial.print(":");
    Serial.print(xRaw);
    Serial.print(":");
    Serial.print(yRaw);
    Serial.print(":");
    Serial.print(speed);
    Serial.print(":");
}

void printIkaMode(int mode){

    Serial.print(mode);
    Serial.print(":");
}

void printTurretMode(int mode){

    Serial.println(mode);
}

void printer(){

    switch(flyingMode){

        case 0:
            printFlyingMode(0);
            break;
        case 1:
            printFlyingMode(1);
            break;
        case 2:
            printFlyingMode(2);
            break;
        case 3:
            printFlyingMode(3);
            break;
        case 4:
            printFlyingMode(4);
            break;
    }

    switch(ikaMode){

        case 0:
            printIkaMode(0);
            break;
        case 1:
            printIkaMode(1);
            break;
        case 2:
            printIkaMode(2);
            break;
        case 3:
            printIkaMode(3);
            break;
        case 4:
            printIkaMode(4);
            break;
    }

    switch(turretMode){

        case 0:
            printTurretMode(0);
            break;
        case 1:
            printTurretMode(1);
            break;
        case 2:
            printTurretMode(2);
            break;
        case 3:
            printTurretMode(3);
            break;
        case 4:
            printTurretMode(4);
            break;
        case 5:
            printTurretMode(5);
            break;
    }
}


// ---------------------GUARD------------------------
#endif
// --------------------------------------------------
