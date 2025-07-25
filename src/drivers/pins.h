#ifndef PINS_H
#define PINS_H

typedef enum {
  P10, P11, P12, P13, P14, P15, P16, P17,
  P20, P21, P22, P23, P24, P25, P26, P27,
} Pin;

typedef enum {
  INPUT,
  OUTPUT
} PinDir;

typedef enum {
  LOW,
  HIGH,
} PinOut;

void pin_set_dir(Pin pin, PinDir dir);
void pin_set_out(Pin pin, PinOut out);

#endif
