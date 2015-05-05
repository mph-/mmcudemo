/* File:   busart_echo1.c
   Author: M. P. Hayes, UCECE
   Date:   29 May 2013
   Descr: 
*/
#include <stdio.h>
#include "busart.h"

/* This can be 0 or 1.  */
#define BUSART_DEVICE 1

int main (void)
{
    char txbuffer[64];
    char rxbuffer[64];
    busart_t busart;

    busart = busart_init (BUSART_DEVICE,
                          BUSART_BAUD_DIVISOR (57600),
                          txbuffer, sizeof (txbuffer),
                          rxbuffer, sizeof (rxbuffer));
    
    busart_puts (busart, "Hello world\n");
    
    while (1)
    {
        char ch;

        /* NB, this blocks!   */
	ch = busart_getc (busart);

        busart_putc (busart, ch);
    }
}
