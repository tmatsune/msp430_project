
# **Clocks vs Timers**
    - Clocks provide the timing source fo rthe CPU and peripherals
    - Tiemrs use a clock to count or generate time-based events like PWM, delays, or input capture 

Three main clocks: ACLK, SMCLK, MCLK. You can choose which clock drives the timers (usually SMCLK for PWM)
# How they work together
    - Timer needs a clock source to count timer 
    - Tell Timer: 
        - Use SMCLK as source 
        - Count in up mode 
        - Toggle an output when count hits CCR1 

Compare Mode (Timer_A)
    - Set a compare value in a Capture/Compare Register (CCRx)
    - TAxCCR1 = N
    - timer counts up from 0 using a selected clock 
    - when the timer count matches the compare value N, it triggers an event 
        - setting, resetting, or toggling an output pin
        - generating an interrupt
        - resetting the timer count 
    - Up mode: Timer counts up from 0 up to a specified value ni the CCR0 regsiter when reaches the value in CCR0, resets back to 0 
    - Continuous Mode: Counts 0 - 0xFFFF (max 16-bit), then rolls over to 0 


