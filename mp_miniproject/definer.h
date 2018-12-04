#ifndef DEFINER_H
#define DEFINER_H
#include <stdio.h>

#include <cstdlib>
#include <map>
#include <string>
#include <vector>

#include "function.h"
#include "parser.h"

/*
The Definer class is used when define functions. 

#defineExpr: A pointer points to a pointer to char used to parse input.
#myFuncs: A pointer points to a map where we store all the defined functions.*/

/*
(constructor): Initialize defineExpr and myFuncs.

define(): Parse the input and store the parsed function name and 
function * into the map. Print error messages and return false 
when encountered any problem. Return true otherwise.
 
print(Function * myFuncPter): Take a function * as parameter and print out 
its function name and parameters after defined.*/

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
//output stream used in print function
std::ostream & operator<<(std::ostream & s, std::vector<std::string> & v);
#endif
