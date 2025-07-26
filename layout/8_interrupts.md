
Interrupts:
    - MCU reacts only when events occur (e.g. button press)
    - CPU can sleep and wake only when needed 
    - Minimal Latency and better power effieciency
How it works
    - event occurs on peripherial
    - interrupt controller detects it and asserts a signal to CPU 
    - CPU finishes instruction an saves program state to the stack 
    - Looks up ISR address in the interrupt vector table 
    - Jumps to the ISR 
    - Executes ISR code 
    - Restores state from stack and returns to main code 
Vector table 
    - holds addresses of ISR 
    - places ISR addresses at fixed locations 
    
