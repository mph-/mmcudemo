/* File:   usart_echo1.c
   Author: M. P. Hayes, UCECE
   Date:   27 May 2015
   Descr: 
*/
#include <stdio.h>
#include "usart.h"

/* This can be 0 or 1.  */
#define USART_DEVICE 1

int main (void)
{
    usart_t usart;

    usart = usart_init (USART_DEVICE, USART_BAUD_DIVISOR (57600));
    
    usart_puts (usart, "Hello world\n");
    
    while (1)
    {
        char ch;

        /* NB, this blocks!   */
	ch = usart_getc (usart);

        usart_putc (usart, ch);
    }
}
