#include "adc.h"
#include <msp430.h>

#define ADC_COUNT (8u)
#define ADC_CHANNEL_COUNT (8u)
typedef uint16_t adc_channel_values_t[ADC_CHANNEL_COUNT];
volatile uint16_t adc_mem[ADC_COUNT];
volatile uint16_t adc_mem_cache[ADC_COUNT];

void adc_start_conversion(void){ ADC10CTL0 |= ADC10SC; }

void adc_init(void)
{
  ADC10CTL0 = ADC10ON + SREF_0 + ADC10SHT_2 + MSC + ADC10IE;
  // turn on ADC 
  // Set ref voltage to mcu votlage 
  // 16 cycle hold time 
  // multiple channel conversion 
  // enable interrupts 

  ADC10CTL1 = INCH_7 + SHS_0 + ADC10DIV_7 + ADC10SSEL_0 + CONSEQ_1;
  // Turn on ADC for P1.7-P1.0
  // ADC10SC bit
  // ADC10 clock divider to 7
  // ADC clock source 
  // multiple conversion mode

  ADC10AE0 = BIT5 | BIT4 | BIT3 | BIT0;
  ADC10DTC0 = ADC10CT;                    // continuous transfer 
  ADC10DTC1 = ADC_COUNT; 
  ADC10SA = (uint16_t)adc_mem;            // adc memory block 
  ADC10CTL0 |= ENC + ADC10SC;             // enable and start conversion 
}

void adc_get_values(uint16_t* values)
{
    _disable_interrupts();
    for (uint8_t i = 0; i < ADC_COUNT; i++) {
        values[i] = adc_mem_cache[i];  
    }
    _enable_interrupts();
}

__attribute__((interrupt(ADC10_VECTOR)))
void ADC10_ISR(void)
{
    for (uint8_t i = 0; i < ADC_COUNT; i++) {
        adc_mem_cache[i] = adc_mem[i];
    }
}

