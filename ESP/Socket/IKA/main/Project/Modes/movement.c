// ---------------------GUARD------------------------
#ifndef Movement
#define Movement
// --------------------------------------------------

bool movementType = 1;         // Reverse this if the movements are flipped

void shutdownAllPins(){

    digitalWrite(leftForward, !movementType);
    digitalWrite(leftRear, !movementType);
    digitalWrite(rightForward, !movementType);
    digitalWrite(rightRear, !movementType);
    digitalWrite(udTurret1, !movementType);
    digitalWrite(udTurret2, !movementType);

}

void shutDownMovementPins(){

    digitalWrite(leftForward, !movementType);
    digitalWrite(leftRear, !movementType);
    digitalWrite(rightForward, !movementType);
    digitalWrite(rightRear, !movementType);
}

void shutDownTurretPins(){

    digitalWrite(udTurret1, !movementType);
    digitalWrite(udTurret2, !movementType);
}

void moveForward(){

    digitalWrite(leftForward, movementType);
    digitalWrite(leftRear, !movementType);
    digitalWrite(rightForward, movementType);
    digitalWrite(rightRear, !movementType);
}

void moveBackward(){

    digitalWrite(leftForward, !movementType);
    digitalWrite(leftRear, movementType);
    digitalWrite(rightForward, !movementType);
    digitalWrite(rightRear, movementType);
}

void moveRight(){

    digitalWrite(leftForward, movementType);
    digitalWrite(leftRear, !movementType);
    digitalWrite(rightForward, !movementType);
    digitalWrite(rightRear, movementType);
}

void moveLeft(){

    digitalWrite(leftForward, !movementType);
    digitalWrite(leftRear, movementType);
    digitalWrite(rightForward, movementType);
    digitalWrite(rightRear, !movementType);
}

void turretUp(){

    digitalWrite(udTurret1, !movementType);
    digitalWrite(udTurret2, movementType);
}

void turretDown(){

    digitalWrite(udTurret1, movementType);
    digitalWrite(udTurret2, !movementType);
}

// void turretRight(){

//     digitalWrite(rlTurret1, movementType);
//     digitalWrite(rlTurret2, !movementType);
// }

// void turretLeft(){

//     digitalWrite(rlTurret1, !movementType);
//     digitalWrite(rlTurret2, movementType);
// }

void shoot(){

    ESP_ERROR_CHECK(mcpwm_comparator_set_compare_value(Comparator, example_angle_to_compare(0)));
}

void returnServo(){

    ESP_ERROR_CHECK(mcpwm_comparator_set_compare_value(Comparator, example_angle_to_compare(90)));
}

// ---------------------GUARD------------------------
#endif
// --------------------------------------------------
