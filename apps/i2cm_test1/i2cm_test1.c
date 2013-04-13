/* File:   i2cm_test1.c
   Author: M. P. Hayes, UCECE
   Date:   13 April 2013
   Descr: 
*/
#include "i2cm.h"


#define SDA_PIO PIO_DEFINE(PORT_A, 8)
#define SCL_PIO PIO_DEFINE(PORT_A, 9)

static const i2cm_cfg_t i2c_dev1_cfg =
{
    .id = 0x32,
    .addr_bytes = 1,
    .scl = SCL_PIO,
    .sda = SDA_PIO
};


int
main (void)
{
    i2cm_t i2c_dev1;

    i2c_dev1 = i2cm_init (&i2c_dev1_cfg);

    while (1)
    {
        uint8_t tx[] = {1, 2, 3, 4};
        uint8_t rx[4];

        i2cm_write (i2c_dev1, 25, tx, sizeof(tx));

        i2cm_read (i2c_dev1, 25, rx, sizeof(rx));
    }
}

