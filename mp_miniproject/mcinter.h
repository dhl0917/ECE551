#ifndef MCINTER_H
#define MCINTER_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <cstdlib>
#include <iostream>

#include "function.h"
#include "parser.h"
class Mcinter
{
 private:
  const char ** expr;
  std::map<std::string, Function *> * myFuncs;
  Function * func;
  double trials;
  std::vector<std::pair<double, double> > argv;

 public:
  Mcinter(const char ** strp, std::map<std::string, Function *> * myMap) :
      expr(strp),
      myFuncs(myMap),
      func(NULL),
      trials(0) {
    //skip "mcint"
    *expr = *expr + 5;
    initialize();
  }
  void initialize();
  double getRanDou(double low, double high);
  std::vector<double> getRanDouVec();
  double integrate();
  double multipleRanges();
  ~Mcinter() {}
};

#endif
