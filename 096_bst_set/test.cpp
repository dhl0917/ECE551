#include <assert.h>

#include <cstdio>
#include <cstdlib>

#include "bstset.h"
void check(void) {
  BstSet<int> b;
  b.add(0);
  b.add(-1);
  b.add(2);
  assert(b.contains(0) == true);
  assert(b.contains(1) == false);
  b.remove(0);
  assert(b.contains(0) == false);
  BstSet<int> b1(b);
  b.add(10);
  b1 = b;
}

int main() {
  check();
  return EXIT_SUCCESS;
}
