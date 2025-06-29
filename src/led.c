#include <msp430.h>
#include "led.h"

void led_init(void)
{
    P1DIR |= 0x01; // Set P1.0 to output direction
}

void led_toggle(void)
{
    P1OUT = 0x00; // Toggle P1.0 using exclusive-OR
}
