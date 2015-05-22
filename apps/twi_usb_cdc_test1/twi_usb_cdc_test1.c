/* File:   twi_usb_cdc_test1.c
   Author: M. P. Hayes, UCECE
   Date:   27 April 2015
   Descr:  This program requires two instances communicating via TWI
   with USB CDC operating to provide a command line interface.  By default,
   the program acts as a slave but messages can be read/written as a master
   using the r and w commands.  The s command switches back to slave mode.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "usb_cdc.h"
#include "pio.h"
#include "twi.h"
#include "sys.h"
#include "pacer.h"


#define PACER_RATE 1000

#define TIMEOUT_US 20000

#define SLAVE_ADDR 0x42
#define CLOCK_SPEED 100e3

#define GENERAL_LED_PIO  LED1_PIO
#define USB_LED_PIO  LED2_PIO


static const twi_cfg_t twi_cfg =
{
    .period = TWI_PERIOD_DIVISOR (CLOCK_SPEED),
    .slave_addr = SLAVE_ADDR
};


typedef enum {STATE_ADDR, STATE_DATA} state_t;

enum {LINEBUFFER_SIZE = 80};

static int char_count = 0;
static char linebuffer[LINEBUFFER_SIZE];
static twi_mode_t mode = TWI_MODE_SLAVE;
static twi_t twi;

static void
process_command (void)
{
    char ch;
    uint8_t addr = 0;
    char *msg;
    char message[16];
    twi_ret_t ret;
    
    ch = fgetc (stdin);
    fputc (ch, stderr);
    if (char_count < LINEBUFFER_SIZE - 1)
        linebuffer[char_count++] = ch;

    if (ch != '\r')
        return;
    fputc ('\n', stderr);
    linebuffer[char_count++] = 0;
    char_count = 0;

    switch (linebuffer[0])
    {
    case '0':
        pio_output_set (GENERAL_LED_PIO, 0);
        break;
        
    case '1':
        pio_output_set (GENERAL_LED_PIO, 1);
        break;

    case 'h':
        fprintf (stderr, "Hello world!\n");
        break;

    case 's':
        mode = TWI_MODE_SLAVE;
        fprintf (stderr, "Slave listening on address %d\n", SLAVE_ADDR);
        break;

    case 'w':
        mode = TWI_MODE_MASTER;

        msg = linebuffer + 1;
        while (isspace (*msg))
            msg++;

        addr = strtoul (msg, &msg, 10);
        if (! isspace (*msg))
        {
            fprintf (stderr, "Syntax error, w addr message\n");
            return;
        }

        while (isspace (*msg))
            msg++;

        strncpy (message, msg, sizeof (message));
        ret = twi_master_addr_write (twi, SLAVE_ADDR, addr, 1, message,
                                     sizeof (message));
        if (ret == sizeof (message))
            fprintf (stderr, "Master write %d: %s\n", addr, message);        
        else
            fprintf (stderr, "Master write %d: error %d\n", addr, ret);        
        break;

    case 'r':
        mode = TWI_MODE_MASTER;

        addr = strtoul (linebuffer + 1, &msg, 10);

        /* NB, this blocks while the slave gets its act together.  */
        ret = twi_master_addr_read_timeout (twi, SLAVE_ADDR, addr, 1, message,
                                            sizeof (message), TIMEOUT_US);
        if (ret == sizeof (message))
            fprintf (stderr, "Master read %d: %s\n", addr, message);        
        else
            fprintf (stderr, "Master read %d: error %d\n", addr, ret);        
        break;
        
    default:
        break;
    }
}


static void
process_twi_slave (twi_t twi)
{
    static state_t state = STATE_ADDR;
    static int write_count = 0;
    static uint8_t addr = 0;
    static char message[16];
    twi_ret_t ret;

    ret = twi_slave_poll (twi);
    if (ret == 0)
        return;

    /* ret can either be TWI_READ for a master read or TWI_WRITE for
       for a master read.  */

    switch (state)
    {
    case STATE_ADDR:
        ret = twi_slave_read (twi, &addr, sizeof (addr));
        if (ret < 0)
            fprintf (stderr, "Slave address read error %d\n", ret);
        if (ret == sizeof (addr))
            state = STATE_DATA;
        break;
            
    case STATE_DATA:
        state = STATE_ADDR;
        if (ret == TWI_WRITE)
        {
            ret = twi_slave_read (twi, message, sizeof (message));
            if (ret == sizeof (message))
                fprintf (stderr, "Slave read %d: %s\n", addr, message);
            else
                fprintf (stderr, "Slave read %d: error %d\n", addr, ret);
        }
        else if (ret == TWI_READ)
        {
            sprintf (message, "Hello world! %d", write_count++);
            ret = twi_slave_write (twi, message, sizeof (message));
            if (ret == sizeof (message))
                fprintf (stderr, "Slave write %d: %s\n", addr, message);
            else
                fprintf (stderr, "Slave write %d: error %d\n", addr, ret);
        }
    }
}


int main (void)
{
    usb_cdc_t usb_cdc;

    pio_config_set (USB_LED_PIO, PIO_OUTPUT_LOW);                
    pio_config_set (GENERAL_LED_PIO, PIO_OUTPUT_HIGH);                

    twi = twi_init(&twi_cfg);

    usb_cdc = usb_cdc_init ();
    
    sys_redirect_stdin ((void *)usb_cdc_read, usb_cdc);
    sys_redirect_stdout ((void *)usb_cdc_write, usb_cdc);
    sys_redirect_stderr ((void *)usb_cdc_write, usb_cdc);

    /* Wait until USB configured.  */
    while (! usb_cdc_update ())
        continue;
    pio_config_set (USB_LED_PIO, PIO_OUTPUT_HIGH);                

    fprintf (stderr, "Slave listening on address %d\n", SLAVE_ADDR);

    pacer_init (PACER_RATE);
    while (1)
    {
        pacer_wait ();

        if (usb_cdc_read_ready_p (usb_cdc))
            process_command ();

        /* Check if USB disconnected.  */
        pio_output_set (USB_LED_PIO, usb_cdc_update ());

        if (mode == TWI_MODE_SLAVE)
            process_twi_slave (twi);
    }
}
