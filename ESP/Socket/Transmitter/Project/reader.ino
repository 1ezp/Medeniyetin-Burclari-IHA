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

    if(xRaw < 425){ xRaw = 425; }
    else if(xRaw > 605){ xRaw = 605; }

    if(yRaw < 425){ yRaw = 425; }
    else if(yRaw > 605){ yRaw = 605; }

    xRaw = map(xRaw, 425, 605, 0, 180);
    yRaw = map(yRaw, 425, 605, 0, 180);
}


// ---------------------GUARD------------------------
#endif
// --------------------------------------------------
