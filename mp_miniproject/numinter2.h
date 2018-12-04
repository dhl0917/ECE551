#ifndef NUMINTER2_H
#define NUMINTER2_H
#include "inter.h"

/*
Numinter class is the child class of Inter used for numint. It has 4 more fields, all of which 
play a role in the trapezoid method to calculate integration. 

#sum: The accumulation result of all the trapezoids so it is the answer as well.
#loopDepth: How deep we need iteration and it's equal to the amount of the function's argument. 
#factor: The small "area" we need to time every time.
#divider: Divider is the constant we need to divide to get the average for every
          coords. It is equal to the 2 to the loopDepth.*/

/*
(constructor): Take const char ** and map* two parameters. It calls the proper constructor
of the Inter first and then initialize the remain fields of its own.

intergrate(): It overloads the function in Inter. It modifies the field sum and make 
it equal to the answer at the end.

accumulate(..): It takes 4 parameters. pos is the depth of the current iteration. ranges
is the parameters' valid range. step is the integrate step. values is the generated 
vector. It generates all the parameter vectors in the valid range recursively.

span(..): It takes 4 parameters. pos is the depth of the current iteration. helperVector
is the parameters' valid range. step is the integrate step. res is the spanned
vector. It spans one coords(parameter vector) with the delta x in all possible 
directions. And calcuate the trapezoid's value, and then make a sum of them to
update the sum field to the value with this coords accumulated. */

class Numinter : public Inter
{
 private:
  double sum;
  int loopDepth;
  double factor;
  double divider;

 public:
  Numinter(const char ** strp, std::map<std::string, Function *> * myMap) :
      Inter(strp, myMap),
      sum(0),
      loopDepth(0),
      factor(0),
      divider(0) {
    loopDepth = getFunction()->getArgs().size();
    factor = pow(getSteps(), loopDepth);
    divider = pow(2, loopDepth);
  }
  virtual void integrate();
  void accumulate(int pos,
                  std::vector<std::pair<double, double> > & ranges,
                  double step,
                  std::vector<double> & values);
  void span(int pos, std::vector<double> & helperVector, double step, std::vector<double> & res);
  virtual ~Numinter() {}
};
#endif
