#ifndef UART_DRIVER_H
#define UART_DRIVER_H

void uart_init(void);
void uart_char_polling(char c);
void uart_print(char *str);

/*
  UART is a serial communication protocol that transmits data one bit at a time 
  tx send , rx receives 
  both agreee on baud rate to send data
 
  configure UART pins 
  choose clock - typically SMCLK 
  set baud rate - calc and config the divisor for your clock to acheive 9600
  enable UART module 
  wait for transmit buffer ready 
    0 continuously check the uart flag to see if hardware is ready to send 
  writ eto transmit buffer 
    TXBUF 
*/ 

#endif
