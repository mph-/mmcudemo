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
#define CPU_PLL_MUL 125
#define CPU_PLL_DIV 24
#define CPU_USB_DIV 2
/* 96 MHz  */
#define F_PLL (F_XTAL / CPU_PLL_DIV * CPU_PLL_MUL)
/* 48 MHz  */
#define F_CPU (F_PLL / 2)


#define LED1_PIO PIO_DEFINE(PORT_A, 8)
#define LED2_PIO PIO_DEFINE(PORT_A, 9)

#define IR_RC5_RX_PIO PIO_DEFINE(PORT_A, 5)
#define IR_SIRC_RX_PIO PIO_DEFINE(PORT_A, 5)

#define IR_SIRC_RX_MODULATION_FREQ 36e3


#endif /* TARGET_H  */
