// ---------------------GUARD------------------------
#ifndef initPins
#define initPins
// --------------------------------------------------

// (Pins): Select, Shutdown
// (Servo): Up Right, Right Left
// (Analog): Motor

// Variables
#define pixhawlkPin 4
#define shutdownPin 6

// Main
void init_pins(){

    // Pixhawlk and Shutdown
    gpio_config_t io_conf;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = (1ULL << pixhawlkPin) | (1ULL << shutdownPin);
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 0;
    gpio_config(&io_conf);

    assignServoTimers();
    init_motor();
}


// ---------------------GUARD------------------------
#endif
// --------------------------------------------------
