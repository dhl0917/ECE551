#ifndef EXTREMER_H
#define EXTREMER_H

#include <stdio.h>

#include <cstdlib>
#include <map>

#include "function.h"
#include "vector.h"
class Extremer
{
 private:
  const char ** expr;
  std::map<std::string, Function *> * myFuncs;
  Function * func;
  double gamma;
  double convergedDistance;
  Vector startPoint;
  int trials;

 public:
  Extremer(const char ** strp, std::map<std::string, Function *> * myMap) :
      expr(strp),
      myFuncs(myMap),
      func(NULL),
      gamma(0),
      convergedDistance(0),
      trials(0) {
    //skip "max"
    *expr = *expr + 3;
    initialize();
  }
  void initialize();
  void getMaximum();
  void getMinimum();
  ~Extremer() {}
};

#endif
