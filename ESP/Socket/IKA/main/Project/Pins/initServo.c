// ---------------------GUARD------------------------
#ifndef initServo
#define initServo
// --------------------------------------------------



#define SERVO_PULSE_GPIO             19        // GPIO connects to the PWM signal line

#define SERVO_MIN_PULSEWIDTH_US     500  // Minimum pulse width in microsecond
#define SERVO_MAX_PULSEWIDTH_US     2500  // Maximum pulse width in microsecond
#define SERVO_MIN_DEGREE            0   // Minimum angle
#define SERVO_MAX_DEGREE            180    // Maximum angle
#define SERVO_TIMEBASE_RESOLUTION_HZ 1000000  // 1MHz, 1us per tick
#define SERVO_TIMEBASE_PERIOD        20000    // 20000 ticks, 20ms

static inline uint32_t example_angle_to_compare(int angle){

    return (angle - SERVO_MIN_DEGREE) * (SERVO_MAX_PULSEWIDTH_US - SERVO_MIN_PULSEWIDTH_US) / (SERVO_MAX_DEGREE - SERVO_MIN_DEGREE) + SERVO_MIN_PULSEWIDTH_US;
}

mcpwm_timer_handle_t Timer = NULL;
mcpwm_oper_handle_t Oper = NULL;
mcpwm_cmpr_handle_t Comparator = NULL;
mcpwm_gen_handle_t Generator = NULL;

void assignServoTimers(){

    mcpwm_timer_config_t Timer_config = {
        .group_id = 0,
        .clk_src = MCPWM_TIMER_CLK_SRC_DEFAULT,
        .resolution_hz = SERVO_TIMEBASE_RESOLUTION_HZ,
        .period_ticks = SERVO_TIMEBASE_PERIOD,
        .count_mode = MCPWM_TIMER_COUNT_MODE_UP,
    };
    ESP_ERROR_CHECK(mcpwm_new_timer(&Timer_config, &Timer));

    mcpwm_operator_config_t Oper_config = {
        .group_id = 0, // operator must be in the same group to the timer
    };
    ESP_ERROR_CHECK(mcpwm_new_operator(&Oper_config, &Oper));

    ESP_ERROR_CHECK(mcpwm_operator_connect_timer(Oper, Timer));

    mcpwm_comparator_config_t Comparator_config = {
        .flags.update_cmp_on_tez = true,
    };
    ESP_ERROR_CHECK(mcpwm_new_comparator(Oper, &Comparator_config, &Comparator));

    mcpwm_generator_config_t Generator_config = {
        .gen_gpio_num = SERVO_PULSE_GPIO,
    };
    ESP_ERROR_CHECK(mcpwm_new_generator(Oper, &Generator_config, &Generator));

    ESP_ERROR_CHECK(mcpwm_generator_set_action_on_timer_event(Generator,
                                                              MCPWM_GEN_TIMER_EVENT_ACTION(MCPWM_TIMER_DIRECTION_UP, MCPWM_TIMER_EVENT_EMPTY, MCPWM_GEN_ACTION_HIGH)));
    ESP_ERROR_CHECK(mcpwm_generator_set_action_on_compare_event(Generator,
                                                                MCPWM_GEN_COMPARE_EVENT_ACTION(MCPWM_TIMER_DIRECTION_UP, Comparator, MCPWM_GEN_ACTION_LOW)));

    ESP_ERROR_CHECK(mcpwm_timer_enable(Timer));
    ESP_ERROR_CHECK(mcpwm_timer_start_stop(Timer, MCPWM_TIMER_START_NO_STOP));
}



// ---------------------GUARD------------------------
#endif
// --------------------------------------------------
