#ifndef NUMINTER2_H
#define NUMINTER2_H
#include "inter.h"

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
