#include <stdio.h>

uint16_t reverse_prefix_sum(int8_t *a) {
  uint16_t r;

  if(*a == -1) return 0;
  r = reverse_prefix_sum(a+1) + (uint8_t)*a;
  *a = r;        /* may discard MSB */
  return(r);
}

void print_array(int8_t *a) {
  if(*a != -1) {
    printf("%d", (uint8_t)*a++);
    while(*a != -1) {
      printf(" %d", (uint8_t)*a++);
    }
  }
  printf("\n");
}

