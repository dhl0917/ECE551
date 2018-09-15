#include <stdio.h>
#include <stdlib.h>
size_t maxSeq(int * array, size_t n);
int main() {
  //test case 1
  int a[] = {1, 2, 1, 3, 5, 8, 2, 4, 6, 9};
  if (maxSeq(a, 10) != 4) {
    return EXIT_FAILURE;
  }
  //test case2
  int b[] = {1, -2, 2, 3, 5, 5, 6, 2};
  if (maxSeq(b, 8) != 4) {
    return EXIT_FAILURE;
  }
  //test case3
  int c[] = {0, 0, 0, 0};
  if (maxSeq(c, 4) != 1) {
    return EXIT_FAILURE;
  }
  //test case4
  int d[1];
  if (maxSeq(d, 0) != 0) {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
