
GCC command
/home/terence/dev/tools/msp430-gcc/bin/msp430-elf-gcc 
-mmcu=msp430g2553 
-I /home/terence/dev/tools/msp430-gcc/include 
-L /home/terence/dev/tools/msp430-gcc/include 
-Og -g -Wall 
led.c main.c -o output


#include "led.h"
#include <msp430.h>


void led_init(void)
{
  P1DIR |= 0x01; 
}

void led_toggle(void)
{
  P1DIR ^= 0x01; 
}



#include "led.h"
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
