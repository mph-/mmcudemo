#include <stdio.h>
#include "usb_cdc.h"
#include "sys.h"
#include "pacer.h"


#define PACER_RATE 1000


int main (void)
{
    usb_cdc_t usb_cdc;

    usb_cdc = usb_cdc_init ();
    
    sys_redirect_stdin ((void *)usb_cdc_read, usb_cdc);
    sys_redirect_stdout ((void *)usb_cdc_write, usb_cdc);
    sys_redirect_stderr ((void *)usb_cdc_write, usb_cdc);


    /* Wait until USB configured.  */
    while (! usb_cdc_update ())
        continue;

    pacer_init (PACER_RATE);

    printf ("Hello world!\n");

    while (1)
    {
        char buffer[80];

        pacer_wait ();

        if (usb_cdc_read_ready_p (usb_cdc))
        {
            fgets (buffer, 80, stdin);

            fputs (buffer, stdout);
        }

        /* Check is USB disconnected.  */
        usb_cdc_update ();
    }
}
