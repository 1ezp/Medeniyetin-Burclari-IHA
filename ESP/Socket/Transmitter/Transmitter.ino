#include "Project/FlyingMode.ino"
#include "Project/Reader.ino"
#include "Project/Printer.ino"

void setup(){

    Serial.begin(9600);

    pinMode(manualPin, INPUT_PULLUP);
    pinMode(PixhawlkPin, INPUT_PULLUP);
    pinMode(PIDPin, INPUT_PULLUP);
    pinMode(shutdownPin, INPUT_PULLUP);
    pinMode(xPin, INPUT);
    pinMode(yPin, INPUT);
}

void loop(){

    adjustMode();
    printer();
    delay(25);
}