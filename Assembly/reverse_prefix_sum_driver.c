#include <stdio.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>
#include "serial.h"

extern uint16_t reverse_prefix_sum(int8_t *v);
extern void print_array(int8_t *v);

int8_t data1[] = { 1, 2, 3, 4, -1 };
int8_t data2[] = { 2, 3, 4, 5, -1 };
int8_t data3[] = { 5, 4, 3, 2,  -1 };
int8_t data4[] = { 1, 2, 1, 2, 1, 2, 3, 1, 2, 3, 1, 2, 3, 4, -1 };
int8_t overflow[] = { 3, 254, -1, };
int8_t slowoverflow[] = { 100, 100, 100, 100, 100, 100, -1, };

void c_print_array(int8_t *v) {
  int8_t n = *v;
  if(n!=-1) {
    do { 
      printf("%d", n);
      n = *(++v);
      if(n==-1) break;
      putchar(' ');
    } while(1);
  }
  printf("\n");
}

int main() {
  uint16_t ret;
  init_serial_stdio();
  print_array(data1);
  c_print_array(data1);
  ret = reverse_prefix_sum(data1);
  print_array(data1);
  print_array(data2);
  ret = reverse_prefix_sum(data2);
  print_array(data2);
  print_array(data3);
  ret = reverse_prefix_sum(data3);
  print_array(data3);
  print_array(data4);
  ret = reverse_prefix_sum(data4);
  print_array(data4);

  print_array(overflow);
  ret = reverse_prefix_sum(overflow);
  print_array(overflow);
  printf("should be 257: %d\n", ret);

  print_array(slowoverflow);
  ret = reverse_prefix_sum(slowoverflow);
  print_array(slowoverflow);
  printf("should be 600: %d\n", ret);

  cli();
  sleep_cpu();
}
