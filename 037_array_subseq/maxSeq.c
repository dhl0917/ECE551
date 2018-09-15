#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n) {
  if (n <= 0) {
    return 0;
  }
  size_t count = 1;
  size_t biggest = 1;
  for (size_t i = 0; i < n - 1; i++) {
    if (array[i + 1] > array[i]) {
      count += 1;
    }
    else {
      if (count > biggest) {
        biggest = count;
      }
      count = 1;
    }
  }
  if (count > biggest) {
    biggest = count;
    count = 1;
  }
  return biggest;
}
