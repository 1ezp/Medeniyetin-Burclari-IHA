// ---------------------GUARD------------------------
#ifndef initPins
#define initPins
// --------------------------------------------------

#define arkaSol1    23
#define arkaSol2    22
#define arkaSag1    32
#define arkaSag2    33
#define onSol1      2
#define onSol2      4
#define onSag1      25
#define onSag2      26
#define udTurret1   18
#define udTurret2   21
#define rlTurret1   27
#define rlTurret2   13
#define shootPin    19

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
    gpio_set_direction(rlTurret1, GPIO_MODE_OUTPUT);
    gpio_set_direction(rlTurret2, GPIO_MODE_OUTPUT);
    gpio_set_direction(shootPin, GPIO_MODE_OUTPUT);
}


// ---------------------GUARD------------------------
#endif
// --------------------------------------------------
