// ---------------------GUARD------------------------
#ifndef Servo
#define Servo
// --------------------------------------------------

#define SERVO_PULSE_GPIO_RL             21        // GPIO connects to the PWM signal line
#define SERVO_PULSE_GPIO_UD             16        // GPIO connects to the PWM signal line
#define motorOutputPin                  5

#define SERVO_MIN_PULSEWIDTH_US     500  // Minimum pulse width in microsecond
#define SERVO_MAX_PULSEWIDTH_US     2500  // Maximum pulse width in microsecond
#define SERVO_MIN_DEGREE            0   // Minimum angle
#define SERVO_MAX_DEGREE            180    // Maximum angle
#define SERVO_TIMEBASE_RESOLUTION_HZ 1000000  // 1MHz, 1us per tick
#define SERVO_TIMEBASE_PERIOD        20000    // 20000 ticks, 20ms

mcpwm_timer_handle_t rlTimer = NULL;
mcpwm_oper_handle_t rlOper = NULL;
mcpwm_cmpr_handle_t rlComparator = NULL;
mcpwm_gen_handle_t rlGenerator = NULL;

mcpwm_timer_handle_t udTimer = NULL;
mcpwm_oper_handle_t udOper = NULL;
mcpwm_cmpr_handle_t udComparator = NULL;
mcpwm_gen_handle_t udGenerator = NULL;


void assignServoTimers(){

    // ------rlServo-------

    mcpwm_timer_config_t rlTimer_config = {
        .group_id = 0,
        .clk_src = MCPWM_TIMER_CLK_SRC_DEFAULT,
        .resolution_hz = SERVO_TIMEBASE_RESOLUTION_HZ,
        .period_ticks = SERVO_TIMEBASE_PERIOD,
        .count_mode = MCPWM_TIMER_COUNT_MODE_UP,
    };
    ESP_ERROR_CHECK(mcpwm_new_timer(&rlTimer_config, &rlTimer));

    mcpwm_operator_config_t rlOper_config = {
        .group_id = 0, // operator must be in the same group to the timer
    };
    ESP_ERROR_CHECK(mcpwm_new_operator(&rlOper_config, &rlOper));

    ESP_ERROR_CHECK(mcpwm_operator_connect_timer(rlOper, rlTimer));

    mcpwm_comparator_config_t rlComparator_config = {
        .flags.update_cmp_on_tez = true,
    };
    ESP_ERROR_CHECK(mcpwm_new_comparator(rlOper, &rlComparator_config, &rlComparator));

    mcpwm_generator_config_t rlGenerator_config = {
        .gen_gpio_num = SERVO_PULSE_GPIO_RL,
    };
    ESP_ERROR_CHECK(mcpwm_new_generator(rlOper, &rlGenerator_config, &rlGenerator));

    ESP_ERROR_CHECK(mcpwm_generator_set_action_on_timer_event(rlGenerator,
                                                              MCPWM_GEN_TIMER_EVENT_ACTION(MCPWM_TIMER_DIRECTION_UP, MCPWM_TIMER_EVENT_EMPTY, MCPWM_GEN_ACTION_HIGH)));
    ESP_ERROR_CHECK(mcpwm_generator_set_action_on_compare_event(rlGenerator,
                                                                MCPWM_GEN_COMPARE_EVENT_ACTION(MCPWM_TIMER_DIRECTION_UP, rlComparator, MCPWM_GEN_ACTION_LOW)));

    ESP_ERROR_CHECK(mcpwm_timer_enable(rlTimer));
    ESP_ERROR_CHECK(mcpwm_timer_start_stop(rlTimer, MCPWM_TIMER_START_NO_STOP));

    // --------------------

    // ------udServo-------

    mcpwm_timer_config_t udTimer_config = {
        .group_id = 1,
        .clk_src = MCPWM_TIMER_CLK_SRC_DEFAULT,
        .resolution_hz = SERVO_TIMEBASE_RESOLUTION_HZ,
        .period_ticks = SERVO_TIMEBASE_PERIOD,
        .count_mode = MCPWM_TIMER_COUNT_MODE_UP,
    };
    ESP_ERROR_CHECK(mcpwm_new_timer(&udTimer_config, &udTimer));

    mcpwm_operator_config_t udOper_config = {
        .group_id = 1, // operator must be in the same group to the timer
    };
    ESP_ERROR_CHECK(mcpwm_new_operator(&udOper_config, &udOper));

    ESP_ERROR_CHECK(mcpwm_operator_connect_timer(udOper, udTimer));

    mcpwm_comparator_config_t udComparator_config = {
        .flags.update_cmp_on_tez = true,
    };
    ESP_ERROR_CHECK(mcpwm_new_comparator(udOper, &udComparator_config, &udComparator));

    mcpwm_generator_config_t udGenerator_config = {
        .gen_gpio_num = SERVO_PULSE_GPIO_UD,
    };
    ESP_ERROR_CHECK(mcpwm_new_generator(udOper, &udGenerator_config, &udGenerator));

    ESP_ERROR_CHECK(mcpwm_generator_set_action_on_timer_event(udGenerator,
                                                              MCPWM_GEN_TIMER_EVENT_ACTION(MCPWM_TIMER_DIRECTION_UP, MCPWM_TIMER_EVENT_EMPTY, MCPWM_GEN_ACTION_HIGH)));
    ESP_ERROR_CHECK(mcpwm_generator_set_action_on_compare_event(udGenerator,
                                                                MCPWM_GEN_COMPARE_EVENT_ACTION(MCPWM_TIMER_DIRECTION_UP, udComparator, MCPWM_GEN_ACTION_LOW)));

    ESP_ERROR_CHECK(mcpwm_timer_enable(udTimer));
    ESP_ERROR_CHECK(mcpwm_timer_start_stop(udTimer, MCPWM_TIMER_START_NO_STOP));
}



// ---------------------GUARD------------------------
#endif
// --------------------------------------------------
