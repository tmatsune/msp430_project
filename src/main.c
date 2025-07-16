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
      if (isr_functions_1[pin])
        isr_functions_1[pin]();
      P1IFG &= ~mask;
    }
  }
}

__attribute__((interrupt(PORT2_VECTOR))) void Port_2(void) {
  volatile unsigned int pin;
  for (pin = 0; pin < PIN_COUNT; pin++) {
    uint8_t mask = (1 << pin);
    if (P2IFG & mask) {
      if (isr_functions_2[pin])
        isr_functions_2[pin]();
      P2IFG &= ~mask;
    }
  }
}

void toggle_led(){
    for (int i=0;i<8;i++) {
        P1OUT ^= BIT0;
        DELAY_MS(250);
    }
    P1OUT &= ~BIT0;
} 

int main(void)
{
  mcu_init();
  configure_pins();
  uart_init();
  create_isr_2(0, PULLUP, FALLING, toggle_led); 

  while(1) {
    uart_print("terence\n"); 
    //DELAY_MS(100);
  };
}
