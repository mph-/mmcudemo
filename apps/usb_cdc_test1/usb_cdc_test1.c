#include <stdio.h>
#include "usb_cdc.h"
#include "sys.h"
#include "pacer.h"

#define PACER_RATE 1000

#define SPAM_RATE 5

int main (void)
{
    int ticks = 0;
    int count = 0;
    usb_cdc_t usb_cdc;

    usb_cdc = usb_cdc_init ();
    
    sys_redirect_stdin ((void *)usb_cdc_read, usb_cdc);
    sys_redirect_stdout ((void *)usb_cdc_write, usb_cdc);
    sys_redirect_stderr ((void *)usb_cdc_write, usb_cdc);

    pacer_init (PACER_RATE);

    while (1)
    {
        pacer_wait ();

        /* This needs to be periodically called to poll the USB
           connection.  */
        usb_cdc_update ();
        
        ticks++;
        if (ticks > PACER_RATE / SPAM_RATE)
        {
            ticks = 0;
            printf ("Hello world %u!\n\r", count++);
        }
    }
}
