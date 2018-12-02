#ifndef MCINTER_H
#define MCINTER_H
#include "inter.h"

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
