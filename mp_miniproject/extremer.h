#ifndef EXTREMER_H
#define EXTREMER_H

#include <stdio.h>

#include <cstdlib>
#include <map>

#include "function.h"
#include "vector.h"

/*
Extremer is a class used to find the maximum and minimum value of a given fucntion.

#expr: A pointer to pointer used to parse the input.
#myFuncs: A pointer points to the map we used to store the functions.
#func: The Function * of the function we need to find its maximum and minimum value.
#gamma: The constant.
#convergeddistance: The distance within which we regard as convergence.
#startpoint: The start coords.
#trials: The most time we try before we give up.*/

/*
(constructor): Take two arguments. Initialize the fields according to the corresponding
parameters or default value. 

initialize(): Through the expr to parse the input and modify the fields according
the input.

getMaximum(): Find the maximum value and output it. Return false when failed.

getMinimum(): Find the minimum value and output it. Return false when failed.*/

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
  bool getMaximum();
  bool getMinimum();
  ~Extremer() {}
};

#endif
