#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <string.h>

#include <cstdlib>
#include <iostream>
#include <map>
#include <vector>

#include "myExpr.h"

/*
Parser is a class used to parse input. 

#myFuncs:  A pointer points to a map where we store all the defined functions.*/

/*
______________________
Private member methods:
skipSpace(..): A private member method used to skip space.

______________________
Public member methods:

(constructor): Take one argument map* which is used to initialize myFuncs.

parse(..): Take one argument const char **. It parses the input(with parseOp) and
return an Expression *.

parseOp(..): Take one argument const char **. It parses the input(with parse) and
return an Expression *.

parseFuncName(..): Take one argument const char **. It parses and returns the function 
name from the input.

isValidSglArgfunc(..): Judge if it is the sort of function that only needs one argument.

isValidDouFunc(..): Judge if it is the sort of function that needs two argument.

makeSglExpr(..): Allocate a SglExpression object and return a pointer pointing it.

makeDouExpr(..): Allocate a corresponding double argument expression object and
return a pointer pointing it.

parseArgs(..): Find the specific expression storing in the map and replace all the
parameters with test numeric numbers. Then parse it and return the parsed result
which is an Expression *.

parseDef(..): Parse the input of "define" and new a function object and return
a Function * pointing at it.

parseFuncArgs(..): Extract and return all the arguments from the input in a 
vector of string.

parseFuncExpr(..): Extract and return the expression exactly as it is as in a string
and return. 

getPrintFuncName(..): Extract the function name and return it in a string.

printArgs(..): Use printPtr to print the arguments exactly as it inputs.*/

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
