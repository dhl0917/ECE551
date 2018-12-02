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
void Function::setViaDou(std::vector<double> valVector) {
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
    //    Expression * arg = parse(strp);
    if (arg == NULL) {  //check parsed result.
      std::cerr << "Cannot set value via pointer.\n";
      exit(EXIT_FAILURE);
    }
    valVector.push_back(arg->evaluate());
    delete arg;
  }
  setViaDou(valVector);
}

double Function::evaluate() {
  if (evalExpr.size() == 0) {
    std::cerr << "Failure set.\n";
    exit(EXIT_FAILURE);
  }
  const char * pointerToEvalExpr = &evalExpr[0];
  Parser myParser(myFuncs);
  Expression * parsedExpr = myParser.parse(&pointerToEvalExpr);
  //  Expression * parsedExpr = parse(&pointerToEvalExpr);
  if (parsedExpr == NULL) {  //check paresd result
    std::cerr << "Cannot parse and evaluate.\n";
    // exit(EXIT_FAILURE);
    return DBL_MIN;  //return DBL_MIN to indicate failure
  }
  double ans = parsedExpr->evaluate();
  delete parsedExpr;
  return ans;
}
Vector Function::gradient(Vector v) {
  //  double delta = 0.001;  //Define delta = 0.001
  setViaDou(v.getCoords());
  double funcValue = evaluate();
  std::vector<double> res;
  res.resize(defArgv.size());
  for (size_t i = 0; i < defArgv.size(); i++) {
    std::vector<double> temp = v.getCoords();
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

/*
Expression * Function::parse(const char ** strp) {
  skipSpace(strp);
  if (**strp == '\0') {
    // std::cerr << "End of line found mid expression!\n";
    return NULL;
  }
  else if (**strp == '(') {
    // (op E E)
    *strp = *strp + 1;
    return parseOp(strp);
  }
  else {
    //number
    char * endp;
    // long num = strtol(*strp, &endp, 10);
    double num = strtod(*strp, &endp);
    if (endp == *strp) {
      std::cerr << "Expected a number, but found " << *strp;
      return NULL;
    }
    *strp = endp;
    return new NumExpression(num);
  }
}
Expression * Function::parseOp(const char ** strp) {
  skipSpace(strp);
  // char op = **strp;
  std::string funcName = parseFuncName(strp);
  // functions in myFuncs
  if (myFuncs->count(funcName) > 0) {
    Function * TarFuncPointer = (*myFuncs)[funcName];  //???delete or not
    Expression * expr = parseArgs(strp, TarFuncPointer);
    delete TarFuncPointer;  //delete
    skipSpace(strp);
    if (**strp == ')') {
      *strp = *strp + 1;
      return expr;
    }
    else {
      std::cerr << "Expected ) but found " << *strp << "\n";
      std::cerr << "Defined function paresd failed.\n";
      delete expr;
      return NULL;
    }
  }
  //One argument
  else if (isValidSglArgFunc(funcName)) {
    Expression * arg = parse(strp);
    skipSpace(strp);
    if (**strp == ')') {
      *strp = *strp + 1;
      return makeSglExpr(funcName, arg);
    }
    std::cerr << "Expected ) but found " << *strp << "\n";
    delete arg;
    return NULL;
  }

  //two arguments
  else if (isValidDouFunc(funcName)) {
    Expression * lhs = parse(strp);
    if (lhs == NULL) {
      return NULL;
    }
    Expression * rhs = parse(strp);
    if (rhs == NULL) {
      delete lhs;
      return NULL;
    }
    skipSpace(strp);
    if (**strp == ')') {
      *strp = *strp + 1;
      return makeDouExpr(funcName, lhs, rhs);
    }
    std::cerr << "Expected ) but found " << *strp << "\n";
    delete lhs;
    delete rhs;
    return NULL;
  }
  else {
    std::cerr << "Invalid op: " << funcName << "\n";
    return NULL;
  }
}
std::string Function::parseFuncName(const char ** strp) {
  std::string funcName;
  skipSpace(strp);
  while (!isspace(**strp)) {
    funcName.append(1, **strp);
    *strp = *strp + 1;
  }
  return funcName;
}
bool Function::isValidSglArgFunc(std::string funcName) {
  if (funcName == "sin") {
    return true;
  }
  if (funcName == "cos") {
    return true;
  }
  if (funcName == "sqrt") {
    return true;
  }
  if (funcName == "ln") {
    return true;
  }
  return false;
}
bool Function::isValidDouFunc(std::string funcName) {
  if (strstr("+-*%/", funcName.c_str()) != NULL) {
    return true;
  }
  if (funcName == "pow") {
    return true;
  }
  return false;
}
Expression * Function::makeSglExpr(std::string funcName, Expression * arg) {
  if (funcName == "sin") {
    return new SglExpression(arg, funcName);
  }
  if (funcName == "cos") {
    return new SglExpression(arg, funcName);
  }
  if (funcName == "sqrt") {
    return new SglExpression(arg, funcName);
  }
  if (funcName == "ln") {
    return new SglExpression(arg, funcName);
  }
  std::cerr << "Impossible funcName: " << funcName << "\n";
  abort();
}
Expression * Function::makeDouExpr(std::string op, Expression * lhs, Expression * rhs) {
  if (op == "+") {
    return new PlusExpression(lhs, rhs);
  }
  if (op == "-") {
    return new MinusExpression(lhs, rhs);
  }
  if (op == "*") {
    return new TimesExpression(lhs, rhs);
  }
  if (op == "/") {
    return new DivExpression(lhs, rhs);
  }
  if (op == "%") {
    return new RemainderExpression(lhs, rhs);
  }
  if (op == "pow") {
    return new PowExpression(lhs, rhs);
  }
  std::cerr << "Impossible op char: " << op << "\n";
  abort();
}
Expression * Function::parseArgs(const char ** strp, Function * tarFunc) {
  skipSpace(strp);
  tarFunc->setViaPointer(strp);
  std::string setExpr = tarFunc->getEvalExpr();
  Expression * parsedFuncExpr;  //delete or not???
  const char * pointerToSetExpr = &setExpr[0];
  parsedFuncExpr = parse(&pointerToSetExpr);  //check succeeded or failed.
  if (parsedFuncExpr == NULL) {               //check parsed result
    std::cerr << "Cannot parse arguments.\n";
    exit(EXIT_FAILURE);
  }
  return parsedFuncExpr;
}
*/
