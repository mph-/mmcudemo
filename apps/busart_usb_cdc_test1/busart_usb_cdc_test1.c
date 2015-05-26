/* File:   busart_usb_cdc_test1.c
   Author: M. P. Hayes, UCECE
   Date:   29 May 2013
   Descr:  This loops a USART to USB CDC using the buffered USART (busart) driver.
           It is useful for communicating with a serial device, such as a bluetooth 
           module.
*/
#include <stdio.h>
#include "busart.h"
#include "usb_cdc.h"
#include "sys.h"

/* This can be 0 or 1.  */
#define BUSART_DEVICE 0
#define BAUD_RATE 115200

int main (void)
{
    char txbuffer[64];
    char rxbuffer[64];
    busart_t busart;
    usb_cdc_t usb_cdc;

    busart = busart_init (BUSART_DEVICE, BUSART_BAUD_DIVISOR (BAUD_RATE),
                          txbuffer, sizeof (txbuffer),
                          rxbuffer, sizeof (rxbuffer));
    
    usb_cdc = usb_cdc_init ();
    
    sys_redirect_stdin ((void *)usb_cdc_read, usb_cdc);
    sys_redirect_stdout ((void *)usb_cdc_write, usb_cdc);
    sys_redirect_stderr ((void *)usb_cdc_write, usb_cdc);


    /* Wait until USB configured.  */
    while (! usb_cdc_update ())
        continue;

    
    while (1)
    {
        if (usb_cdc_read_ready_p (usb_cdc))
        {
            char ch;

            ch = fgetc (stdin);
            busart_putc (busart, ch);

            /* Echo character.  */
            fputc (ch, stderr);
        }

        if (busart_read_ready_p (busart))
        {
            char ch;

            ch = busart_getc (busart);

            fputc (ch, stderr);
        }
    }
}
