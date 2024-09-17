// ---------------------GUARD------------------------
#ifndef initPwm
#define initPwm
// --------------------------------------------------

#define PWM_FREQ        5000  // Set frequency to 5 kHz
#define PWM_RESOLUTION  LEDC_TIMER_10_BIT  // 10-bit resolution (1024 levels)
#define PWM_DUTY_MAX    1023  // Maximum duty cycle for 10-bit resolution

#define leftForward     21
#define leftRear        22
#define rightForward    23
#define rightRear       24

void init_pwm(){

    // Configure the timer for PWM
    ledc_timer_config_t ledc_timer = {
        .speed_mode       = LEDC_LOW_SPEED_MODE,   // High-speed mode
        .timer_num        = LEDC_TIMER_0,           // Timer 0
        .duty_resolution  = PWM_RESOLUTION,         // Resolution of PWM duty
        .freq_hz          = PWM_FREQ,               // Frequency of PWM
        .clk_cfg          = LEDC_AUTO_CLK           // Auto-select the source clock
    };
    ledc_timer_config(&ledc_timer);

    // Configure PWM channels
    ledc_channel_config_t ledc_channel[] = {
        {
            .speed_mode     = LEDC_LOW_SPEED_MODE,
            .channel        = LEDC_CHANNEL_0,
            .timer_sel      = LEDC_TIMER_0,
            .intr_type      = LEDC_INTR_DISABLE,
            .gpio_num       = leftForward,
            .duty           = 0,    // Initial duty cycle (off)
            .hpoint         = 0
        },
        {
            .speed_mode     = LEDC_LOW_SPEED_MODE,
            .channel        = LEDC_CHANNEL_1,
            .timer_sel      = LEDC_TIMER_0,
            .intr_type      = LEDC_INTR_DISABLE,
            .gpio_num       = leftRear,
            .duty           = 0,    // Initial duty cycle
            .hpoint         = 0
        },
        {
            .speed_mode     = LEDC_LOW_SPEED_MODE,
            .channel        = LEDC_CHANNEL_2,
            .timer_sel      = LEDC_TIMER_0,
            .intr_type      = LEDC_INTR_DISABLE,
            .gpio_num       = rightForward,
            .duty           = 0,
            .hpoint         = 0
        },
        {
            .speed_mode     = LEDC_LOW_SPEED_MODE,
            .channel        = LEDC_CHANNEL_3,
            .timer_sel      = LEDC_TIMER_0,
            .intr_type      = LEDC_INTR_DISABLE,
            .gpio_num       = rightRear,
            .duty           = 0,
            .hpoint         = 0
        },
    };

    // Initialize the channels
    for (int i = 0; i < sizeof(ledc_channel) / sizeof(ledc_channel[0]); i++) {
        ledc_channel_config(&ledc_channel[i]);
    }
}

void analogWrite(ledc_channel_t channel, uint32_t duty){

    ledc_set_duty(LEDC_LOW_SPEED_MODE, channel, duty);
    ledc_update_duty(LEDC_LOW_SPEED_MODE, channel);
}

// ---------------------GUARD------------------------
#endif
// --------------------------------------------------
