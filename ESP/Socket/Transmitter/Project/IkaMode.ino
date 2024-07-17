// ---------------------GUARD------------------------
#ifndef IkaMode
#define IkaMode
// --------------------------------------------------



// IKA Pins
#define ikaForwardPin 6
#define ikaBackwardPin 7
#define ikaRightPin 8
#define ikaLeftPin 9
#define turretUpPin 10
#define turretDownPin 11
#define turretRightPin 12
#define turretLeftPin A3
#define shootPin A4

short int ikaMode = 0;
short int turretMode = 0;

void adjustIkaMode(){

    if(!digitalRead(ikaForwardPin)){

        ikaMode = 1;
    }
    else if(!digitalRead(ikaBackwardPin)){

        ikaMode = 2;
    }
    else if(!digitalRead(ikaRightPin)){

        ikaMode = 3;
    }
    else if(!digitalRead(ikaLeftPin)){

        ikaMode = 4;
    }
    else{

        ikaMode = 0;
    }
}

void adjustTurretMode(){

    if(!digitalRead(turretUpPin)){

        turretMode = 1;
    }
    else if(!digitalRead(turretDownPin)){

        turretMode = 2;
    }
    else if(!digitalRead(turretRightPin)){

        turretMode = 3;
    }
    else if(!digitalRead(turretLeftPin)){

        turretMode = 4;
    }
    else if(!digitalRead(shootPin)){

        turretMode = 5;
    }
    else{

        turretMode = 0;
    }
}

// ---------------------GUARD------------------------
#endif
// --------------------------------------------------
