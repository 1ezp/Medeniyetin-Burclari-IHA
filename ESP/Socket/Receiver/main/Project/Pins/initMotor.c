// ---------------------GUARD------------------------
#ifndef Motor
#define Motor
// --------------------------------------------------


#define motorTimerNum            LEDC_TIMER_2
#define motorMode                LEDC_LOW_SPEED_MODE
#define motorChannelNum          LEDC_CHANNEL_2
#define motorDutyRes             LEDC_TIMER_10_BIT
#define motorFreq                (4000)

static void init_motor(void){

    // motor timer configuration
    ledc_timer_config_t motorTimer = {

        .speed_mode       = motorMode,
        .duty_resolution  = motorDutyRes,
        .timer_num        = motorTimerNum,
        .freq_hz          = motorFreq,
        .clk_cfg          = LEDC_AUTO_CLK
    };
    ESP_ERROR_CHECK(ledc_timer_config(&motorTimer));

    // motor channel configuration
    ledc_channel_config_t motorChannel = {
        .speed_mode     = motorMode,
        .channel        = motorChannelNum,
        .timer_sel      = motorTimerNum,
        .intr_type      = LEDC_INTR_DISABLE,
        .gpio_num       = motorOutputPin,
        .duty           = 0,
        .hpoint         = 0
    };
    ESP_ERROR_CHECK(ledc_channel_config(&motorChannel));
}

// ---------------------GUARD------------------------
#endif
// --------------------------------------------------

