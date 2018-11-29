#ifndef DEFINER_H
#define DEFINER_H
#include <stdio.h>

#include <cstdlib>
#include <map>
#include <string>
#include <vector>

#include "function.h"
#include "parser.h"
class Definer
{
 private:
  const char ** defineExpr;
  std::map<std::string, Function *> * myFuncs;

 public:
  Definer(const char ** defExpr, std::map<std::string, Function *> * myMap) :
      defineExpr(defExpr),
      myFuncs(myMap) {}
  bool define();
  void print(Function * myFuncPter);
  ~Definer() {}
};
std::ostream & operator<<(std::ostream & s, std::vector<std::string> & v);
#endif
