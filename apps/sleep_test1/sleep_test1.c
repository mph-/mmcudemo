/* File:   sleep_test1.c
   Author: M. P. Hayes, UCECE
   Date:   15 April 2013
   Descr:  This only works for them SAM7 and needs tweaking for the SAM4S.
*/
#include "mcu.h"
#include "led.h"
#include "pio.h"
#include "pacer.h"
#include "button.h"
#include "extint.h"


#define BUTTON_POLL_RATE 100

#define BUTTON1_PIO PA30_PIO
#define EXTINT1_PIO BUTTON1_PIO


/* Define LED configuration.  */
static const led_cfg_t led1_cfg =
{
    .pio = LED1_PIO,
    .active = 1
};


static const extint_cfg_t extint1_cfg =
{
    .pio = BUTTON1_PIO,
};


static const button_cfg_t button1_cfg =
{
    .pio = BUTTON1_PIO
};


static void
sleep_setup (void)
{
    extint_t extint;

    pio_shutdown (EXTINT1_PIO);

    /* Note, only two PIOs can be used on the SAM7 for external interrupts.  */
    extint = extint_init (&extint1_cfg);

    extint_sleep (extint);
    
    /* Force a MCU reset.  */
    mcu_reset ();

    /* Never get here.  */
    while (1)
        continue;
}


int
main (void)
{
    led_t led1;
    button_t button1;

    /* Initialise LED.  */
    led1 = led_init (&led1_cfg);

    /* Turn on LED.  */
    led_set (led1, 1);

    /* Initialise button.  */
    button1 = button_init (&button1_cfg);

    button_poll_count_set (BUTTON_POLL_COUNT (BUTTON_POLL_RATE));

    pacer_init (BUTTON_POLL_RATE);

    while (1)
    {
        pacer_wait ();

        button_poll (button1);

        if (button_pushed_p (button1))
        {
            /* Turn off LED.  */
            led_set (led1, 0);        

            sleep_setup ();
        }
    }
    return 0;
}

