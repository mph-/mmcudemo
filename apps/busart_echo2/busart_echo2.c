/* File:   busart_echo2.c
   Author: M. P. Hayes, UCECE
   Date:   29 May 2013
   Descr: 
*/
#include <stdio.h>
#include "busart.h"


int main (void)
{
    char txbuffer[64];
    char rxbuffer[64];
    busart_t busart;

    busart = busart_init (1, BUSART_BAUD_DIVISOR (57600),
                          txbuffer, sizeof (txbuffer),
                          rxbuffer, sizeof (rxbuffer));
    
    busart_puts (busart, "Hello world\n");
    
    while (1)
    {
        if (busart_read_ready_p (busart))
        {
            char ch;

            ch = busart_getc (busart);

            busart_putc (busart, ch);
        }
    }
}
