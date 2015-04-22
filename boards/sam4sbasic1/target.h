/** @file   target.h
    @author M. P. Hayes, UCECE
    @date   22 April 2015
    @brief 
*/
#ifndef TARGET_H
#define TARGET_H

#include "mat91lib.h"

/* This is for the original sam4sbasic board.  The only difference
   between it and the newer board is that it uses an 18.432 MHz
   crystal instead of a 12 MHz crystal.  The SAM4S PLL is not as
   flexible as the SAM7S PLL (the maximum multiplier is reduced to 80)
   and it is not possible to achieve an exact 96 MHz clock.  Anyway,
   this is good enough for the USB (indeed a multiplier of 32 and a
   divisor of 3 giving 196.61 MHz works).  */

/* System clocks  */
#define F_XTAL 18.432e6
#define MCU_PLL_MUL 73
#define MCU_PLL_DIV 7
#define MCU_USB_DIV 2
/* 192.219 MHz  */
#define F_PLL (F_XTAL / MCU_PLL_DIV * MCU_PLL_MUL)
/* 96.110 MHz  */
#define F_CPU (F_PLL / 2)

#define LED1_PIO PA0_PIO
#define LED2_PIO PA1_PIO
#define LED3_PIO PA2_PIO

#define UDP_VBUS_PIO PA5_PIO

#endif /* TARGET_H  */
