#ifndef DEFINES_H 
#define DEFINES_H

#define ONEMHZ (1000000u)
#define SIXTEENMHZ (16 * ONEMHZ)
#define PIN_COUNT (8u)

#define UNUSED(x) (void)(x)
#define UNUSED_FUNC __attribute__((unused))
#define DELAY(x) __delay_cycles(x);

#endif 
