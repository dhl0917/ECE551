#ifndef MAXER_H
#define MAXER_H
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
  //  Point p;
  Vector startPoint;
  //  std::vector<double> startPoint;
  int trials;

 public:
  Maxer(const char ** strp, std::map<std::string, Function *> * myMap) :
      expr(strp),
      myFuncs(myMap),
      func(NULL),
      gamma(0),
      convergedDistance(0),
      trials(0) {
    initialize();
    //skip "max"
    *strp = *strp + 3;
  }
  void initialize();
  double getMaximum();
};

#endif
