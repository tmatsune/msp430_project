#include "drivers/pins.h"
#include <msp430.h> 

void configure_pins(void){
  P1DIR |= BIT0;
  P1OUT &= ~BIT0;
  P1SEL |= BIT1 | BIT2;
  P1SEL2 |= BIT1 | BIT2;
}

