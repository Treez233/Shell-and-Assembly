#include <stdio.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>
#include "serial.h"

extern uint8_t is_palindrome(const char *s);

int main() {
  const char *inputs[] = {
    "abba",
    "racecar",
    "swap paws",
    "not a palindrome",
    "another non palindrome",
    "almost but tsomla",
    NULL,
  };
  uint8_t i;

  init_serial_stdio();

  for(i = 0; inputs[i]; i++) {
    printf("%s -> %c\n", inputs[i], is_palindrome(inputs[i]) ? 'Y' : 'N');
  }

  cli();
  sleep_cpu();
}
  
