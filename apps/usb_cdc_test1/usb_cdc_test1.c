#include <stdio.h>
#include "usb_cdc.h"
#include "sys.h"

int main (void)
{
    usb_cdc_t usb_cdc;

    usb_cdc = usb_cdc_init ();
    
    sys_redirect_stdin ((void *)usb_cdc_read, usb_cdc);
    sys_redirect_stdout ((void *)usb_cdc_write, usb_cdc);
    sys_redirect_stderr ((void *)usb_cdc_write, usb_cdc);

    while (1)
    {
        printf ("Hello world!\n");
    }
}
