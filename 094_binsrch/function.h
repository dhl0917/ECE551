#include <cmath>
#include <cstdio>
#include <cstdlib>
#ifndef __FUNCTION_H__
#define __FUNCTION_H__
template<typename R, typename A>
class Function
{
 public:
  virtual R invoke(A arg) = 0;
  virtual ~Function() {}
};
/*
class CountedIntFn : public Function<int, int>
{
 protected:
  unsigned remaining;
  Function<int, int> * f;
  const char * mesg;

 public:
  CountedIntFn(unsigned n, Function<int, int> * fn, const char * m) :
      remaining(n),
      f(fn),
      mesg(m) {}
  virtual int invoke(int arg) {
    if (remaining == 0) {
      fprintf(stderr, "Too many function invocations in %s\n", mesg);
      exit(EXIT_FAILURE);
    }
    remaining--;
    return f->invoke(arg);
  }
};
int binarySearchForZero(Function<int, int> * f, int low, int high);

void check(Function<int, int> * f, int low, int high, int expected_ans, const char * mesg) {
  unsigned n = log(high - low) / log(2) + 1;
  CountedIntFn * c = new CountedIntFn(n, f, mesg);
  if (expected_ans != binarySearchForZero(c, low, high)) {
    fprintf(stderr, "Result Error!\n");
    exit(EXIT_FAILURE);
  }
  delete c;
}
*/
#endif
