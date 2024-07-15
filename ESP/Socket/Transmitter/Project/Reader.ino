// ---------------------GUARD------------------------
#ifndef initReader
#define initReader
// --------------------------------------------------


#define xPin A0
#define yPin A1
#define speedPin A2

int xRaw = 0;
int yRaw = 0;

int speed = 0;

void readAndFix(){

    xRaw = analogRead(xPin);
    yRaw = analogRead(yPin);
    speed = analogRead(speedPin);

    xRaw = map(0, 1024, 605, 0, 180);
    yRaw = map(0, 1024, 605, 0, 180);
}


// ---------------------GUARD------------------------
#endif
// --------------------------------------------------
