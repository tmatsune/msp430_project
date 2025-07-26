#include "mcu_init.h"
#include <msp430.h>

static inline void stop_watchdog(void) { WDTCTL = WDTPW + WDTHOLD; }

void mcu_init(void)
{
  stop_watchdog();
}

