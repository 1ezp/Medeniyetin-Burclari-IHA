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

void read(){

    xRaw = analogRead(xPin);
    yRaw = analogRead(yPin);
    speed = analogRead(speedPin);
}


// ---------------------GUARD------------------------
#endif
// --------------------------------------------------
