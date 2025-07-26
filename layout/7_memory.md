
## two types of memeory: Flash and RAM 
Flash: Non Volatile 
    - memory stays when powered off
    - Stores code (stays same through execution of program)
    - Larger
RAM: Volaitle 
    - memory gone when powered off
    - dynamic
    - stores variables

---

## Source code to memory 
Source Code -> Compiler -> Object Files .elf -> linker (linker script: memory layout of MCU, where to put everything) ->
-> Turns into one executable file -> Flash programmer takes machine code and writes it to flash memory -> Reset MCU -> 
-> startup code (init RAM, runs before main, set stack pointer)

--- 


+-------------------------+ 0xFFFF
|     16-bit Peripherals  |
|  (Timer, ADC, USCI, etc)|
+-------------------------+ 0x0100
|     8-bit Peripherals   |
| (GPIO, IE/IFG, BCS, etc)|
+-------------------------+ 0x0010
|     Special Function    |
|     Registers (SFR)     |
+-------------------------+ 0x0000
+-------------------------+ 0xFFFF
|     Interrupt Vectors   | ← Top of Flash
| (RESET, Timer, Port, ...)|
+-------------------------+
|                         |
|      Flash Memory       | ← Program code
|                         |
+-------------------------+ 
|       (Unused)          |
+-------------------------+
|       RAM               | ← Stack, globals, locals
+-------------------------+ 0x0200 (start of RAM)


## **🧪Tips for Memory Optimization**
Prefer uint8_t/uint16_t over int where possible
Avoid dynamic memory (malloc)
Minimize use of float, %, /, printf
Mark unused variables as static to avoid linker inclusion
Use volatile only when necessary (e.g., hardware registers)

