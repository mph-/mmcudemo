/** @file   glcd_test6.c
    @author Michael Hayes
    @date   19 December 2007
    @brief  GLCD test.
*/

#include "config.h"
#include "delay.h"
#include "pio.h"
#include "glcd.h"
#include "glcd_text.h"
#include "textview.h"
#include "delay.h"
#include "font.h"

#include <stdio.h>
#include <stdlib.h>


static font_t font =
{
#include "font7x5_2.def"
};


enum {ROWS = 8, COLS = 20};

textview_t textview;

extern void
stdio_redirect (void (*putc1) (int ch), int (*getc1) (void));


static void stdio_putc (int ch)
{
    textview_putc (textview, ch);
}


static int stdio_getc (void)
{
    return 0;
}


int main (void)
{
    glcd_cfg_t glcd_cfg;
    glcd_dev_t glcd_dev;
    glcd_t glcd;
    textview_obj_t textview_obj;
    char screen[COLS * ROWS];

    /* Enable the digital power supply.  */
    pio_config_set (PSU_DIGITAL, PIO_OUTPUT);
    pio_output_high (PSU_DIGITAL);
    delay_ms (1000);

    glcd = glcd_init (&glcd_dev, &glcd_cfg);
    
    textview = textview_init (&textview_obj, screen, COLS, ROWS, &font,
                              (textview_pixel_set_t)glcd_pixel_set,
                              (textview_update_t)glcd_update, glcd);
    
    stdio_redirect (stdio_putc, stdio_getc);

    textview_puts (textview, "HELLO WORLD!\n");
    textview_puts (textview, "MPH\n");

    while (1)
    {
        int i;

        for (i = 0; i < 100; i++)
        {
            printf ("HELLO %d\n", i);

            delay_ms (200);
        }
    }
}

