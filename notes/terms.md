
DMA (Direct memory access):
A hardware feature that allows peripherals (like UART, ADC, etc) to read from or write to memory withour involving the CPU
for each byte transmitted 

--- 

# **Clocks:**
## Three main clocks:
**DCO (Digitally Controlled Oscillator)**
    - main system clock source
    - fq: 1MHz by default (can go up to 16MHz)
    - for CPU and peripherals when high-speed operation is needed 
    - Can source: MCLK, SMCLK
**LFXT1**
    - low-fq and high-fq
    - Accurate low-speed timing 
    - cand source ACLK 
**VLO (very low-fq Oscillator)**
    - Low-power internal backup clock 
    - 12kHz 
    - backup for ACLK 

## Clock signals dereived from sources 
    - MCLK: master clock: drives the CPU 
    - SMCLK: Sub-Main clock: peripherals (e.g. UART, Timer)
    - ACLK: Auxiliary clock 

DCO is the primary high-speed clock source, the backbone for
    - MCLK (Master clock) : Drives the CPU core so DCO sets the processor speed 
    - SMCLK (Sub-Main Clock): clock peripherals like UART, SPI, Timer, ADC 
    - Timers (Timer_A, Timer_B) usually SMCLK : timers often indirectly run at DCO speed 
    - USART, UART, SPI uses SMCLK
    - ADC10 / ADC12 : can use MCLK


             DCO (~1–16 MHz)
               │
     ┌─────────┴──────────┐
     ↓                    ↓
  MCLK (CPU)          SMCLK (Peripherals)
     ↓                    ↓
  Core logic       Timers, UART, SPI, ADC...

# All MCUs have:
    - Main clock source: generates the base clock signal - can be internal(DCO) or external(crystal)
    - Clock Tree / selectors: Routes that base clock to the CPU and peripherals 
    - Dividers / PLLs: Adjust the clock speed - either divide it down or multiply up 
