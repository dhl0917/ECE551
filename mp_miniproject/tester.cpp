#include "tester.h"

void Tester::test() {
  Parser myParser(myFuncs);
  expr = myParser.parse(testExpr);
  if (expr == NULL) {
    std::cerr << "Expression side parsed failed.\n";
    //    delete expr;
    return;
  }
  ans = myParser.parse(testExpr);
  if (ans == NULL) {
    std::cerr << "Answer side parsed failed.\n";
    // delete ans;
    // delete expr;
    return;
  }
  Expression * checkItsBack;
  checkItsBack = myParser.parse(testExpr);
  if (checkItsBack != NULL) {
    std::cerr << "More than one answers.\n";
    delete checkItsBack;
    // delete expr;
    // delete ans;
  }
  delete checkItsBack;
  if (abs(expr->evaluate() - ans->evaluate()) < 0.0000000000001) {
    printCorrect();
  }
  else {
    printInCorrect();
  }
}

void Tester ::printCorrect() {
  std::string funcName;
  Parser myParser(myFuncs);
  funcName = myParser.getPrintFuncName(printPtr);
  if (funcName.size() == 0) {
    std::cout << expr->toString() << " = " << ans->evaluate() << " [CORRECT]\n";
  }
  else {
    std::cout << funcName << "(";
    myParser.printArgs(printPtr, funcName);
    std::cout << ")"
              << " = " << ans->evaluate() << " [CORRECT]\n";
  }
}
void Tester ::printInCorrect() {
  std::string funcName;
  Parser myParser(myFuncs);
  funcName = myParser.getPrintFuncName(printPtr);
  if (funcName.size() == 0) {
    std::cout << expr->toString() << " = " << ans->evaluate()
              << " [INCORRECT: expected: " << expr->evaluate() << "]\n";
  }
  else {
    std::cout << "(" << funcName;
    myParser.printArgs(printPtr, funcName);
    std::cout << ")"
              << " = " << ans->evaluate() << " [INCORRECT: expected: " << expr->evaluate() << "]\n";
  }
}
