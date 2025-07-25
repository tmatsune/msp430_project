#include "drivers/led.h"
#include <msp430.h>

int main(void)
{
  volatile unsigned int i;
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
  led_init(); 

  while(1) {
    for (i=10000; i>0; i--);
    led_toggle();
  }
      
}
