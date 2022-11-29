#include <stdio.h>
#include "pins_arduino.h"
#include "serial.h"

static int uart_putchar(char c, FILE *stream);
static FILE mystdout = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);

static int uart_putchar(char c, FILE *stream) {
  if (c == '\n')
    uart_putchar('\r', stream);
  loop_until_bit_is_set(UCSR1A, UDRE1);
  UDR1 = c;
  return 0;
}

void init_serial_stdio(void) {
  stdout = &mystdout;
  printf("Serial simulator online.\n");
}

