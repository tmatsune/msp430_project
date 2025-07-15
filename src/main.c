#include "drivers/mcu_init.h"
#include "drivers/pins.h"
#include "common/assert_handler.h"
#include <msp430.h> 

int main(void)
{
  mcu_init();
  configure_pins();
}
