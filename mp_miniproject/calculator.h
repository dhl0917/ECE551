#ifndef CALCULATOR_H
#define CALCULATOR_H
#include <stdio.h>

#include <cstdlib>
#include <iostream>
#include <map>
#include <string>

#include "definer.h"
#include "function.h"
#include "numinter.h"
#include "tester.h"
class Calculator
{
 private:
  std::map<std::string, Function *> * myFuncs;  //It's a * and remember to delete

 public:
  Calculator() : myFuncs(new std::map<std::string, Function *>){};
  void run();
  void printDef(Function * funcPointer);
  ~Calculator() {
    for (std::map<std::string, Function *>::iterator it = (*myFuncs).begin();
         it != (*myFuncs).end();
         ++it) {
      delete it->second;
    }
    delete myFuncs;
  }
};

#endif
