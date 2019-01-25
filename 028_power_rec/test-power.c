#include <stdio.h>
#include <stdlib.h>

unsigned power(unsigned x, unsigned y);
int run_check(unsigned x, unsigned y) {
  unsigned expected_ans = 1;
  for (unsigned i = 0; i < y; i++) {
    expected_ans = expected_ans * x;
  }

  unsigned ans = power(x, y);
  if (ans == expected_ans) {
    return 1;
  }
  else {
    return 0;
  }
}

int main() {
  for (unsigned i = 0; i <= 1000; i++) {
    for (unsigned j = 0; j <= 1000; j++) {
      if (!run_check(i, j)) {
        return EXIT_FAILURE;
      }
    }
  }
  return EXIT_SUCCESS;
}
