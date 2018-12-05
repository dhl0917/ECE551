#ifndef INTER_H
#define INTER_H
#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "function.h"
#include "parser.h"

/*
Inter class is the parent class of Numinter and Mcinter because they all conform
to the "is a" kind relationship. 

#expr: Used to parse input.
#myFuncs: A pointer points to a map where we store all the defined functions.
#func: the Function * of the integrand.
#steps: The step we integrate in numint and the trials we will make in mcint.
#argv: A vector of pair. The pair consists two double. This vector stores the 
       lower and upper bound in pairs for every parameter in pairs.*/

/*
(constructor): Take const char** and map* two parameters and call initialize().

initialize(): Initialize all the fields to proper value according to input.

integrate(): This is an abstract function which is to be overloaded in the
children classes. Return a bool*/

class Inter
{
 private:
  const char ** expr;
  std::map<std::string, Function *> * myFuncs;
  Function * func;
  double steps;
  std::vector<std::pair<double, double> > argv;

 public:
  Inter(const char ** strp, std::map<std::string, Function *> * myMap) :
      expr(strp),
      myFuncs(myMap),
      func(NULL),
      steps(0) {
    *expr = *expr + 6;
    initialize();
  }
  void initialize();
  virtual bool integrate() = 0;
  Function * getFunction() { return func; }
  double getSteps() { return steps; }
  std::vector<std::pair<double, double> > getArgv() { return argv; }
  const char ** getExpr() { return expr; }
  virtual ~Inter(){};
};
#endif
