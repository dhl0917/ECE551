#include "function.h"

//private methods
void Function::skipSpace(const char ** strp) {
  while (isspace(**strp)) {
    *strp = *strp + 1;
  }
}

std::string Function::dou2str(double arg) {
  std::stringstream strStream;
  std::string myStr;
  strStream << arg;
  strStream >> myStr;
  return myStr;
}

//public methods
void Function::demoTest() {
  std::vector<double> demoArgv;
  for (size_t i = 0; i < defArgv.size(); i++) {
    demoArgv.push_back(1);
  }
  Parser myParser(myFuncs);
  setViaDou(demoArgv);
  const char * demoPtr = &evalExpr[0];
  Expression * demoParsed = NULL;
  demoParsed = myParser.parse(&demoPtr);
  if (demoParsed == NULL) {
    std::cerr << "Invalid function.\n";
    valid = false;
    return;
  }
  //check its back
  skipSpace(&demoPtr);
  if (*demoPtr != '\0') {
    std::cerr << "Invalid right hand side expression of the function.\n";
    valid = false;
    delete demoParsed;
    return;
  }
  /*
  Expression * checkItsBack = myParser.parse(&demoPtr);
  if (checkItsBack != NULL) {
    std::cerr << "Invalid right hand side expression of the function.\n";
    valid = false;
    delete demoParsed;
    delete checkItsBack;
    return;
  }
  */
  delete demoParsed;
}

void Function::setViaDou(std::vector<double> valVector) {
  if (valVector.size() != defArgv.size()) {
    //  std::cerr << "Cannot set via double vector.\n";
    evalExpr.clear();
    return;
  }
  evalExpr = defExpr;
  for (size_t i = 0; i < defArgv.size(); i++) {
    int pos = evalExpr.find(defArgv[i]);
    while (pos != -1) {
      evalExpr.replace(pos, defArgv[i].length(), dou2str(valVector[i]));
      pos = evalExpr.find(defArgv[i]);
    }
  }
}
void Function::setViaPointer(const char ** strp) {
  skipSpace(strp);
  std::vector<double> valVector;
  size_t n = defArgv.size();
  for (size_t i = 0; i < n; i++) {
    Parser myParser(myFuncs);
    Expression * arg = myParser.parse(strp);
    if (arg == NULL) {  //check parsed result.
      //  std::cerr << "Cannot set value via pointer.\n";
      //      valVector.clear();
      evalExpr.clear();
      return;
    }
    valVector.push_back(arg->evaluate());
    delete arg;
  }
  setViaDou(valVector);
}

double Function::evaluate() {
  const char * pointerToEvalExpr = &evalExpr[0];
  Parser myParser(myFuncs);
  Expression * parsedExpr = myParser.parse(&pointerToEvalExpr);
  /*
  if (parsedExpr == NULL) {  //check paresd result
    std::cerr << "Cannot parse and evaluate.\n";
    // exit(EXIT_FAILURE);
    return DBL_MIN;  //return DBL_MIN to indicate failure?????
  }
  */
  double ans = parsedExpr->evaluate();
  delete parsedExpr;
  return ans;
}

Vector Function::gradient(Vector v) {
  setViaDou(v.getCoords());
  double funcValue = evaluate();
  std::vector<double> res;
  res.resize(defArgv.size());
  for (size_t i = 0; i < defArgv.size(); i++) {
    std::vector<double> temp = v.getCoords();
    //make delta be 0.01 of the current value
    double delta = temp[i] * 0.01;
    if (delta == 0) {
      delta = 0.01;
    }
    temp[i] += delta;
    setViaDou(temp);
    res[i] = ((evaluate() - funcValue) / delta);
  }
  return Vector(res);
}
