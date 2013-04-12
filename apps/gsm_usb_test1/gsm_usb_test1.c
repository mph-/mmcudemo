#include <stdio.h>
#include "usb_cdc.h"
#include "gsm862.h"
#include "sys.h"

static const gsm862_cfg_t gsm_cfg = GSM862_CFG(0, 9600, GSM_ONOFF_PIO,
                                               GSM_PWRMON_PIO, GSM_RESET_PIO);

int main (void)
{
    usb_cdc_t usb_cdc;
    gsm862_t gsm;

    usb_cdc = usb_cdc_init ();

    sys_redirect_stdin ((void *)usb_cdc_read, usb_cdc);
    sys_redirect_stdout ((void *)usb_cdc_write, usb_cdc);
    sys_redirect_stderr ((void *)usb_cdc_write, usb_cdc);

    gsm = gsm862_init (&gsm_cfg);
    
    printf ("Hello world!\n");

    gsm862_puts (gsm, "Hello\r");

    while (1)
    {
        char buffer[80];

        gsm862_gets (gsm, buffer, sizeof (buffer), 2000);
        
        puts (buffer);
    }
}
