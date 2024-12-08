// ---------------------GUARD------------------------
#ifndef initPins
#define initPins
// --------------------------------------------------

/*

  ^          ^
  R 0------0 R
    |      |
    |      |
    |      |
    |      |
  ^ |      | ^
  L 0------0 L


    leftForward    --->         front left R && rear left L
    leftRear       --->         front left L && rear left R

    rightForward   --->         front right R && rear right L
    rightRear      --->         front right L && rear right R

*/


// initPwm  -->                  21
// initPwm  -->                  22
// initPwm  -->                  23
// initPwm  -->                  4
// initServo.c  -->              19
// initGps -->                   17
// initGps -->                   16
#define udTurret1                18
#define udTurret2                32
// #define rlTurret1             27
// #define rlTurret2             2

// Main
void init_pins(){

    gpio_set_direction(udTurret1, GPIO_MODE_OUTPUT);
    gpio_set_direction(udTurret2, GPIO_MODE_OUTPUT);
    // gpio_set_direction(rlTurret1, GPIO_MODE_OUTPUT);
    // gpio_set_direction(rlTurret2, GPIO_MODE_OUTPUT);

    assignServoTimers();
    init_pwm();
    ESP_ERROR_CHECK(mcpwm_comparator_set_compare_value(Comparator, example_angle_to_compare(90)));
}


// ---------------------GUARD------------------------
#endif
// --------------------------------------------------
