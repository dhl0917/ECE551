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
    Parser myParser(myFuncs);
    std::string funcName = myParser.parseFuncName(expr);
    func = (*myFuncs)[funcName];
    Expression * mySteps = myParser.parse(expr);
    steps = mySteps->evaluate();
    delete mySteps;
    for (size_t i = 0; i < func->getArgs().size(); ++i) {  //what if not enough
      Expression * low = myParser.parse(expr);
      Expression * high = myParser.parse(expr);  //check result???
      argv.push_back(std::pair<double, double>(low->evaluate(), high->evaluate()));
      delete low;
      delete high;
    }
  }
  virtual void integrate() = 0;
  Function * getFunction() { return func; }
  double getSteps() { return steps; }
  std::vector<std::pair<double, double> > getArgv() { return argv; }
  virtual ~Inter(){};
};
#endif
