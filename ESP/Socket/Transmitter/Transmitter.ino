#include "Project/FlyingMode.ino"
#include "Project/IkaMode.ino"
#include "Project/Reader.ino"
#include "Project/Printer.ino"


void setup(){

    Serial.begin(9600);

    pinMode(PixhawlkPin, INPUT_PULLUP);
    pinMode(PIDPin, INPUT_PULLUP);
    pinMode(shutdownPin, INPUT_PULLUP);
    pinMode(xPin, INPUT);
    pinMode(yPin, INPUT);


    pinMode(ikaJoystickXPin, INPUT);
    pinMode(ikaJoystickYPin, INPUT);
    pinMode(turretUpPin, INPUT_PULLUP);
    pinMode(turretDownPin, INPUT_PULLUP);
    pinMode(turretRightPin, INPUT_PULLUP);
    pinMode(turretLeftPin, INPUT_PULLUP);
    pinMode(shootPin, INPUT_PULLUP);
}

void loop(){

    adjustFlyingMode();
    adjustIkaMode();
    adjustTurretMode();
    printer();
    delay(5);
}
