// ---------------------GUARD------------------------
#ifndef initPins
#define initPins
// --------------------------------------------------



// Variables
#define DID_WE_CONNECT_PIN_NUM 21

// Functions
void digitalWrite(int pin, int state){ gpio_set_level(pin, state); }

// Main
void init_pins(){

    gpio_set_direction(DID_WE_CONNECT_PIN_NUM, GPIO_MODE_OUTPUT);
}



// ---------------------GUARD------------------------
#endif
// --------------------------------------------------
