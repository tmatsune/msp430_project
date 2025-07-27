#include "common/defines.h"
#include "drivers/pins.h"
#include "drivers/mcu_init.h"
#include "drivers/uart_driver.h"
#include "printf.h"
#include <msp430.h>

int main(void)
{
  mcu_init();

  uart_init();

  __enable_interrupt();

  // ------- RUN ------- //
  while(1) {
    //uart_puts("msp430 \r\n");
    printf("year: %d\r\n", 2025);
    DELAY_MS(1000);
  }
      
}

