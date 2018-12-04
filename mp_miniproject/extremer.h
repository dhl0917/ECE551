#ifndef EXTREMER_H
#define EXTREMER_H

#include <stdio.h>

#include <cstdlib>
#include <map>

#include "function.h"
#include "vector.h"

/*
Extremer is a class used to find the maximum and minimum value of a given fucntion.
It has seven fields. expr is used to parse the input. map* points to the map we
used to store the functions. func is the Function * of the function we need to 
find its maximum and minimum value. gamma is the constant. convergedDistance is 
the distance within which we regard it is close enough. startPoint is the start
coords while trials is the most time we try this method before we give up.
*/

/*
constructor: Take two arguments. Initialize the fields according to the corresponding
parameters or default value. 

initialize(): Through the expr to parse the input and modify the fields according
the input.

getMaximum(): Find the maximum value and output it.

getMinimum(): Find the minimum value and output it.
*/

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
