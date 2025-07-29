#include "pwm.h"
#include "common/defines.h"
#include <msp430.h>

#define PWM_TIMER_FREQ_HZ (SMCLK / (1 << ID_0))  // but since ID_0=0, 1 << 0 = 1
#define PWM_PERIOD_FREQ_HZ 20000
#define PWM_PERIOD_TICKS (PWM_TIMER_FREQ_HZ / PWM_PERIOD_FREQ_HZ)
#define PWM_TA0CCR0 (PWM_PERIOD_TICKS - 1)
#define PWM_MAX_DUTY_CYCLE PWM_PERIOD_TICKS

void pwm_init(void)
{
  P1DIR |= BIT6;
  P1SEL |= BIT6; 

  TA0CCR0 = PWM_TA0CCR0; 
  TA0CCTL1 = OUTMOD_7;     // set TA0.1 waveform mode - clear on compare, set on overflow
   
  TA0CCR1 = 0;
  TA0CTL = TASSEL_2 + MC_1; //  // SMCLK, up mode
}

void pwm_set_duty_cycle(int value)
{
  int real_value = value/2;
  if(real_value > 50) real_value = 49;
  TA0CCR1 = real_value;
}


