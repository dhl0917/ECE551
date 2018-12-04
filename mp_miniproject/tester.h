#ifndef TESTER_H
#define TESTER_H
#include <stdio.h>

#include <cstdlib>
#include <map>

#include "function.h"
#include "parser.h"

/*
Tester is used when we detect key word "test" and need to test if the expressions
are equal. 

#testExpr: Used to parse the input.
#printPtr: Used to print the arguments we test the function.
#myFuncs: A pointer points to a map where we store all the defined functions.
#expr: The parsed function expression.
#ans:  The parsed function expression.*/

/*
(constructor): Take two const char** and one map* parameters and then initialize 
all the fields. Then make the *testExpr and *printPtr plus 4 to skip the key
word "test".

test(): The entrance of class Tester. Parse the input to expr and ans. Use the 
evaluate() method to calculate the value of both sides and then give the result.

printCorrect(): Used when the value of expr is equal to ans to output result.

printInCorrect(): Used when the value of expr is not equal to ans to output result.

(destructor): Free expr and ans.*/

class Tester
{
 private:
  const char ** testExpr;
  const char ** printPtr;
  std::map<std::string, Function *> * myFuncs;
  Expression * expr;
  Expression * ans;

 public:
  Tester(const char ** ptrToExpr,
         const char ** ptrToPrint,
         std::map<std::string, Function *> * myMap) :
      testExpr(ptrToExpr),
      printPtr(ptrToPrint),
      myFuncs(myMap),
      expr(NULL),
      ans(NULL) {
    //skip "test"
    *testExpr = *testExpr + 4;
    *printPtr = *printPtr + 4;
  }
  void test();
  void printCorrect();
  void printInCorrect();
  ~Tester() {
    delete expr;
    delete ans;
  }
};
#endif
