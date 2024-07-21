// ---------------------GUARD------------------------
#ifndef IkaMode
#define IkaMode
// --------------------------------------------------



// IKA Pins
#define ikaJoystickXPin A3
#define ikaJoystickYPin A4
#define turretUpPin 8
#define turretDownPin 9
#define turretRightPin 10
#define turretLeftPin 11
#define shootPin 12

short int ikaMode = 0;
short int turretMode = 0;

void adjustIkaMode(){

    if(analogRead(ikaJoystickXPin) > 600){

        ikaMode = 2;
    }
    else if(analogRead(ikaJoystickXPin) < 424){

        ikaMode = 1;
    }
    else if(analogRead(ikaJoystickYPin) > 600){

        ikaMode = 3;
    }
    else if(analogRead(ikaJoystickYPin) < 424){

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
