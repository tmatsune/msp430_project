#ifndef ISR_TABLE_H
#define ISR_TABLE_H

#include <stdint.h>
#include <stddef.h>
#include "common/defines.h"

typedef enum {
  FALLING,
  RISING
} edge_type_t;

typedef enum {
  PULLDOWN,
  PULLUP
} pull_type_t;

typedef void (*isr_function)(void);
extern int isrs_taken[PIN_COUNT];
extern isr_function isr_functions_1[PIN_COUNT];
extern isr_function isr_functions_2[PIN_COUNT];

void enable_interrupt(int port, int pin);
void disable_interrupt(int port, int pin);
void create_isr_1(int pin, pull_type_t pull, edge_type_t edge, isr_function func); 
void create_isr_2(int pin, pull_type_t pull, edge_type_t edge, isr_function func); 

#endif
