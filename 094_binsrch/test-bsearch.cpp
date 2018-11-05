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
  check(myFx, -20, -1, -2, "y=x_2");
  check(myFx, 10, 20, 10, "y=x_3");
  delete myFx;

  return EXIT_SUCCESS;
}
