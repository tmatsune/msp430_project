#ifndef DEFINES_H
#define DEFINES_H

#define UNUSED(a) (void)(a)
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))
#define PORT_COUNT (8u)

#define CYCLES_1MHZ (1000000u)
#define MCU_FREQ CYCLES_1MHZ
#define MCLK MCU_FREQ 
#define SMCLK MCLK 
#define DELAY(cycles)        __delay_cycles(cycles)
#define DELAY_MS(ms)         __delay_cycles((MCU_FREQ / 1000) * (ms))

#define INTERRUPT(vector) __attribute__((interrupt(vector)))


#endif 
