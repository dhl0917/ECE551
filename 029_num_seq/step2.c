#include <stdio.h>
#include <stdlib.h>
// This file is for Step 2.
// You should do
//  Step 2 (A): write seq2
int seq2(int x) {
  return x * (x + 3) + 1;
}
int sumSeq2(int low, int high);
//  Step 2 (B): write main to test seq2
int main() {
  // test case1 x=0
  if (seq2(0) == 1) {
    printf("seq2(%d)=%d\n", 0, seq2(0));
  }
  else {
    return EXIT_FAILURE;
  }
  //test case2 x=-4
  if (seq2(-4) == 5) {
    printf("seq2(%d)=%d\n", -4, seq2(-4));
  }
  else {
    return EXIT_FAILURE;
  }
  //test case3 x=14
  if (seq2(14) == 239) {
    printf("seq2(%d)=%d\n", 14, seq2(14));
  }
  else {
    return EXIT_FAILURE;
  }

  //  Step 2 (D): add test cases to main to test sumSeq2
  //test case1
  printf("sumSeq2(%d,%d)=%d\n", 0, 2, sumSeq2(0, 2));
  printf("sumSeq2(%d,%d)=%d\n", 3, 6, sumSeq2(3, 6));
  printf("sumSeq2(%d,%d)=%d\n", 9, 7, sumSeq2(9, 7));
  printf("sumSeq2(%d,%d)=%d\n", 0, 0, sumSeq2(0, 0));
  return EXIT_SUCCESS;
}

//  Step 2 (C): write sumSeq2
int sumSeq2(int low, int high) {
  int sum = 0;
  if (high > low) {
    for (int i = low; i < high; i++) {
      sum = sum + seq2(i);
    }
  }
  return sum;
}

//
// Be sure to #include any header files you need!
