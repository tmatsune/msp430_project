Binary: base-2 number system with only two digits 0 and 1 
Hex: Base-16 number system, using 0-9 and A-F 
    - compact representation of binary 
Pull-up / Pull-down resistors
    - Used to ensure a defined logic level (HIGH and LOW) on input pins when switch it open
    - Pull-up resistor connects pin to Vcc through resistor -> default high 
    - Pull-down resistor connects pin to GND through resistor -> default low 
MCU: Compact integrated circuit designed to govern a specific operation in an embedded system 
    Contains: 
        - CPU, RAM, Flash/ROM, Timers, GPIO pins, Peripherals(I2C, SPI, UART, ADC, etc)
Registers: 
    - small, fast memory inside the CPU/MCU 
    - Used to: 
        - store data temporarily
        - Control hardware 
        - Interface with Peripherals
    - Types:
        - General Purpose Regsiters: Used for math, logic, temp storage
        - Control/status registers: Enable or config peripherals (e.g. GPIO_DIR, TIMER_CTRL)
        - Special Function Registers: Memory-mapped registers tied to hardware behavior 
GPIO(General purpose input/output)
    - MCU pins that can be programmed as INPUT or OUTPUT 
    Modes: 
        - input: reads external signal 
        - output: sends signal to external circuit(e.g. LED)
    Example: 
        - GPIO_DIR |= (1 << 2); // set pin 2 as output 
        - GPIO_OUT |= (1 << 2); // set pin 2 as HIGH  
        - GPIO_IN & (1 << 3); // read pin 3 
Memory-Mapped I/O 
    - Peripherals (GPIO/UART/ADC/etc) are assigned memory addresses 
    - MCU reads/writse to these addresses like regular memory 
Multiplexer (MUX): A combinational circuit that selects one of many inputs and forwards it to a single output line
                    based on Control/select lines 
    - Inputs: I0, I1, I2, I3 
    - Select Lines: S1, S0 
    - Output: Y
    - 00 -> I0, 01 -> I1, 10 -> I2, 11 -> I3 
Decoder: Takes an n-bit inputs and activates exactly one of 2n outputs 
    - Inputs: A1, A0 
    - Outputs: Y0, Y1, Y2, Y3 


