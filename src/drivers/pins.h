#ifndef PINS_H
#define PINS_H

typedef enum {
  P10, P11, P12, P13, P14, P15, P16, P17,
  P20, P21, P22, P23, P24, P25, P26, P27,
} Pin;

typedef enum {
  INPUT,
  OUTPUT
} PinDir;

typedef enum {
  LOW,
  HIGH,
} PinOut;

typedef enum {
  RES_DISABLE,
  RES_ENABLE_PULLUP,
  RES_ENABLE_PULLDOWN
} PinResistor;

typedef enum {
  PIN_GPIO,
  PIN_PRIMARY,
  PIN_RESERVED,
  PIN_SECONDARY
} PinSelect;

typedef enum {
  FALLING, 
  RISING
} IsrEdgeSelect;

typedef struct {
  Pin pin; 
  PinDir dir;
  PinOut out; 
  PinResistor res; 
  PinSelect select;
} PinConfig;

typedef void (*Isr)(void);

void pin_configure(PinConfig config);
void pin_set_dir(Pin pin, PinDir dir);                    // PxDIR
void pin_set_out(Pin pin, PinOut out);                    // PxOUT
PinOut pin_get(Pin pin);                                  // PxIN
void pin_set_resistor(Pin pin, PinResistor res);          // PxREN 
void pin_set_select(Pin pin, PinSelect select);           // PxSEL PxSEL2
void pin_toggle(Pin pin);
void isr_init(Pin pin, IsrEdgeSelect edge, Isr isr);
void enable_interrupt(Pin pin);
void disable_interrupt(Pin pin);
void clear_interrupt_flag(Pin pin);


/*
Interrupt Code:
    P1DIR &= ~BIT3;             // Set P1.3 as input
    P1REN |= BIT3;              // Enable pull resistor
    P1OUT |= BIT3;              // Set pull-up (resistor pulls high)

    P1IES |= BIT3;              // Interrupt on falling edge
    P1IFG &= ~BIT3;             // Clear interrupt flag (important!)
    P1IE  |= BIT3;              // Enable interrupt on P1.3

__attribute__((interrupt(PORT1_VECTOR)))
void Port_1_ISR(void)
{
    if (P1IFG & BIT3) {
        // Your interrupt handler code here
        P1IFG &= ~BIT3;  // Clear the interrupt flag
    }
}
*/








/* 
 
 
| Register | Purpose                              | MSP430 Example         |
| -------- | ------------------------------------ | ---------------------- |
| `DIR`    | **Direction** — input or output      | `P1DIR`, `P2DIR`, etc. |
| `OUT`    | **Output** — sets pin HIGH or LOW    | `P1OUT`, `P2OUT`       |
| `IN`     | **Input** — reads pin level          | `P1IN`, `P2IN`         |
| `REN`    | **Resistor Enable** — pull-up/down   | `P1REN`, `P2REN`       |
| `SEL`    | **Function Select** — GPIO or alt fn | `P1SEL`, `P2SEL`, etc. |
| `IES`    | **Interrupt Edge Select**            | `P1IES`, `P2IES`       |
| `IE`     | **Interrupt Enable**                 | `P1IE`, `P2IE`         |
| `IFG`    | **Interrupt Flag** — detects change  | `P1IFG`, `P2IFG`       |
 
| Register | Name                                    | Purpose                                                                |
| -------- | --------------------------------------- | ---------------------------------------------------------------------- |
| `P1IN`   | Port 1 Input                            | Read the current logic level (input value) on the port pins            |
| `P1OUT`  | Port 1 Output                           | Write output values (when configured as output); controls pull-up/down |
| `P1DIR`  | Port 1 Direction                        | Configure each pin as input (`0`) or output (`1`)                      |
| `P1REN`  | Port 1 Resistor Enable                  | Enable pull-up or pull-down resistors on input pins                    |
| `P1SEL`  | Port 1 Function Select                  | Select peripheral function (1) or GPIO function (0)                    |
| `P1SEL2` | Port 1 Function Select 2 (if available) | Used on some MSP430s to select alternate peripheral functions          |
| `P1IES`  | Interrupt Edge Select                   | Set interrupt edge: `0` = rising edge, `1` = falling edge              |
| `P1IFG`  | Interrupt Flag                          | Indicates which pin caused an interrupt (must be cleared in ISR)       |
| `P1IE`   | Interrupt Enable                        | Enable or disable interrupts for individual pins                       |

*/

#endif
