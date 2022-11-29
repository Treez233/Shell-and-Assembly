#include <stdint.h>
/* from wikipedia, https://en.wikipedia.org/wiki/Integer_square_root */

typedef uint8_t the_type;

the_type isqrt(the_type n) {
  if(n<2) return n;
  the_type small = isqrt(n >> 2) << 1;
  the_type large = small + 1;
  if (large * large > n) 
    return small;
  else
    return large;
}
