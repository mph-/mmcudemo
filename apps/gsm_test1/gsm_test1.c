#include <stdio.h>
#include "gsm862.h"


static const gsm862_cfg_t gsm_cfg = GSM862_CFG(0, 9600, GSM_ONOFF_PIO,
                                               GSM_PWRMON_PIO, GSM_RESET_PIO);

int main (void)
{
    gsm862_t gsm;

    gsm = gsm862_init (&gsm_cfg);

    gsm862_sms_send (gsm, "Hello world", "021123456");
    
    while (1)
    {
    }
}
