x/** @file   target.h
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
   and it is not possible to achieve an exact 96 MHz clock. 

   In principle, a multiplier of 73 and a divisor of 7 should produce
   F_PLL to 192.219 MHz.  However, F_XTAL / 7 is less than the minimum
   of 3 MHz for the PLL.

   A multiplier of 32 and a divisor of 3 giving 196.61 MHz for F_PLL
   makes the USB work.  */

/* System clocks  */
#define F_XTAL 18.432e6
#define MCU_PLL_MUL 52
#define MCU_PLL_DIV 5
#define MCU_USB_DIV 2
/* 191.69 MHz  */
#define F_PLL (F_XTAL / MCU_PLL_DIV * MCU_PLL_MUL)
/* 95.845 MHz  */
#define F_CPU (F_PLL / 2)

#define LED1_PIO PA0_PIO
#define LED2_PIO PA1_PIO
#define LED3_PIO PA2_PIO

#define UDP_VBUS_PIO PA5_PIO

#endif /* TARGET_H  */
