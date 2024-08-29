// ---------------------GUARD------------------------
#ifndef initPins
#define initPins
// --------------------------------------------------

#define arkaSol1    23
#define arkaSol2    13
#define arkaSag1    32
#define arkaSag2    33
#define onSol1      2
#define onSol2      4
#define onSag1      25
#define onSag2      26
#define udTurret1   18
#define udTurret2   21
// #define rlTurret1   27
// #define rlTurret2   13

// Main
void init_pins(){

    gpio_set_direction(arkaSol1, GPIO_MODE_OUTPUT);
    gpio_set_direction(arkaSol2, GPIO_MODE_OUTPUT);
    gpio_set_direction(arkaSag1, GPIO_MODE_OUTPUT);
    gpio_set_direction(arkaSag2, GPIO_MODE_OUTPUT);
    gpio_set_direction(onSol1, GPIO_MODE_OUTPUT);
    gpio_set_direction(onSol2, GPIO_MODE_OUTPUT);
    gpio_set_direction(onSag1, GPIO_MODE_OUTPUT);
    gpio_set_direction(onSag2, GPIO_MODE_OUTPUT);
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
