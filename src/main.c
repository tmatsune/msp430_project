#include <msp430.h>
#include "led.h"
#include "drivers/i2c.h"
#include "app/drive.h"

// sudo make flash 
// space + e open left window 
// space + x to close left window 
// space + h to open terminal 
// ctrl + d to close terminal 


int main(void)
{
    i2c_init();
    volatile unsigned int i;
    WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer
    led_init();

    while(1)
    {
        led_toggle();
        for (i=10000; i>0; i--);
    }
}
