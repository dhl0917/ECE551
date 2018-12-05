#include "parser.h"

#include "function.h"
void Parser::skipSpace(const char ** strp) {
  while (isspace(**strp)) {
    *strp = *strp + 1;
  }
}

//CITE: Come from codes provided in assignment 083 but with pretty much modifications
Expression * Parser::parse(const char ** strp) {
  skipSpace(strp);
  if (**strp == '\0') {
    // End of line found mid expression
    return NULL;
  }
  else if (**strp == '(') {
    // (func Expression Expression)
    *strp = *strp + 1;
    return parseOp(strp);
  }
  else {
    //number
    char * endp;
    double num = strtod(*strp, &endp);
    if (endp == *strp) {
      std::cerr << "Unexpected: " << **strp << "\n";
      return NULL;
    }
    *strp = endp;
    return new NumExpression(num);
  }
}

//CITE: Come from codes provided in assignment 083 but with pretty much modifications
Expression * Parser::parseOp(const char ** strp) {
  skipSpace(strp);
  //extract funcName
  std::string funcName = parseFuncName(strp);

  //functions in myFuncs
  if (myFuncs->count(funcName) > 0) {
    Function * TarFuncPointer = (*myFuncs)[funcName];
    Expression * expr = parseArgs(strp, TarFuncPointer);
    if (expr == NULL) {  //Arguments parsed failed. Displayed in parseArgs(..).
      return expr;
    }
    skipSpace(strp);
    if (**strp == ')') {
      *strp = *strp + 1;
      return expr;
    }
    else {
      std::cerr << "Unexpected: " << **strp << "\n";
      std::cerr << "Defined function paresd failed.\n";
      delete expr;
      return NULL;
    }
  }

  //One argument Op
  else if (isValidSglArgFunc(funcName)) {
    Expression * arg = parse(strp);
    skipSpace(strp);
    if (**strp == ')') {
      *strp = *strp + 1;
      return makeSglExpr(funcName, arg);
    }
    std::cerr << "Unexpected: " << **strp << "\n";
    delete arg;
    return NULL;
  }

  //Two arguments Op
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
    std::cerr << "Unexpected: " << **strp << "\n";
    delete lhs;
    delete rhs;
    return NULL;
  }
  else {
    std::cerr << "Invalid function name.\n";
    return NULL;
  }
}
std::string Parser::parseFuncName(const char ** strp) {
  std::string funcName;
  skipSpace(strp);
  while (!isspace(**strp)) {
    funcName.append(1, **strp);
    *strp = *strp + 1;
  }
  return funcName;
}
bool Parser::isValidSglArgFunc(std::string funcName) {
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
bool Parser::isValidDouFunc(std::string funcName) {
  if (strstr("+-*%/", funcName.c_str()) != NULL) {
    return true;
  }
  if (funcName == "pow") {
    return true;
  }
  return false;
}
Expression * Parser::makeSglExpr(std::string funcName, Expression * arg) {
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
Expression * Parser::makeDouExpr(std::string op, Expression * lhs, Expression * rhs) {
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
Expression * Parser::parseArgs(const char ** strp, Function * tarFunc) {
  skipSpace(strp);
  tarFunc->setViaPointer(strp);
  std::string setExpr = tarFunc->getEvalExpr();
  Expression * parsedFuncExpr;
  const char * pointerToSetExpr = &setExpr[0];
  parsedFuncExpr = parse(&pointerToSetExpr);  //check succeeded or failed.
  if (parsedFuncExpr == NULL) {               //check parsed result
    std::cerr << "Cannot parse arguments.\n";
  }
  return parsedFuncExpr;
}
Function * Parser::parseDef(const char ** defineExpr) {
  skipSpace(defineExpr);
  if (**defineExpr == '\0') {
    std::cerr << "End of line found in the expression! Please try again.\n";
    return NULL;  //return NULL when failed.
  }
  else if (**defineExpr == '(') {
    *defineExpr = *defineExpr + 1;
    std::string defFuncName = parseFuncName(defineExpr);
    if (defFuncName.size() == 0) {
      //Invalid function name
      return NULL;
    }
    std::vector<std::string> defFuncArgs = parseFuncArgs(defineExpr);
    if (defFuncArgs.size() == 0) {
      //Invalid function args
      return NULL;
    }
    *defineExpr = *defineExpr + 1;  //skip ')'
    std::string defFuncExpr = parseFuncExpr(defineExpr);
    if (defFuncExpr.size() == 0) {
      //Invalid function expression
      return NULL;
    }
    //try to insert to myFuncs
    if (myFuncs->count(defFuncName) > 0) {
      std::cerr << "Already defined!\n";
      return NULL;
    }
    else {
      Function * myFunc = new Function(defFuncName, defFuncArgs, defFuncExpr, myFuncs);
      if (myFunc->isValid()) {
        return myFunc;
      }
      else {
        delete myFunc;
        return NULL;
      }
    }
  }
  else {
    std::cerr << "Invalid defination syntax!\n";
    return NULL;
  }
}
std::vector<std::string> Parser::parseFuncArgs(const char ** defineExpr) {
  std::vector<std::string> argv;
  skipSpace(defineExpr);
  while (**defineExpr != ')') {
    std::string temp;
    while (isalpha(**defineExpr)) {
      temp.append(1, **defineExpr);
      *defineExpr = *defineExpr + 1;
    }
    argv.push_back(temp);
    if (isspace(**defineExpr)) {
      skipSpace(defineExpr);
    }
    else if (**defineExpr == ')') {
      break;
    }
    else {
      std::cerr << "Invalid arguments!\n";
      argv.clear();
      return argv;
    }
  }
  if (argv.size() == 0) {
    std::cerr << "No arguments!\n";
  }
  return argv;
}
std::string Parser::parseFuncExpr(const char ** defineExpr) {
  std::string funcExpr;
  skipSpace(defineExpr);
  if (**defineExpr != '=') {
    std::cerr << "Found no function expression.\n";
    return funcExpr;
  }
  *defineExpr = *defineExpr + 1;
  funcExpr = *defineExpr;
  return funcExpr;
}
std::string Parser::getPrintFuncName(const char ** strp) {
  std::string printName;
  skipSpace(strp);
  if (**strp == '(') {
    //skip '('
    *strp = *strp + 1;
    while (!isspace(**strp)) {
      printName.append(1, **strp);
      *strp = *strp + 1;
    }
  }
  return printName;
}
void Parser::printArgs(const char ** strp, std::string funcName) {
  skipSpace(strp);
  const char * temp = *strp;
  size_t n;
  if (myFuncs->count(funcName) > 0) {
    Function * funcPtr = (*myFuncs)[funcName];
    std::vector<std::string> defArgv = funcPtr->getArgs();
    n = defArgv.size();
  }
  else if (isValidSglArgFunc(funcName)) {
    n = 1;
  }
  else if (isValidDouFunc(funcName)) {
    n = 2;
  }
  else {
    std::cerr << "Invalid funcname.\n";
    return;
  }
  skipSpace(strp);
  for (size_t i = 0; i < n; i++) {
    Expression * arg = parse(strp);
    delete arg;
  }
  while (temp != *strp) {
    std::cout << *temp;
    temp++;
  }
}
