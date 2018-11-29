#ifndef FUNCTION_H
#define FUNCTION_H

#include <float.h>
#include <stdio.h>
#include <string.h>

#include <cstdlib>
#include <iostream>
#include <map>
#include <vector>

//#include "myExpr.h"
#include "parser.h"
class Function
{
 private:
  std::string name;
  std::vector<std::string> defArgv;
  std::string defExpr;
  std::string evalExpr;
  std::map<std::string, Function *> * myFuncs;

  void skipSpace(const char ** strp);
  std::string dou2str(double arg);

 public:
  Function(std::string funcName,
           std::vector<std::string> argv,
           std::string funcExpr,
           std::map<std::string, Function *> * myMap) :
      name(funcName),
      defArgv(argv),
      defExpr(funcExpr),
      myFuncs(myMap){};
  std::string getEvalExpr() const { return evalExpr; }
  void setViaDou(std::vector<double> valVector);
  void setViaPointer(const char ** strp);
  double evaluate();
  std::string getName() const { return name; }
  std::vector<std::string> getArgs() { return defArgv; }
  /*
  Expression * parse(const char ** strp);
  Expression * parseOp(const char ** strp);
  std::string parseFuncName(const char ** strp);
  bool isValidSglArgFunc(std::string funcName);
  bool isValidDouFunc(std::string funcName);
  Expression * makeSglExpr(std::string funcName, Expression * arg);
  Expression * makeDouExpr(std::string op, Expression * lhs, Expression * rhs);
  Expression * parseArgs(const char ** strp, Function * tarFunc);
  */
  ~Function(){};
};
#endif
