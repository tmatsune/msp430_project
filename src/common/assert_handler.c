#include "assert_handler.h"
#include "common/defines.h"
#include "drivers/uart_driver.h"
#include "printf.h"

//#define BREAKPOINT __asm volatile("CLR.B R3");

void assert_handler(int condition, char *msg)
{
  if(!condition){
    while(1)
    {
      printf("MSG: %s", msg);
      DELAY_MS(1000);
    }
  }
}



