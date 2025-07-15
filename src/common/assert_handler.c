#include "assert_handler.h"
#include <msp430.h>

void assert_handler(void) 
{
  volatile int unsigned i;
  while(1) {
    P1OUT ^= BIT0;
    for(i=0;i<10000;i++);
  }

} 
