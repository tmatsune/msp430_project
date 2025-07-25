#include "pins.h"
#include "commons/defines.h"
#include <msp430.h>
#include <stdint.h>

#define PORT_OFFSET (3 << 3)
static inline uint8_t get_port(Pin pin) { return ((PORT_OFFSET & pin) >> 3) + 1; }
static inline uint8_t get_pin_num(Pin pin) { return 7 & pin; }
static inline uint8_t get_bit(Pin pin)
{
  int num = get_pin_num(pin);
  return (1 << (num));
}

volatile uint8_t* port_dir[] = { &P1DIR, &P2DIR };
volatile uint8_t* port_out[] = { &P1OUT, &P2OUT };

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
