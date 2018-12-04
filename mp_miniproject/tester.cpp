#include "tester.h"

void Tester::test() {
  //parse input to expr
  Parser myParser(myFuncs);
  expr = myParser.parse(testExpr);
  if (expr == NULL) {
    std::cerr << "Expression side parsed failed.\n";
    return;
  }
  //parse input to ans
  ans = myParser.parse(testExpr);
  if (ans == NULL) {
    std::cerr << "Answer side parsed failed.\n";
    return;
  }
  //check the back of ans to see if there are unnecessary expressions.
  Expression * checkItsBack;
  checkItsBack = myParser.parse(testExpr);
  if (checkItsBack != NULL) {
    std::cerr << "More than one answers.\n";
    delete checkItsBack;
  }
  delete checkItsBack;
  //compare if expr == ans and give the result
  //if either expr's or ans's absolute value is less than 1,
  //adjust its display format to avoid scientific notion
  if (abs(expr->evaluate() - ans->evaluate()) < 0.0000000000001) {
    if (abs(expr->evaluate()) < 1 || abs(ans->evaluate()) < 1) {
      std::cout.setf(std::ios::fixed, std::ios::floatfield);
    }
    printCorrect();
    std::cout.unsetf(std::ios::fixed);
  }
  else {
    if (abs(expr->evaluate()) < 1 || abs(ans->evaluate()) < 1) {
      std::cout.setf(std::ios::fixed, std::ios::floatfield);
    }
    printInCorrect();
    std::cout.unsetf(std::ios::fixed);
  }
}

void Tester ::printCorrect() {
  std::cout.precision(13);  //display format
  std::string funcName;
  Parser myParser(myFuncs);
  funcName = myParser.getPrintFuncName(printPtr);
  if (funcName.size() == 0) {
    std::cout << expr->evaluate() << " = " << ans->evaluate() << " [CORRECT]\n";
  }
  else {
    std::cout << funcName << "(";
    myParser.printArgs(printPtr, funcName);
    std::cout << ")"
              << " = " << ans->evaluate() << " [CORRECT]\n";
  }
}
void Tester ::printInCorrect() {
  std::cout.precision(13);  //display format
  std::string funcName;
  Parser myParser(myFuncs);
  funcName = myParser.getPrintFuncName(printPtr);
  if (funcName.size() == 0) {
    std::cout << expr->evaluate() << " = " << ans->evaluate()
              << " [INCORRECT: expected: " << expr->evaluate() << "]\n";
  }
  else {
    std::cout << "(" << funcName << " ";
    myParser.printArgs(printPtr, funcName);
    std::cout << ")"
              << " = " << ans->evaluate() << " [INCORRECT: expected: " << expr->evaluate() << "]\n";
  }
}
