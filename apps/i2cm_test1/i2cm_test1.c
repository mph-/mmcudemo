/* File:   i2cm_test1.c
   Author: M. P. Hayes, UCECE
   Date:   13 April 2013
   Descr: 
*/
#include "i2c_master.h"


#define SDA_PIO PIO_DEFINE(PORT_A, 8)
#define SCL_PIO PIO_DEFINE(PORT_A, 9)

static const i2c_bus_cfg_t i2c_bus_cfg =
{
    .scl = SCL_PIO,
    .sda = SDA_PIO
};


static const i2c_slave_cfg_t i2c_slave1_cfg =
{
    .id = 0x32,
};


int
main (void)
{
    i2c_t i2c_slave1;

    i2c_slave1 = i2c_master_init (&i2c_bus_cfg, &i2c_slave1_cfg);

    while (1)
    {
        uint8_t tx[] = {1, 2, 3, 4};
        uint8_t rx[] = {0, 0, 0, 0};
        i2c_addr_t addr = 1;

        i2c_master_addr_write (i2c_slave1, addr, 1, tx, sizeof(tx));

        i2c_master_addr_read (i2c_slave1, addr, 1, rx, sizeof(rx));

        /* TODO: check if rx matches tx.  */
    }
}

