/* File:   i2cs_test1.c
   Author: M. P. Hayes, UCECE
   Date:   13 April 2013
   Descr: 
*/
#include "i2c_slave.h"


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
    .addr_bytes = 1,
};


int
main (void)
{
    i2c_t i2c_slave1;
    int data[] = {0, 1, 2, 3};

    i2c_slave1 = i2c_slave_init (&i2c_bus_cfg, &i2c_slave1_cfg);

    while (1)
    {
        i2c_addr_t addr;
        i2c_ret_t ret;

        ret = i2c_slave_listen (i2c_slave1, &addr, 1000);

        if (addr >= sizeof (data))
            addr = 0;

        switch (ret)
        {
        case I2C_SLAVE_READ:
            i2c_slave_write (i2c_slave1, &data[addr], sizeof(data[0]));
            break;

        case I2C_SLAVE_WRITE:
            i2c_slave_read (i2c_slave1, &data[addr], sizeof(data[0]));
            break;

        default:
            break;
        }
    }
}

