#include "inter.h"

void Inter::initialize() {
  Parser myParser(myFuncs);
  std::string funcName = myParser.parseFuncName(expr);
  if ((*myFuncs).count(funcName) <= 0) {  //invalid funcname
    std::cerr << "Invalid function name./n";
    expr = NULL;
    return;
  }
  func = (*myFuncs)[funcName];
  Expression * mySteps = myParser.parse(expr);
  if (mySteps == NULL) {  //invalid step/trials
    std::cerr << "Invalid input for step/trials.";
    expr = NULL;
    return;
  }
  steps = mySteps->evaluate();
  delete mySteps;
  for (size_t i = 0; i < func->getArgs().size(); ++i) {  //what if not enough
    Expression * low = myParser.parse(expr);
    if (low == NULL) {  //Invalid lower bound
      std::cerr << "Invalid lower bound.\n";
      expr = NULL;
      return;
    }
    Expression * high = myParser.parse(expr);  //check result???
    if (high == NULL) {                        //Invalid upper bound
      std::cerr << "Invalid upper bound.\n";
      delete low;
      expr = NULL;
      return;
    }
    if (low->evaluate() > high->evaluate()) {
      std::cerr << "Lower bound should be less than or equal to upper bound.\n";
      delete low;
      delete high;
      expr = NULL;
      return;
    }
    argv.push_back(std::pair<double, double>(low->evaluate(), high->evaluate()));
    delete low;
    delete high;
  }
  Expression * checkItsBack = myParser.parse(expr);
  if (checkItsBack != NULL) {
    std::cerr << "Unnecessary parameters.\n";
    expr = NULL;
    delete checkItsBack;
    return;
  }
}
