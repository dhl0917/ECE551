#ifndef TESTER_H
#define TESTER_H
#include <stdio.h>

#include <cstdlib>
#include <map>

#include "function.h"
#include "parser.h"
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
