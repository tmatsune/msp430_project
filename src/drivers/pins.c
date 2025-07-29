#include "pins.h"
#include "common/defines.h"
#include <msp430.h>
#include <stdint.h>
#include <stddef.h>

#define PORT_OFFSET (3 << 3) //  00011000
static inline uint8_t get_port(Pin pin) { return ((PORT_OFFSET & pin) >> 3) + 1; } // 00011000 & 00000010 -> 00000000
static inline uint8_t get_pin_num(Pin pin) { return 7 & pin; }                     // 00000111 & 00001010 = 00000010 2
static inline uint8_t get_bit(Pin pin)                                             // 00000001 << 2 -> 00000100
{
  int num = get_pin_num(pin);
  return (1 << (num));
}

volatile uint8_t* port_dir[] = { &P1DIR, &P2DIR };
volatile uint8_t* port_out[] = { &P1OUT, &P2OUT };
volatile uint8_t* port_in[] = { &P1IN, &P2IN };
volatile uint8_t* port_ren[] = { &P1REN, &P2REN };
volatile uint8_t* port_sel1[] = { &P1SEL, &P2SEL };
volatile uint8_t* port_sel2[] = { &P1SEL2, &P2SEL2 };
volatile uint8_t* port_interrupt_edge[] = { &P1IES, &P2IES };
volatile uint8_t* port_interrupt_flag[] = { &P1IFG, &P2IFG };
volatile uint8_t* port_interrupt_enable[] = { &P1IE, &P2IE };

static Isr isrs_1[] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};
//static Isr isrs_2[] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};

void pin_configure(PinConfig config)
{
  Pin pin = config.pin;
  PinDir dir = config.dir;
  PinOut out = config.out; 
  PinResistor res = config.res;
  PinSelect select = config.select;
  pin_set_dir(pin, dir);
  pin_set_out(pin, out);
  pin_set_resistor(pin, res);    
  pin_set_select(pin, select);         
}

void pin_set_dir(Pin pin, PinDir dir)
{
  uint8_t port = get_port(pin);
  uint8_t bit = get_bit(pin);
  switch(dir)
  {
    case INPUT:
      *port_dir[port-1] &= ~bit;
      break;
    case OUTPUT:
      *port_dir[port-1] |= bit;
      break;
  }
}

void pin_set_out(Pin pin, PinOut out)
{
  uint8_t port = get_port(pin);
  uint8_t bit = get_bit(pin);
  switch(out)
  {
    case LOW:
      *port_out[port-1] &= ~bit;
      break;
    case HIGH:
      *port_out[port-1] |= bit;
      break;
  }
}

PinOut pin_get(Pin pin)
{
  uint8_t port = get_port(pin);
  uint8_t bit  = get_bit(pin);
  return (*port_in[port-1] & bit) ? HIGH : LOW;
}


void pin_set_resistor(Pin pin, PinResistor res)
{
  uint8_t port = get_port(pin);
  uint8_t bit  = get_bit(pin);
  switch(res)
  {
    case RES_DISABLE:
      *port_ren[port-1] &= ~bit;      // Disable resistor
      break;

    case RES_ENABLE_PULLUP:
      *port_out[port-1] |= bit;       // Select pull-up
      *port_ren[port-1] |= bit;       // Enable resistor
      break;

    case RES_ENABLE_PULLDOWN:
      *port_out[port-1] &= ~bit;      // Select pull-down
      *port_ren[port-1] |= bit;       // Enable resistor
      break;
  }
}

void pin_set_select(Pin pin, PinSelect select)
{
  uint8_t port = get_port(pin);
  uint8_t bit  = get_bit(pin);
  switch (select)
  {
    case PIN_GPIO:
      *port_sel1[port-1] &= ~bit;
      *port_sel2[port-1] &= ~bit;  
      break;
    case PIN_PRIMARY:
      *port_sel1[port-1] &= ~bit;
      *port_sel2[port-1] |= bit;  
      break;
    case PIN_RESERVED:
      *port_sel1[port-1] |= bit;
      *port_sel2[port-1] &= ~bit;  
      break;
    case PIN_SECONDARY:
      *port_sel1[port-1] |= bit;
      *port_sel2[port-1] |= bit;  
      break;
  }
}

void pin_toggle(Pin pin)
{
  PinOut out = pin_get(pin);
  if (out == HIGH) { pin_set_out(pin, LOW); }
  else { pin_set_out(pin, HIGH); }
}

void isr_init(Pin pin, IsrEdgeSelect edge, Isr isr)
{
  uint8_t port = get_port(pin);
  uint8_t bit  = get_bit(pin);
  pin_set_dir(pin, INPUT);
  PinResistor res = (edge == FALLING) ? RES_ENABLE_PULLUP : RES_ENABLE_PULLDOWN;
  pin_set_resistor(pin, res);
  switch (edge)
  {
    case FALLING:
      *port_interrupt_edge[port-1] |= bit;
      break;
    case RISING:
      *port_interrupt_edge[port-1] &= ~bit;
      break;
  }
  *port_interrupt_flag[port-1] &= ~bit;
  enable_interrupt(pin);
  uint8_t index = __builtin_ctz(bit); // Count trailing zeros to get 0–7
  isrs_1[index] = isr;
}

void enable_interrupt(Pin pin)
{
  uint8_t port = get_port(pin);
  uint8_t bit  = get_bit(pin);
  *port_interrupt_enable[port-1] |= bit;
}

void disable_interrupt(Pin pin)
{
  uint8_t port = get_port(pin);
  uint8_t bit  = get_bit(pin);
  *port_interrupt_enable[port-1] &= ~bit;
}

__attribute__((interrupt(PORT1_VECTOR))) void Port_1_ISR(void)
{
  uint8_t i;
  for(i=0;i<PORT_COUNT;i++){
    if (P1IFG & (1 << i)) {
      if (isrs_1[i]) isrs_1[i](); 
      P1IFG &= ~(1 << i);
    }
  }
}






/*
    P1DIR &= ~BIT3;             // Set P1.3 as input
    P1REN |= BIT3;              // Enable pull resistor
    P1OUT |= BIT3;              // Set pull-up (resistor pulls high)

    P1IES |= BIT3;              // Interrupt on falling edge
    P1IFG &= ~BIT3;             // Clear interrupt flag (important!)
    P1IE  |= BIT3;              // Enable interrupt on P1.3


*/



