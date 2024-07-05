// ---------------------GUARD------------------------
#ifndef initPrinter
#define initPrinter
// --------------------------------------------------


void printer(){

    if(isOverride){

        Serial.println("-4");
    }
    else if(isManual){

        read();
        Serial.print(xRaw);
        Serial.print(":");
        Serial.print(yRaw);
        Serial.print(":");
        Serial.println(speed);
    }
    else if(isPixhawlk){

        Serial.println("-1");
    }
    else if(isPID){

        Serial.println("-2");
    }
    else if(isShutdown){

        Serial.println("-3");
    }
}


// ---------------------GUARD------------------------
#endif
// --------------------------------------------------
