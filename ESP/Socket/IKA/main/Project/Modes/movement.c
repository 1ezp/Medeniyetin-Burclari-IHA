// ---------------------GUARD------------------------
#ifndef Movement
#define Movement
// --------------------------------------------------

bool relayType = 0;         // 0 for active LOW, 1 for active HIGH

void returnServo(){

    ESP_ERROR_CHECK(mcpwm_comparator_set_compare_value(Comparator, example_angle_to_compare(90)));
}

void shutdownAllPins(){

    digitalWrite(arkaSol1, 0);
    digitalWrite(arkaSol2, 0);
    digitalWrite(arkaSag1, 0);
    digitalWrite(arkaSag2, 0);
    digitalWrite(onSol1, 0);
    digitalWrite(onSol2, 0);
    digitalWrite(onSag1, 0);
    digitalWrite(onSag2, 0);
    digitalWrite(udTurret1, 0);
    digitalWrite(udTurret2, 0);
    digitalWrite(rlTurret1, 0);
    digitalWrite(rlTurret2, 0);
}

void shutDownMovementPins(){

    digitalWrite(arkaSol1, 0);
    digitalWrite(arkaSol2, 0);
    digitalWrite(arkaSag1, 0);
    digitalWrite(arkaSag2, 0);
    digitalWrite(onSol1, 0);
    digitalWrite(onSol2, 0);
    digitalWrite(onSag1, 0);
    digitalWrite(onSag2, 0);
}

void shutDownTurretPins(){

    digitalWrite(udTurret1, 0);
    digitalWrite(udTurret2, 0);
    digitalWrite(rlTurret1, 0);
    digitalWrite(rlTurret2, 0);
}

void moveForward(){

    digitalWrite(arkaSol1, !relayType);     // CW
    digitalWrite(arkaSol2, relayType);
    digitalWrite(arkaSag1, !relayType);
    digitalWrite(arkaSag2, relayType);
    digitalWrite(onSol1, relayType);        // CW
    digitalWrite(onSol2, !relayType);
    digitalWrite(onSag1, relayType);
    digitalWrite(onSag2, !relayType);
}

void moveBackward(){

    digitalWrite(arkaSol1, relayType);      // CCW
    digitalWrite(arkaSol2, !relayType);
    digitalWrite(arkaSag1, relayType);
    digitalWrite(arkaSag2, !relayType);
    digitalWrite(onSol1, !relayType);       // CCW
    digitalWrite(onSol2, relayType);
    digitalWrite(onSag1, !relayType);
    digitalWrite(onSag2, relayType);
}

void moveRight(){

    digitalWrite(arkaSol1, !relayType);     // CW
    digitalWrite(arkaSol2, relayType);
    digitalWrite(arkaSag1, relayType);      // CCW
    digitalWrite(arkaSag2, !relayType);
    digitalWrite(onSol1, relayType);        // CW
    digitalWrite(onSol2, !relayType);
    digitalWrite(onSag1, !relayType);       // CCW
    digitalWrite(onSag2, relayType);
}

void moveLeft(){

    digitalWrite(arkaSol1, relayType);
    digitalWrite(arkaSol2, !relayType);
    digitalWrite(arkaSag1, !relayType);
    digitalWrite(arkaSag2, relayType);
    digitalWrite(onSol1, !relayType);
    digitalWrite(onSol2, relayType);
    digitalWrite(onSag1, relayType);
    digitalWrite(onSag2, !relayType);
}

void turretUp(){

    digitalWrite(udTurret1, relayType);
    digitalWrite(udTurret2, !relayType);
}

void turretDown(){

    digitalWrite(udTurret1, !relayType);
    digitalWrite(udTurret2, relayType);
}

void turretRight(){

    digitalWrite(rlTurret1, relayType);
    digitalWrite(rlTurret2, !relayType);
}

void turretLeft(){

    digitalWrite(rlTurret1, !relayType);
    digitalWrite(rlTurret2, relayType);
}

void shoot(){

    ESP_ERROR_CHECK(mcpwm_comparator_set_compare_value(Comparator, example_angle_to_compare(0)));
}

// ---------------------GUARD------------------------
#endif
// --------------------------------------------------
