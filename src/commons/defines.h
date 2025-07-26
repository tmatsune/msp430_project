#ifndef DEFINES_H
#define DEFINES_H

#define UNUSED(a) (void)(a)
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))
#define PORT_COUNT (8u)
#define DELAY(cycles) __delay_cycles(cycles)

#endif 
