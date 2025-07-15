#ifndef ASSERT_HANDLER_H
#define ASSERT_HANDLER_H

/*
  Custom assert handler for embedded systems. goal is to catch programming mistakes during runtime
  and provide clear visible feedback when they occur 
  
  create a macro based assert function 
    - triggers when condition is false 
    - uses file and line number info via __FILE__ and __LINE__ 
  what handler does 
    - disable motors 
    - print error location 
    - trigger software breakpoint 
    - blink led in endless loop 
*/

/*
  Example:
  volatile int speed = -10;
  ASSERT(speed >= 0); -> RUNS 

*/

void assert_handler(void);

#define ASSERT(cond)  \
  do {                \
    if(!(cond)) {     \
      assert_handler(); \
    }                 \
  } while(0)   

#endif 
