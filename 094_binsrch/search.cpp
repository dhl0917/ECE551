#include <cstdio>
#include <cstdlib>

//#include "function.h"

int binarySearchForZero(Function<int, int> * f, int low, int high) {
  int m;
  while (high >= low) {
    m = (low + high) / 2;
    int x = f->invoke(m);
    if (x > 0) {
      high = m - 1;
    }
    else if (x == 0) {
      return m;
    }
    else {
      low = m + 1;
    }
  }
  if (m < 0) {
    m = m - 1;
  }
  return m;
}
