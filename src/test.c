#include "common/defines.h"
#include "drivers/mcu_init.h"
#include <msp430.h> 

UNUSED_FUNC void test_pin_config(void)
{
  P1DIR |= BIT0;
}

UNUSED_FUNC void test_blink_led(void) 
{
  while(1) {
    DELAY(10000);
    P1OUT ^= BIT0; 
  }
}

UNUSED_FUNC void turn_off_led(void)
{
  P1OUT &= ~BIT0; 
}

int main(void)
{
  mcu_init();
  

  return 0; 
}

