#ifndef DEFINES_H 
#define DEFINES_H

#define CYCLES_1MHZ (1000000u) // million cycles per sec
#define CYCLES_16MHZ (16u * CYCLES_1MHZ) // 16 million cycles per sec
#define CYCLES_PER_MS (CYCLES_16MHZ / 1000u) // 16 million cycles per sec / 1000 
#define PIN_COUNT (8u)
#define ARRAY_SIZE(array) (sizeof(array) / sizeof(array[0]))
#define IS_ODD(x) (x & 1)

#define UNUSED(x) (void)(x)
#define UNUSED_FUNC __attribute__((unused))
#define DELAY(x) __delay_cycles(x);
#define DELAY_MS(x) DELAY((x) * CYCLES_PER_MS)

#endif 
