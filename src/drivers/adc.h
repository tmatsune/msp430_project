#ifndef ADC_H
#define ADC_H
#include <stdint.h>

#define ADC_COUNT (8u)

void adc_init(void);
void adc_get_values(uint16_t *values);
void adc_start_conversion(void);

#endif
