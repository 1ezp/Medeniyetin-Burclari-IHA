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


#define leftForward     23
#define leftRear        13
#define rightForward    32
#define rightRear       33
#define udTurret1       18
#define udTurret2       21
// #define rlTurret1    27
// #define rlTurret2    2
// initServo.c -->      19
// initGps -->          17
//                      16

// Main
void init_pins(){

    gpio_set_direction(leftForward, GPIO_MODE_OUTPUT);
    gpio_set_direction(leftRear, GPIO_MODE_OUTPUT);
    gpio_set_direction(rightForward, GPIO_MODE_OUTPUT);
    gpio_set_direction(rightRear, GPIO_MODE_OUTPUT);
    gpio_set_direction(udTurret1, GPIO_MODE_OUTPUT);
    gpio_set_direction(udTurret2, GPIO_MODE_OUTPUT);
    // gpio_set_direction(rlTurret1, GPIO_MODE_OUTPUT);
    // gpio_set_direction(rlTurret2, GPIO_MODE_OUTPUT);

    assignServoTimers();
    ESP_ERROR_CHECK(mcpwm_comparator_set_compare_value(Comparator, example_angle_to_compare(90)));
}


// ---------------------GUARD------------------------
#endif
// --------------------------------------------------
