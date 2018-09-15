#include <stdio.h>
#include <stdlib.h>
// This file is for Step 3.
// You should do
//  Step 3 (A): write seq3
int seq3(int x, int y) {
  return (-3 + y) * x + 2 * y;
}
int countEvenInSeq3Range(int xLow, int xHi, int yLow, int yHi);
//  Step 3 (B): write main to test seq3
int main() {
  int a;
  int b;
  int ans;
  //test case1 (-5,-3)
  a = -5;
  b = -3;
  ans = seq3(a, b);
  if (ans == 24) {
    printf("seq3(%d,%d)=%d\n", a, b, ans);
  }
  else {
    return EXIT_FAILURE;
  }
  //test case2 (2,-4)
  a = 2;
  b = -4;
  ans = seq3(a, b);
  if (ans == -22) {
    printf("seq3(%d,%d)=%d\n", a, b, ans);
  }
  else {
    return EXIT_FAILURE;
  }
  //test case3 (-1,5)
  a = -1;
  b = 5;
  ans = seq3(a, b);
  if (ans == 8) {
    printf("seq3(%d,%d)=%d\n", a, b, ans);
  }
  else {
    return EXIT_FAILURE;
  }
  //test case4 (1,4)
  a = 1;
  b = 4;
  ans = seq3(a, b);
  if (ans == 9) {
    printf("seq3(%d,%d)=%d\n", a, b, ans);
  }
  else {
    return EXIT_FAILURE;
  }
  //test case5 (0,0)
  a = 0;
  b = 0;
  ans = seq3(a, b);
  if (ans == 0) {
    printf("seq3(%d,%d)=%d\n", a, b, ans);
  }
  else {
    return EXIT_FAILURE;
  }
  //  Step 3 (D): add test cases to main to test countEvenInSeq3Range
  //test case1 (0,2,0,3)
  printf("countEvenInSeq3Range(%d,%d,%d,%d)=%d\n", 0, 2, 0, 3, countEvenInSeq3Range(0, 2, 0, 3));
  //test case2 (0,0,1,5)
  printf("countEvenInSeq3Range(%d,%d,%d,%d)=%d\n", 0, 0, 1, 5, countEvenInSeq3Range(0, 0, 1, 5));
  //test case3(-3,-1,0,2)
  printf(
      "countEvenInSeq3Range(%d,%d,%d,%d)=%d\n", -3, -1, 0, 2, countEvenInSeq3Range(-3, -1, 0, 2));

  return EXIT_SUCCESS;
}
//  Step 3 (C): write countEvenInSeq3Range
int countEvenInSeq3Range(int xLow, int xHi, int yLow, int yHi) {
  int count = 0;
  for (int i = xLow; i < xHi; i++) {
    for (int j = yLow; j < yHi; j++) {
      if (seq3(i, j) % 2 == 0) {
        count += 1;
      }
    }
  }
  return count;
}
//
// Be sure to #include any header files you need!
