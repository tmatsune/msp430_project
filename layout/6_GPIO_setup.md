
get port and pin bit 

## **Why volatile uint8_t* port_out[] = { &P1OUT, &P2OUT };**
#define P1OUT (*(volatile uint8_t *)0x0021)
    - P1OUT means: “go to memory address 0x0021, and get the 8-bit value stored there.”
    - It’s a dereferenced value at that address.
volatile uint8_t *port = &P1OUT;
    - &P1OUT gives you the address (which is 0x0021)
    - So now port holds the address of that register
    - don't optimize, hardware register and can change at any time 
 “port is a pointer where it’s storing the address where P1OUT is being held”
    - port == 0x0021
    - *port == value at address 0x0021
*port |= BIT1 dereferences and changes the value stored at the memory location


---

# Remember Pointers are just C variables that store memory addresses 
    - They point to a memory location where a value lives

---

