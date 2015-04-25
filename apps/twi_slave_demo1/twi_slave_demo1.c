/* File:   twi_slave_demo1.c
   Author: M. P. Hayes, UCECE
   Date:   25 April 2015
   Descr:  Send TWI packet
*/
#include <string.h>
#include <twi.h>
#include "target.h"
#include "pacer.h"


enum {LOOP_POLL_RATE = 2};

#define SLAVE_ADDR 0x42

#define CLOCK_SPEED 40e3


static const twi_cfg_t twi_cfg =
{
    .slave_addr = SLAVE_ADDR
};


int
main (void)
{
    char message1[16];
    char message2[16];
    uint8_t addr;
    twi_t twi;

    twi = twi_init(&twi_cfg);

    pacer_init (LOOP_POLL_RATE);

    while (1)
    {
        twi_ret_t ret;

	/* Wait until next clock tick.  */
	pacer_wait ();

        
        ret = twi_slave_poll (twi);
        if (ret == TWI_READ)
        {
            twi_slave_read (twi, &addr, sizeof(addr));
            if (addr == 1)
                twi_slave_read (twi, message1, sizeof(message1));
            else if (addr == 2)
                twi_slave_read (twi, message2, sizeof(message2));
        }
        else if (ret == TWI_WRITE)
        {
            twi_slave_read (twi, &addr, sizeof(addr));
            if (addr == 1)
                twi_slave_write (twi, message1, sizeof(message1));
            else if (addr == 2)
                twi_slave_write (twi, message2, sizeof(message2));
        }
    }
}
