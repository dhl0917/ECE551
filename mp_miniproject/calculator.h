#ifndef CALCULATOR_H
#define CALCULATOR_H
#include <stdio.h>

#include <cstdlib>
#include <iostream>
#include <map>
#include <string>

#include "definer.h"
#include "extremer.h"
#include "function.h"
#include "mcinter2.h"
#include "numinter2.h"
#include "tester.h"
/*
Calculator class is the numeric calculator on which all our numeric methods, 
integrate and optimize functions implement. 

#myFuncs: A pointer points to a map where we store all the defined functions.*/

/*
(constructor): New an empty map and return the pointer to myFuncs.

run(): Entrance method.

(destructor): Free all the function * in the map and the map itself.*/

class Calculator
{
 private:
  std::map<std::string, Function *> * myFuncs;

 public:
  Calculator() : myFuncs(new std::map<std::string, Function *>){};
  void run();
  //  void printDef(Function * funcPointer);
  ~Calculator() {  //free all the function * in the map
    for (std::map<std::string, Function *>::iterator it = (*myFuncs).begin();
         it != (*myFuncs).end();
         ++it) {
      delete it->second;
    }
    delete myFuncs;  //free the map
  }
};

#endif
