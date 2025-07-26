#include "commons/defines.h"
#include "drivers/pins.h"
#include "drivers/mcu_init.h"
#include <msp430.h>

/*
  sudo make all TOOLS_PATH=/home/terence/dev/tools
  sudo make flash TOOLS_PATH=/home/terence/dev/tools
*/

void test_isr(void)
{
  for(int i = 0; i < 16; i++){
    pin_toggle(P11);
    DELAY(400000);
  }  
}

int main(void)
{
  mcu_init();
  PinConfig test_led = { .pin = P10, .dir = OUTPUT, .out = HIGH, .res = RES_DISABLE, .select = PIN_GPIO, };
  PinConfig test_pin = { .pin = P11, .dir = OUTPUT, .out = HIGH, .res = RES_DISABLE, .select = PIN_GPIO, };
  pin_configure(test_led);
  pin_configure(test_pin);
  isr_init(P12, FALLING, test_isr);
  __enable_interrupt();

  while(1) {
    DELAY(400000);
    pin_toggle(P10);
  }
      
}
