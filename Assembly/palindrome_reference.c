#include <string.h>
#include <stdio.h>

uint8_t is_palindrome(const char *string) {
  uint8_t i;
  uint8_t data_length = strlen(string);

  for (i = 0; i < data_length / 2; i++) {
    if (string[i] != string[data_length - i - 1]) {
      return 0;
    }
  }
  return 1;
}

