#include <stdio.h>
#include <stdint.h>

// gcc -Wall -W testing.c -o output
//     8421
// 00000001 1
// 00000010 2
// 00000011 3
// 00000100 4
// 00000101 5
// 00000110 6
// 00000111 7
//
// 00001000 8
// 00001001 9
// 00001010 10
// 00001011 11
// 00001100 12
// 00001101 13
// 00001110 14
// 00001111 15
//
// 00010000 16

#define PORT_OFFSET (3 << 3)

#define UNUSED(a) (void)(a)
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

void print_binary(uint8_t value) {
    for (int i = 7; i >= 0; i--) {
        putchar((value & (1 << i)) ? '1' : '0');
    }
    printf("\n");
}

typedef enum {
  PIN10, PIN11, PIN12, PIN13, PIN14, PIN15, PIN16, PIN17,
  PIN20, PIN21, PIN22, PIN23, PIN24, PIN25, PIN26, PIN27,
} Pin;

int get_port(Pin pin)
{
  return ((PORT_OFFSET & pin) >> 3) + 1;
}
int get_pin_num(Pin pin)
{
  return 7 & pin;
}
int get_bit(Pin pin)
{
  int num = get_pin_num(pin);
  return (1 << (num));
}

int main(void)
{
  Pin pin1 = PIN10;
  Pin pin2 = PIN20;

  int port1 = get_port(pin1);
  int port2 = get_port(pin2);

  printf("port for pin 1: %d\n", port1);
  printf("port for pin 2: %d\n", port2);
  
  Pin pins1[] = {PIN10, PIN11, PIN12, PIN13, PIN14, PIN15, PIN16, PIN17};
  for(int i=0;i < ARRAY_SIZE(pins1);i++){
    int bit = get_bit(pins1[i]);
    print_binary(bit);
  }
  
  printf("\n");
  Pin pins2[] = {PIN20, PIN21, PIN22, PIN23, PIN24, PIN25, PIN26, PIN27};
  for(int i=0;i < ARRAY_SIZE(pins2);i++){
    int bit = get_bit(pins2[i]);
    print_binary(bit);
  }



  return 0;
}
