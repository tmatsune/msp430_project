#include "commons/defines.h"
#include "drivers/pins.h"
#include <msp430.h>

/*
  sudo make all TOOLS_PATH=/home/terence/dev/tools
  sudo make flash TOOLS_PATH=/home/terence/dev/tools
*/

int main(void)
{
  volatile unsigned int i;
  WDTCTL = WDTPW + WDTHOLD; 
  pin_set_dir(P10, OUTPUT);
  pin_set_out(P10, HIGH);

  while(1) {
    for (i=10000; i>0; i--);
    //P1OUT ^= BIT0;
  }
      
}
