/** @file   target.h
    @author M. P. Hayes, UCECE
    @date   02 June 2007
    @brief 
*/
#ifndef TARGET_H
#define TARGET_H

#include "mat91lib.h"

/* System clocks  */
#define F_XTAL 12e6
#define MCU_PLL_MUL 16
#define MCU_PLL_DIV 1
#define MCU_USB_DIV 2
/* 192 MHz  */
#define F_PLL (F_XTAL / MCU_PLL_DIV * MCU_PLL_MUL)
/* 96 MHz  */
#define F_CPU (F_PLL / 2)

#define LED1_PIO PA0_PIO
#define LED2_PIO PA1_PIO
#define LED3_PIO PA2_PIO

#define UDP_VBUS_PIO PA5_PIO

#endif /* TARGET_H  */
