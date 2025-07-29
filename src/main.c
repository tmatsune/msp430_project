#include "common/defines.h"
#include "common/assert_handler.h"
#include "drivers/pins.h"
#include "drivers/mcu_init.h"
#include "drivers/uart_driver.h"
#include "drivers/pwm.h"
#include "drivers/adc.h"
#include "printf.h"
#include <stdint.h>
#include <msp430.h>

volatile int duty = 4;
int up = 1;

int main(void)
{
  mcu_init();
  uart_init();
  pwm_init();
  adc_init();
  __enable_interrupt();

  pwm_set_duty_cycle(duty);
  DELAY(100);

  // ------- RUN ------- //
  while(1) {
   
    // 7 4 3 2
    adc_start_conversion();
    uint16_t adc_values[ADC_COUNT];
    adc_get_values(adc_values);
    printf("2: %d 3: %d 4: %d 7: %d\r\n", adc_values[2], adc_values[3], adc_values[4], adc_values[7]);

    if(up) duty += 6;  
    else duty -= 6; 
    if(duty > 99 && up) up = 0;
    else if (duty < 6 && !up) up = 1;
    pwm_set_duty_cycle(duty);
    DELAY_MS(250);
  }
}

