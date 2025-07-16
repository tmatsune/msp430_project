#include "isr.h"
#include "common/defines.h"
#include <msp430.h>
#include <stdint.h>

static inline void isr_pull(int port, uint8_t bit, pull_type_t pull)
{
  switch (pull) {
    case PULLDOWN:
      switch (port) {
        case 1:
          P1OUT &= ~bit;
          break; 
        case 2:
          P2OUT &= ~bit;
          break;
      }
      break;
    case PULLUP:
      switch (port) {
        case 1:
          P1OUT |= bit;
          break; 
        case 2:
          P2OUT |= bit;
          break;
      }
      break; 
  }
}

static inline void isr_trigger(int port, uint8_t bit, edge_type_t edge)
{
  switch (edge) {
    case FALLING:
      switch (port) {
        case 1:
          P1IES |= bit;  
          break;
        case 2:
          P2IES |= bit; 
          break;
      }
      break;
    case RISING:
      switch (port) {
        case 1:
          P1IES &= ~bit;
          break;
        case 2:
          P2IES &= ~bit;
          break;
      }
      break;
  }
}

void enable_interrupt(int port, int pin)
{
  uint8_t bit = (1 << pin);
  switch (port) {
    case 1:
      P1IE |= bit; 
      break;
    case 2: 
      P2IE |= bit; 
      break;
  }
}
void disable_interrupt(int port, int pin)
{
  uint8_t bit = (1 << pin);
  switch (port) {

  }
}

void create_isr_1(int pin, pull_type_t pull, edge_type_t edge, isr_function func)
{
  uint8_t bit = (1 << pin);
  P1DIR &= ~bit;   // Always set as input
  P1REN |= bit;    // Always enable pull resistor
  P1IE  |= bit;    // Always enable interrupt
  P1IFG &= ~bit;   // Always clear interrupt flag (initialization)
  isr_trigger(1, bit, edge);
  isr_pull(1, bit, pull);
  isr_functions_1[pin] = func;
}

void create_isr_2(int pin, pull_type_t pull, edge_type_t edge, isr_function func)
{
  uint8_t bit = (1 << pin);
  P2DIR &= ~bit;   // Always set as input
  P2REN |= bit;    // Always enable pull resistor
  P2IE  |= bit;    // Always enable interrupt
  P2IFG &= ~bit;   // Always clear interrupt flag (initialization)
  isr_trigger(2, bit, edge);
  isr_pull(2, bit, pull);
  isr_functions_2[pin] = func;
}

isr_function isr_functions_1[PIN_COUNT] = {
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL
};
isr_function isr_functions_2[PIN_COUNT] = {
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL
};

