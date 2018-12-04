#ifndef MCINTER_H
#define MCINTER_H
#include "inter.h"

/*
Mcinter is the child class of the Inter. It is used to calculate the integration in 
Monte Carlo Integration. 
*/

/*
(constructor): Takes 2 parameters and calls the parent class's constructor to construct
the object.

getRandou(..): Take two parameters which are the lower and upper bound of the random 
double number generated. Return a random double number.

getRandouVec(): Call getRandou to generate a vector of random double numbers in valid
ranges.

integrate(): It overloads the function in the parent class to calculate the intergrate
value.

multipleRanges(): It returns the product of all the length of ranges. 
*/

class Mcinter : public Inter
{
 private:
 public:
  Mcinter(const char ** strp, std::map<std::string, Function *> * myMap) : Inter(strp, myMap) {}
  double getRanDou(double low, double high);
  std::vector<double> getRanDouVec();
  virtual void integrate();
  double multipleRanges();
  ~Mcinter() {}
};
#endif
