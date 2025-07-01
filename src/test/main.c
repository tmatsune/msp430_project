#include <msp430.h>

static void test_blink_led(void)
{
  P1DIR |= BIT0; 
  volatile unsigned int i; // volatile to prevent omptimization 
  while (1){
    P1OUt ^= BIT0; 
    for(i = 10000; i > 0; i--) {} // delay 
  }
}

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;
  test_blink_led();
  return 0; 
}
