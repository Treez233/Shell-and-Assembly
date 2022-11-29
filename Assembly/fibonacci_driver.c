#include <stdio.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>
#include "serial.h"

extern int fib(int n);

int main() {
  uint16_t inputs[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 14, 16, 18, 20, 22, 23, 24, 0 };
  uint8_t i;

  init_serial_stdio();

  for(i = 0; inputs[i]; i++) {
    printf("%u -> %u\n", inputs[i], fib(inputs[i]));
  }

  cli();
  sleep_cpu();
}
  
