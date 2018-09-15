#include <stdio.h>
#include <stdlib.h>
// This file is for Step 1.
// You should do
//  Step 1 (A): write seq1
void printSeq1Range(int low, int high);
int seq1(int x) {
  int ans;
  ans = 4 * x - 3;
  return ans;
}
//  Step 1 (B): write main to test seq1
int main() {
  // Test case1
  int x = 0;
  int ans = seq1(x);
  if (ans == -3) {
    printf("seq1(%d)=%d\n", x, ans);
  }
  else {
    return EXIT_FAILURE;
  }
  // Test case2
  x = 10;
  ans = seq1(x);
  if (ans == 37) {
    printf("seq1(%d)=%d\n", x, ans);
  }
  else {
    return EXIT_FAILURE;
  }
  // Test case3
  x = -4;
  ans = seq1(x);
  if (ans == -19) {
    printf("seq1(%d)=%d\n", x, ans);
  }
  else {
    return EXIT_FAILURE;
  }

  //  Step 1 (D): add test cases to main to test printSeq1Range
  // Test case1
  printf("printSeq1Range(%d,%d)\n", 0, 4);
  printSeq1Range(0, 4);
  // Test case2
  printf("printSeq1Range(%d,%d)\n", -2, 6);
  printSeq1Range(-2, 6);
  // Test case3
  printf("printSeq1Range(%d,%d)\n", 7, 3);
  printSeq1Range(7, 3);
  // Test case4
  printf("printSeq1Range(%d,%d)\n", 0, 0);
  printSeq1Range(0, 0);

  return EXIT_SUCCESS;
}
//  Step 1 (C): write printSeq1Range
void printSeq1Range(int low, int high) {
  if (high > low) {
    printf("%d", seq1(low));
    for (int i = low + 1; i < high; i++) {
      printf(", %d", seq1(i));
    }
  }
  printf("\n");
}
//
// Be sure to #include any header files you need!
