#include <stdio.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>
#include "serial.h"

extern uint8_t isqrt(uint8_t n);

int main() {
  uint16_t inputs[] = { 1, 12, 225, 169, 16, 25, 100, 81, 99, 121, 144, 0 };
  uint8_t i;
  init_serial_stdio();

  for(i = 0; inputs[i]; i++) {
    printf("%d -> %d\n", inputs[i], isqrt(inputs[i]));
  }

  cli();
  sleep_cpu();
}
  
