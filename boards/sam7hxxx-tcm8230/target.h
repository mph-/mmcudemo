/** @file   target.h
    @author M. P. Hayes, UCECE
    @date   02 June 2007
    @brief 
*/
#ifndef TARGET_H
#define TARGET_H

#include "mat91lib.h"

/* CPU clocks  */
#define F_XTAL 18432000.0
#define MCU_PLL_MUL 125
#define MCU_PLL_DIV 24
#define MCUUSB_DIV 2
/* 96 MHz  */
#define F_PLL (F_XTAL / MCU_PLL_DIV * MCU_PLL_MUL)
/* 48 MHz  */
#define F_CPU (F_PLL / 2)



#define LED0_PIO PA7_PIO
#define LED1_PIO PA8_PIO
#define LED2_PIO PA9_PIO
#define LED3_PIO PA10_PIO

#define TCM8230_RESET_PIO PA26_PIO

#define TCM8230_VD_PIO PA13_PIO
#define TCM8230_HD_PIO PA14_PIO
#define TCM8230_DCLK_PIO PA15_PIO
#define TCM8230_EXTCLK_PIO PA25_PIO

#define TCM8230_DATA_PIOBUS PIOBUS_DEFINE(PORT_A, 16, 23)

#define TCM8230_SDA_PIO PA3_PIO
#define TCM8230_SCL_PIO PA4_PIO

#define UDP_PULLUP_PIO PA31_PIO

#define SCL_PIO PA5_PIO
#define SDA_PIO PA6_PIO


#endif /* TARGET_H  */
