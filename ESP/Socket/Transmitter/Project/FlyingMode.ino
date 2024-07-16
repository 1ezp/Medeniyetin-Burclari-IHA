// ---------------------GUARD------------------------
#ifndef initflyingMode
#define initflyingMode
// --------------------------------------------------



#define manualPin 2
#define PixhawlkPin 3
#define PIDPin 4
#define shutdownPin 5

short int flyingMode = 0;

void adjustFlyingMode(){

    if(!digitalRead(manualPin)){

        flyingMode = 0;
    }
    else if(!digitalRead(PixhawlkPin)){

        flyingMode = 1;
    }
    else if(!digitalRead(PIDPin) || flyingMode == 4){

        flyingMode = 2;
    }
    else if(!digitalRead(shutdownPin)){

        flyingMode = 3;
    }

    if(flyingMode == 2 && !digitalRead(PIDPin)){

        flyingMode = 4;
    }
}



// ---------------------GUARD------------------------
#endif
// --------------------------------------------------
