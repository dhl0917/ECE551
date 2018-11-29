#ifndef NUMINTER_H
#define NUMINTER_H
#include <stdio.h>

#include <cstdlib>
#include <iostream>
#include <map>
#include <vector>

#include "function.h"
#include "parser.h"
class Numinter
{
 private:
  const char ** expr;
  std::map<std::string, Function *> * myFuncs;
  Function * func;
  double step;
  std::vector<std::pair<double, double> > argv;
  double sum;
  int loopDepth;
  double factor;
  double divider;
  //  std::vector<std::pair<int, int> > spanHelper;

 public:
  Numinter(const char ** strp, std::map<std::string, Function *> * myMap) :
      expr(strp),
      myFuncs(myMap),
      func(NULL),
      step(0),
      sum(0),
      loopDepth(0),
      factor(0),
      divider(0) {
    //skip "numint"
    *expr = *expr + 6;
    initialize();
  }
  /*
  Numinter(Function * myFunc, double myStep, std::vector<std::pair<double, double> > argVector) :
      func(myFunc),
      step(myStep),
      argv(argVector),
      sum(0) {
    loopDepth = func->getArgs().size();
  }
  */
  double integrate();
  void accumulate(int pos,
                  std::vector<std::pair<double, double> > & ranges,
                  double step,
                  std::vector<double> & values);
  void span(int pos, std::vector<double> & helperVector, double step, std::vector<double> & res);
  void initialize();
  ~Numinter() {}
};
#endif
