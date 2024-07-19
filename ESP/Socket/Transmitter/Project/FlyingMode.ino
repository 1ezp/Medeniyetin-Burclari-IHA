// ---------------------GUARD------------------------
#ifndef initflyingMode
#define initflyingMode
// --------------------------------------------------



#define PixhawlkPin 5
#define PIDPin 6
#define shutdownPin 7

short int flyingMode = 1;

void adjustFlyingMode(){

    if(!digitalRead(PixhawlkPin)){

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
