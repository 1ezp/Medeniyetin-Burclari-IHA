// ---------------------GUARD------------------------
#ifndef initflyingMode
#define initflyingMode
// --------------------------------------------------


#define manualPin 5
#define PixhawlkPin 3
#define PIDPin 6
#define shutdownPin 4

bool isManual = true;
bool isPixhawlk = false;
bool isPID = false;
bool isShutdown = false;
bool isOverride = false;

void adjustMode(){

    if(!digitalRead(manualPin)){

        isManual = true;
        isPixhawlk = false;
        isPID = false;
        isShutdown = false;
    }
    else if(!digitalRead(PixhawlkPin)){

        isManual = false;
        isPixhawlk = true;
        isPID = false;
        isShutdown = false;
    }
    else if(!digitalRead(PIDPin)){

        isManual = false;
        isPixhawlk = false;
        isPID = true;
        isShutdown = false;
    }
    else if(!digitalRead(shutdownPin)){

        isManual = false;
        isPixhawlk = false;
        isPID = false;
        isShutdown = true;
    }

    if(isPID && !digitalRead(PIDPin)){

        isOverride = true;
    }
    else{

        isOverride = false;
    }
}


// ---------------------GUARD------------------------
#endif
// --------------------------------------------------
