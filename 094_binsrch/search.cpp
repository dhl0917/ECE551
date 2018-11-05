#include <cstdio>
#include <cstdlib>

#include "function.h"

int binarySearchForZero(Function<int, int> * f, int low, int high) {
  int m;
  int x;
  if (low == high) {
    return low;
  }
  while (high > low) {
    m = (low + high) / 2;
    x = f->invoke(m);
    if (x > 0) {
      high = m;
    }
    else if (x == 0) {
      return m;
    }
    else {
      low = m + 1;
    }
  }
  if (x < 0) {
    m = m - 1;
  }
  return m;
}
