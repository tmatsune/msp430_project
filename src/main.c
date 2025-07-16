#include "drivers/mcu_init.h"
#include "drivers/pins.h"
#include "drivers/isr.h"
#include "drivers/uart_driver.h"
#include "common/assert_handler.h"
#include "common/defines.h"
#include <msp430.h> 

__attribute__((interrupt(PORT1_VECTOR))) void Port_1(void) {
  volatile unsigned int pin;

  for (pin = 0; pin < PIN_COUNT; pin++) {
    uint8_t mask = (1 << pin);
    if (P1IFG & mask) {
      if (isr_functions[pin])
        isr_functions[pin]();
      P1IFG &= ~mask;
    }
  }
}

int main(void)
{
  mcu_init();
  configure_pins();
  uart_init();

  while(1) {
    uart_print("terence\n"); 
    DELAY_MS(100);
  };
}
