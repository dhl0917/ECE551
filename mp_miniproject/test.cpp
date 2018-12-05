#include <stdio.h>

#include <cstdlib>

#include "calculator.h"
#include "function.h"
#include "vector.h"
int main() {
  //creat an obect
  Calculator myCalculator;
  if (myCalculator.run() == false) {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
