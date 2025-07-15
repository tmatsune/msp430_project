#include "drivers/mcu_init.h"
#include "drivers/pins.h"
#include <msp430.h> 

int main(void)
{
  mcu_init();
  configure_pins();
}
