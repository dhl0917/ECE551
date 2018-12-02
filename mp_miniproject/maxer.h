#ifndef MAX_H
#define MAX_H
#include <stdio.h>

#include <cstdlib>
#include <iostream>
#include <map>
#include <vector>

#include "function.h"
#include "parser.h"
#include "vector.h"
class Maxer
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
  Maxer(const char ** strp, std::map<std::string, Function *> * myMap) :
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
  double getMaximum();
  ~Maxer() {}
};

#endif
