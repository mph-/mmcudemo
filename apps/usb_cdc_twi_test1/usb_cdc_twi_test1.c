#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "usb_cdc.h"
#include "pio.h"
#include "twi.h"
#include "sys.h"
#include "pacer.h"


#define PACER_RATE 1000

#define SLAVE_ADDR 0x42
#define CLOCK_SPEED 40e3

#define GENERAL_LED_PIO  LED1_PIO
#define USB_LED_PIO  LED2_PIO


static const twi_cfg_t twi_cfg =
{
    .period = TWI_PERIOD_DIVISOR (CLOCK_SPEED)
};


typedef enum {STATE_ADDR, STATE_DATA} state_t;

enum {LINEBUFFER_SIZE = 80};

static int char_count = 0;
static char linebuffer[LINEBUFFER_SIZE];
static twi_mode_t mode = TWI_MODE_MASTER;
static twi_t twi;

static void
process_command (void)
{
    char ch;
    uint8_t addr = 0;
    char *msg;
    char message[16];
    
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

    case 's':
        mode = TWI_MODE_SLAVE;
        fprintf (stderr, "Slave mode on address %d\n", SLAVE_ADDR);
        break;

    case 'w':
        mode = TWI_MODE_MASTER;

        addr = atoi (linebuffer + 1);
        msg = index (linebuffer + 1, ' ');
        if (!msg)
        {
            fprintf(stderr, "Syntax error, missing space\n");
            return;
        }
        msg++;
        strncpy (message, msg, sizeof (message));
        twi_master_addr_write (twi, SLAVE_ADDR, addr, 1, message, sizeof(message));
        fprintf (stderr, "Master wrote %d: %s\n", addr, message);        
        break;


    case 'r':
        mode = TWI_MODE_MASTER;

        addr = atoi (linebuffer + 1);
        msg = index (linebuffer + 1, ' ');
        if (!msg)
        {
            fprintf(stderr, "Syntax error, missing space\n");
            return;
        }
        msg++;
        /* NB, this blocks.  FIXME.  */
        twi_master_addr_read (twi, SLAVE_ADDR, addr, 1, message, sizeof(message));
        fprintf (stderr, "Master read %d: %s\n", addr, message);        
        break;
        
    default:
        break;
    }
}


static void
process_twi_slave (twi_t twi)
{
    static state_t state = STATE_ADDR;
    static uint8_t addr = 0;
    static char message[16];
    twi_ret_t ret;

    ret = twi_slave_poll (twi);
    if (ret == 0)
        return;

    switch (state)
    {
    case STATE_ADDR:
        if (twi_slave_read (twi, &addr, sizeof(addr)) == sizeof(addr))
            state = STATE_DATA;
        break;
            
    case STATE_DATA:
        state = STATE_ADDR;
        if (ret == TWI_READ)
        {
            twi_slave_read (twi, message, sizeof(message));
            fprintf (stderr, "Slave read %d: %s\n", addr, message);
        }
        else if (ret == TWI_WRITE)
        {
            strcpy (message, "Hello world!");
            twi_slave_write (twi, message, sizeof(message));
            fprintf (stderr, "Slave wrote %d: %s\n", addr, message);
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

    pacer_init (PACER_RATE);

    printf ("Hello world!\n");

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
