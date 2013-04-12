/** @file   target.h
    @author M. P. Hayes, UCECE
    @date   02 June 2007
    @brief 
*/
#ifndef TARGET_H
#define TARGET_H

#define F_XTAL 18432000.0
#define CPU_PLL_MUL (72 + 1)
#define CPU_PLL_DIV 14
#define F_PLL (F_XTAL / CPU_PLL_DIV * CPU_PLL_MUL)
#define F_CPU (F_PLL / 2)

/* Power ports */
#define PSU_DIGITAL PIO_DEFINE(PORT_A, 29)


/* SPI  */
#define SPI_DEVICES_NUM 8
#define SPI_CHANNEL_DEFAULT SPI_CHANNEL3


/* GLCD  */
#define GLCD_SPI_CHANNEL SPI_CHANNEL1
#define GLCD_RS PIO_DEFINE(PORT_A, 8)
#define GLCD_CS PIO_DEFINE(PORT_A, 9)
#define GLCD_RESET PIO_DEFINE(PORT_A, 7)
#define GLCD_BACKLIGHT PIO_DEFINE(PORT_A, 6)

#endif /* TARGET_H  */
