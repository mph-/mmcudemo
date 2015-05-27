/* File:   uart_echo1.c
   Author: M. P. Hayes, UCECE
   Date:   27 May 2015
   Descr: 
*/
#include <stdio.h>
#include "uart.h"

/* This can be 0 or 1.  */
#define UART_DEVICE 1

int main (void)
{
    uart_t uart;

    uart = uart_init (UART_DEVICE, UART_BAUD_DIVISOR (57600));
    
    uart_puts (uart, "Hello world\n");
    
    while (1)
    {
        char ch;

        /* NB, this blocks!   */
	ch = uart_getc (uart);

        uart_putc (uart, ch);
    }
}
