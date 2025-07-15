#include "drivers/pins.h"
#include <msp430.h> 

void configure_pins(void){
  P1DIR |= BIT0;
}

