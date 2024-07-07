// ---------------------GUARD------------------------
#ifndef initPrinter
#define initPrinter
// --------------------------------------------------

void printValues(int mode){

    readAndFix();
    Serial.print(mode);
    Serial.print(":");
    Serial.print(xRaw);
    Serial.print(":");
    Serial.print(yRaw);
    Serial.print(":");
    Serial.println(speed);
}

void printer(){

    if(isOverride){

        printValues(4);
    }
    else if(isManual){

        printValues(0);
    }
    else if(isPixhawlk){

        printValues(1);
    }
    else if(isPID){

        printValues(2);
    }
    else if(isShutdown){

        printValues(3);
    }
}


// ---------------------GUARD------------------------
#endif
// --------------------------------------------------
