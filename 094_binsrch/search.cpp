#include <cstdio>
#include <cstdlib>

#include "function.h"

int binarySearchForZero(Function<int, int> * f, int low, int high) {
  /*
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
      low = m;
    }
  }
  if (x < 0) {
    m -= 1;
  }
  return m;
  */
  if (low >= high - 1) {
    return low;
  }
  else {
    int m = (low + high) / 2;
    int x = f->invoke(m);
    if (x == 0) {
      return m;
    }
    else if (x > 0) {
      return binarySearchForZero(f, low, m);
    }
    else {
      return binarySearchForZero(f, m, high);
    }
  }
}
