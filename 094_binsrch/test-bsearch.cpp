#include <assert.h>

#include <cstdio>
#include <cstdlib>
#include <ostream>

#include "function.h"
#include "search.cpp"
class Fx : public Function<int, int>
{
 public:
  virtual int invoke(int arg) { return arg; }
};

class Fx1 : public Function<int, int>
{
 public:
  virtual int invoke(int arg) { return arg; }
};

int main() {
  Fx * myFx = new Fx();
  check(myFx, -1, 10, 0, "y=x_1");
  check(myFx, -5, -1, -2, "y=x_2");
  check(myFx, 1, 9, 1, "y=x_3");
  delete myFx;

  return EXIT_SUCCESS;
}
