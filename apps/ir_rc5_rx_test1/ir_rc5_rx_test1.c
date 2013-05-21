/* File:   ir_rc5_rx_test1.c
   Author: M. P. Hayes, UCECE
   Date:   21 May 2013
   Descr: 
*/
#include "led.h"
#include "pacer.h"
#include "pio.h"
#include "ir_rc5_rx.h"


/* Define how fast ticks occur.  This must be faster than
   TICK_RATE_MIN.  */
enum {LOOP_POLL_RATE = 200};

/* Define LED flash rate in Hz.  */
enum {LED_FLASH_RATE = 2};


/* Define LEDs configuration.  */
static const led_cfg_t leds_cfg[] =
{
    {
        .pio = LED1_PIO,
        .active = 1
    },
    {
        .pio = LED2_PIO,
        .active = 1
    }
};

enum {LEDS_NUM = ARRAY_SIZE (leds_cfg)};


int
main (void)
{
    led_t leds[LEDS_NUM];
    uint8_t i;
    uint8_t flash_ticks;


    /* Initialise IR driver.  */
    ir_rc5_rx_init ();

    /* Initialise LEDs.  */
    for (i = 0; i < LEDS_NUM; i++)
	leds[i] = led_init (&leds_cfg[i]);

    led_set (leds[0], 1);
    led_set (leds[1], 0);

    pacer_init (LOOP_POLL_RATE);
    flash_ticks = 0;

    while (1)
    {
        uint8_t system;
        uint8_t code;
        uint8_t toggle;
        ir_rc5_rx_ret_t status;
        
        /* Poll the IR driver.  */
        status = ir_rc5_rx_read (&system, &code, &toggle);
        if (status == IR_RC5_RX_OK)
	    led_set (leds[1], 1);
    }
}

