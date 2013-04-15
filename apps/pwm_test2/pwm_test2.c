/* File:   pwm_test2.c
   Author: M. P. Hayes, UCECE
   Date:   15 April 2013
   Descr: 
*/
#include "pwm.h"
#include "pio.h"


#define PWM1_PIO PIO_DEFINE (PORT_A, 1)
#define PWM2_PIO PIO_DEFINE (PORT_A, 2)

#define PWM_FREQ_HZ 100e3


static const pwm_cfg_t pwm1_cfg =
{
    .pio = PWM1_PIO,
    .period = PWM_PERIOD_DIVISOR (PWM_FREQ_HZ),
    .duty = PWM_DUTY_DIVISOR (PWM_FREQ_HZ, 50),
    .align = PWM_ALIGN_LEFT,
    .polarity = PWM_POLARITY_LOW
};

static const pwm_cfg_t pwm2_cfg =
{
    .pio = PWM2_PIO,
    .period = PWM_PERIOD_DIVISOR (PWM_FREQ_HZ),
    .duty = PWM_DUTY_DIVISOR (PWM_FREQ_HZ, 50),
    .align = PWM_ALIGN_LEFT,
    .polarity = PWM_POLARITY_HIGH
};


int
main (void)
{
    pwm_t pwm1;
    pwm_t pwm2;

    /* Set default pin states in case PWM is disabled.  */
    pio_config_set (PWM1_PIO, PIO_OUTPUT_LOW);
    pio_config_set (PWM2_PIO, PIO_OUTPUT_LOW);

    pwm1 = pwm_init (&pwm1_cfg);
    pwm2 = pwm_init (&pwm2_cfg);

    /* Switch PIOs to be PWM pins.  */
    pwm_enable (pwm1);
    pwm_enable (pwm2);

    pwm_channels_start (pwm_channel_mask (pwm1) | pwm_channel_mask (pwm2));

    while (1)
        continue;
    
    return 0;
}
