/* File:   pwm_test1.c
   Author: M. P. Hayes, UCECE
   Date:   15 April 2013
   Descr: 
*/
#include "pwm.h"
#include "pio.h"


#define PWM1_PIO PA1_PIO
#define PWM2_PIO PA2_PIO

#define PWM1_FREQ_HZ 100e3
#define PWM2_FREQ_HZ 50e3


static const pwm_cfg_t pwm1_cfg =
{
    .pio = PWM1_PIO,
    .period = PWM_PERIOD_DIVISOR (PWM1_FREQ_HZ),
    .duty = PWM_DUTY_DIVISOR (PWM1_FREQ_HZ, 50),
    .align = PWM_ALIGN_LEFT,
    .polarity = PWM_POLARITY_LOW
};

static const pwm_cfg_t pwm2_cfg =
{
    .pio = PWM2_PIO,
    .period = PWM_PERIOD_DIVISOR (PWM2_FREQ_HZ),
    .duty = PWM_DUTY_DIVISOR (PWM2_FREQ_HZ, 50),
    .align = PWM_ALIGN_LEFT,
    .polarity = PWM_POLARITY_LOW
};


int
main (void)
{
    pwm_t pwm1;
    pwm_t pwm2;

    pwm1 = pwm_init (&pwm1_cfg);
    pwm2 = pwm_init (&pwm2_cfg);

    pwm_start (pwm1);
    pwm_start (pwm2);

    while (1)
        continue;
    
    return 0;
}
