
Bit Masks
#define BIT0 0x01  // 0000 0001
#define BIT1 0x02  // 0000 0010
#define BIT2 0x04  // 0000 0100
etc ...

---

## **Registers**
| Register | Purpose                                   |
| -------- | ----------------------------------------- |
| `P1DIR`  | Direction: 0 = input, 1 = output          |
| `P1IN`   | Input: read logic level on pin            |
| `P1OUT`  | Output: write logic level to output pin   |
| `P1REN`  | Resistor enable: enables pull-up/down     |
| `P1SEL`  | Function select: 0 = GPIO, 1 = peripheral |
| `P1IES`  | Interrupt edge select                     |
| `P1IE`   | Interrupt enable                          |
| `P1IFG`  | Interrupt flag                            |

**What happens internally**
P1OUT is a memory mapped I/O register, writing to it changes the output latch 
MSP430 has a address decoder that watches the read/writes to the memory-mapped address 
GPIO hardware has a flip-flop that stores this value



