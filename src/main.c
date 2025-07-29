#include "common/defines.h"
#include "common/assert_handler.h"
#include "drivers/pins.h"
#include "drivers/mcu_init.h"
#include "drivers/uart_driver.h"
#include "drivers/pwm.h"
#include "printf.h"
#include <stdint.h>
#include <msp430.h>

#define ADC_COUNT (8u)
#define ADC_CHANNEL_COUNT (8u)
typedef uint16_t adc_channel_values_t[ADC_CHANNEL_COUNT];
volatile uint16_t adc_mem[ADC_COUNT];
volatile uint16_t adc_mem_cache[ADC_COUNT];

void adc_enable_and_start_conversion(void) { ADC10CTL0 |= ENC + ADC10SC; }

void adc_get_channel_values(uint16_t* values)
{
    _disable_interrupts();
    for (uint8_t i = 0; i < ADC_COUNT; i++) {
        values[i] = adc_mem_cache[i];  
    }
    _enable_interrupts();
}

void adc_init(void)
{
  ADC10CTL0 = ADC10ON + SREF_0 + ADC10SHT_2 + MSC + ADC10IE;
  // turn on ADC, Set ref voltage to mcu votlage, 16 cycle hold time 

  ADC10CTL1 = INCH_7 + SHS_0 + ADC10DIV_7 + ADC10SSEL_0 + CONSEQ_1;
  // Turn on ADC for P1.3, ADC10SC bit, ADC10 clock divider to 0, ADC clock source, single conversion mode

  ADC10AE0 = BIT5 | BIT4 | BIT3 | BIT0;
  ADC10DTC0 = ADC10CT;
  ADC10DTC1 = ADC_COUNT;
  ADC10SA = (uint16_t)adc_mem;
  adc_enable_and_start_conversion();
}

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
    
    ADC10CTL0 |= ADC10SC;
    uint16_t adc_values[ADC_COUNT];
    adc_get_channel_values(adc_values);
    printf("0: %d 1: %d 2: %d 3: %d 4: %d 5: %d 6: %d 7: %d\r\n", adc_values[0], adc_values[1], adc_values[2], adc_values[3], adc_values[4], adc_values[5], adc_values[6], adc_values[7]);

    if(up){ 
      duty += 4;
    } else {
      duty -= 4;
    }
    if(duty > 99 && up) up = 0;
    else if (duty < 6 && !up) up = 1;

    pwm_set_duty_cycle(duty);
    DELAY_MS(250);
  
  }
}

__attribute__((interrupt(ADC10_VECTOR)))
void ADC10_ISR(void)
{
    for (uint8_t i = 0; i < ADC_COUNT; i++) {
        adc_mem_cache[i] = adc_mem[i];
    }
    //adc_enable_and_start_conversion();
}
