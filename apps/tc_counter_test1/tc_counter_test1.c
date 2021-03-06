/* File:   tc_counter_test1.c
   Author: M. P. Hayes, UCECE
   Date:   1 May 2015
   Descr:  
*/
#include "tc.h"
#include "pio.h"

#define TIMER_PIO TIOA2_PIO
#define TIMER_PRESCALE 2

#define TIMER_FREQUENCY TC_CLOCK_FREQUENCY(TIMER_PRESCALE)

#define FLASH_RATE 2
#define FLASH_CLOCKS (TIMER_FREQUENCY / FLASH_RATE / 2)

static const tc_cfg_t tc_cfg =
{
    /* The PIO is not used as an input or output but must be specified
       to select the desired channel.  */
    .pio = TIMER_PIO,
    .mode = TC_MODE_COUNTER,
    .prescale = TIMER_PRESCALE
};


int
main (void)
{
    tc_t tc;
    tc_counter_t time;
    tc_counter_t prev_time;

    pio_config_set (LED1_PIO, PIO_OUTPUT_HIGH);
    pio_config_set (LED2_PIO, PIO_OUTPUT_HIGH);

    tc = tc_init (&tc_cfg);
    if (!tc) 
    {
        /* This will fail for an invalid choice of PIO for tc.  */
        pio_output_low (LED2_PIO); 
        while (1)
           continue;
    }
    tc_start (tc);

    prev_time = tc_counter_get (tc);

    while (1)
    {
        while ((tc_counter_get (tc) - prev_time) < FLASH_CLOCKS)
            continue;
        prev_time = tc_counter_get (tc);

        pio_output_toggle (LED1_PIO);
    }
}
