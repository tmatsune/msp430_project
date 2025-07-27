#ifndef UART_DRIVER_H 
#define UART_DRIVER_H

void uart_init(void);
void uart_puts(char *s);
void print_polling(char *str);

#endif
