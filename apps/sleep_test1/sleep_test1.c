/* File:   sleep_test1.c
   Author: M. P. Hayes, UCECE
   Date:   15 April 2013
   Descr: 
*/
#include "cpu.h"
#include "led.h"
#include "irq.h"
#include "pio.h"
#include "pacer.h"
#include "button.h"


#define BUTTON_POLL_RATE 100

#define BUTTON1_PIO PIO_DEFINE (PORT_A, 30)


/* Define LEDs configuration.  */
static const led_cfg_t led1_cfg =
{
    .pio = LED1_PIO,
    .active = 1
};


static const button_cfg_t button1_cfg =
{
    .pio = BUTTON1_PIO
};


static void
wakeup_isr (void)
{
}


static void
sleep (void)
{
    /* Switch button to interrupt pin with pullup enabled.  */
    pio_config_set (BUTTON1_PIO, PIO_PERIPH_PULLUP);

    irq_config (AT91C_ID_IRQ1, 1,
                AT91C_AIC_SRCTYPE_EXT_LOW_LEVEL, 
                wakeup_isr);
    
    irq_enable (AT91C_ID_IRQ1);
    
    pio_shutdown (BUTTON1_PIO);
    
    /* Turn off main oscillator, PLL, and master clock, switch to slow
       clock, and sleep until get a button interrupt.  */
    cpu_sleep ();
    
    irq_disable (AT91C_ID_IRQ1);
    
    /* Force a CPU reset.  */
    cpu_reset ();

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

            sleep ();
        }
    }
    return 0;
}

