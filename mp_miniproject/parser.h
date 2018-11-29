#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <string.h>

#include <cstdlib>
#include <iostream>
#include <map>
#include <vector>

#include "myExpr.h"
//#include "function.h"

class Function;
class Parser
{
 private:
  std::map<std::string, Function *> * myFuncs;

  void skipSpace(const char ** strp);

 public:
  Parser(std::map<std::string, Function *> * myMap) : myFuncs(myMap){};
  Expression * parse(const char ** strp);
  Expression * parseOp(const char ** strp);
  std::string parseFuncName(const char ** strp);
  bool isValidSglArgFunc(std::string funcName);
  bool isValidDouFunc(std::string funcName);
  Expression * makeSglExpr(std::string funcName, Expression * arg);
  Expression * makeDouExpr(std::string op, Expression * lhs, Expression * rhs);
  Expression * parseArgs(const char ** strp, Function * tarFunc);
  Function * parseDef(const char ** strp);
  std::vector<std::string> parseFuncArgs(const char ** defineExpr);
  std::string parseFuncExpr(const char ** defineExpr);
  std::string getPrintFuncName(const char ** strp);
  void printArgs(const char ** strp, std::string funcName);
  ~Parser(){};
};

#endif
