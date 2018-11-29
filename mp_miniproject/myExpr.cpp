#include "myExpr.h"

#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include <cstdlib>
#include <iostream>
#include <map>
#include <vector>

Expression * parse(
    const char ** strp,
    std::map<std::string, std::pair<std::vector<std::string>, std::string> > & myFuncs);

std::string dou2str(double arg) {
  std::stringstream strStream;
  std::string myStr;
  strStream << arg;
  strStream >> myStr;
  return myStr;
}

std::ostream & operator<<(std::ostream & s, std::vector<std::string> & v) {
  std::vector<std::string>::const_iterator it = v.begin();
  for (it = v.begin(); it != v.end() - 1; ++it) {
    s << *it << " ";
  }
  s << *it;
  return s;
}
std::ostream & operator<<(std::ostream & s, std::vector<double> & v) {
  std::vector<double>::const_iterator it = v.begin();
  s << *it;
  for (it = v.begin() + 1; it != v.end(); ++it) {
    s << " " << *it;
  }
  return s;
}
void printDefFunc(
    std::string defFuncName,
    std::map<std::string, std::pair<std::vector<std::string>, std::string> > & myFuncs) {
  if (myFuncs.count(defFuncName) > 0) {
    std::cout << "defined " << defFuncName << "(" << myFuncs[defFuncName].first << ")\n";
  }
}
void skipSpace(const char ** strp) {
  while (isspace(**strp)) {
    *strp = *strp + 1;
  }
}
Expression * makeDouExpr(std::string op, Expression * lhs, Expression * rhs) {
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
Expression * makeSglExpr(std::string funcName, Expression * arg) {
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

std::string getPrintFuncName(const char ** strp) {
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
std::string parseFuncName(const char ** strp) {
  std::string funcName;
  skipSpace(strp);
  while (!isspace(**strp)) {
    funcName.append(1, **strp);
    *strp = *strp + 1;
  }
  return funcName;
  /*
  while (!isspace(**defineExpr)) {
    if (isalpha(**defineExpr) || **defineExpr == '+' || **defineExpr == '+' ||
        **defineExpr == '+' || **defineExpr == '+' || **defineExpr == '+') {
      funcName.append(1, **defineExpr);
      *defineExpr = *defineExpr + 1;
    }
    else {
      //invalid function name, return empty string
      std::cerr << "Invalid function name!\n";
      funcName.erase(funcName.begin(), funcName.end());
      return funcName;
    }
  }
  return funcName;
  */
}
/*
bool isValidOp(char c) {
  return strchr("+-*%/", c) != NULL;
}
*/

bool isValidSglArgFunc(std::string funcName) {
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
bool isValidDouFunc(std::string funcName) {
  if (strstr("+-*%/", funcName.c_str()) != NULL) {
    return true;
  }
  if (funcName == "pow") {
    return true;
  }
  /*
  if (myFuncs.count(funcName) > 0) {
    return true;
  }
  */
  return false;
}
void printArgs(const char ** strp,
               std::string funcName,
               std::map<std::string, std::pair<std::vector<std::string>, std::string> > & myFuncs) {
  skipSpace(strp);
  const char * temp = *strp;
  size_t n;
  if (myFuncs.count(funcName)) {
    std::vector<std::string> defArgv = myFuncs[funcName].first;
    //  std::string expr = myFuncs[funcName].second;
    // std::vector<double> testArgv;
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
    exit(EXIT_FAILURE);
  }
  skipSpace(strp);
  for (size_t i = 0; i < n; i++) {
    Expression * arg = parse(strp, myFuncs);
    // testArgv.push_back(arg->evaluate());
    delete arg;
  }
  while (temp != *strp) {
    std::cout << *temp;
    temp++;
  }
}
Expression * parseArgs(
    const char ** strp,
    std::string funcName,
    std::map<std::string, std::pair<std::vector<std::string>, std::string> > & myFuncs) {
  std::vector<std::string> defArgv = myFuncs[funcName].first;
  std::string expr = myFuncs[funcName].second;
  std::vector<double> testArgv;
  skipSpace(strp);
  size_t n = defArgv.size();
  for (size_t i = 0; i < n; i++) {
    Expression * arg = parse(strp, myFuncs);
    //try
    //  std::cout << (arg->toString());
    testArgv.push_back(arg->evaluate());
    delete arg;
  }

  for (size_t i = 0; i < defArgv.size(); i++) {
    int pos = expr.find(defArgv[i]);
    while (pos != -1) {
      expr.replace(pos, defArgv[i].length(), dou2str(testArgv[i]));
      pos = expr.find(defArgv[i]);
    }
  }
  const char * pointerToExpr = &expr[0];
  Expression * parsedExpr = parse(&pointerToExpr, myFuncs);
  Expression * checkItsBack = parse(&pointerToExpr, myFuncs);
  if (checkItsBack == NULL) {
    delete checkItsBack;
    return parsedExpr;
  }
  else {
    std::cerr << "More than one expressions!\n";
    delete checkItsBack;
    delete parsedExpr;
    return NULL;
  }
}

Expression * parseOp(
    const char ** strp,
    std::map<std::string, std::pair<std::vector<std::string>, std::string> > & myFuncs) {
  skipSpace(strp);
  // char op = **strp;
  std::string funcName = parseFuncName(strp);
  // functions in myFuncs
  if (myFuncs.count(funcName) > 0) {
    Expression * expr = parseArgs(strp, funcName, myFuncs);
    skipSpace(strp);
    if (**strp == ')') {
      *strp = *strp + 1;
      return expr;
      /*
      Expression * checkItsBack = parse(strp, myFuncs);
      if (checkItsBack == NULL) {
        delete checkItsBack;
        return expr;
      }
      else {
        std::cerr << "Illegal! More than one expression detected!\n";
        delete checkItsBack;
        delete expr;
        return NULL;
      }
      */
    }
    else {
      std::cerr << "Expected ) but found " << *strp << "\n";
      std::cerr << "Defined function paresd failed.\n";
      delete expr;
      return NULL;
    }
  }
  //functions not in myFuncs
  // if (!isValidOp(op)) {
  /*
  else if (!isValidFunc(funcName)) {
    std::cerr << "Invalid op: " << funcName << "\n";
    return NULL;
  }
  */
  // *strp = *strp + 1;

  //one argument
  else if (isValidSglArgFunc(funcName)) {
    Expression * arg = parse(strp, myFuncs);
    skipSpace(strp);
    if (**strp == ')') {
      *strp = *strp + 1;
      //try
      return makeSglExpr(funcName, arg);

      // Expression * checkItsBack = parse(strp, myFuncs);
    }
    std::cerr << "Expected ) but found " << *strp << "\n";
    delete arg;
    return NULL;
  }

  //two arguments
  else if (isValidDouFunc(funcName)) {
    Expression * lhs = parse(strp, myFuncs);
    if (lhs == NULL) {
      return NULL;
    }
    Expression * rhs = parse(strp, myFuncs);
    if (rhs == NULL) {
      delete lhs;
      return NULL;
    }
    skipSpace(strp);
    if (**strp == ')') {
      *strp = *strp + 1;
      return makeDouExpr(funcName, lhs, rhs);
      //      Expression * checkItsBack = parse(strp, myFuncs);
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
/*
double calculator(
    std::vector<std::string> defArgv,
    std::vector<double> testArgv,
    std::string expr,
    std::map<std::string, std::pair<std::vector<std::string>, std::string> > & myFuncs) {
  for (size_t i = 0; i < defArgv.size(); i++) {
    int pos = expr.find(defArgv[i]);
    while (pos != -1) {
      expr.replace(pos, defArgv[i].length(), dou2str(testArgv[i]));
      pos = expr.find(defArgv[i]);
    }
  }
  const char * pointerToExpr = &expr[0];
  Expression * parsedExpr = parse(&pointerToExpr, myFuncs);
  Expression * checkItsBack = parse(&pointerToExpr, myFuncs);
  if (checkItsBack == NULL) {
    delete checkItsBack;
    return parsedExpr->evaluate();
  }
  else {
    std::cerr << "More than one expressions!\n";
    delete checkItsBack;
    delete parsedExpr;
    exit(EXIT_FAILURE);
  }
}
*/
Expression * parse(
    const char ** strp,
    std::map<std::string, std::pair<std::vector<std::string>, std::string> > & myFuncs) {
  skipSpace(strp);
  if (**strp == '\0') {
    // std::cerr << "End of line found mid expression!\n";
    return NULL;
  }
  else if (**strp == '(') {
    // (op E E)
    *strp = *strp + 1;
    return parseOp(strp, myFuncs);
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
std::vector<std::string> parseFuncArgs(const char ** defineExpr) {
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
      // argv.push_back(temp);
      skipSpace(defineExpr);
      //      *defineExpr = *defineExpr + 1;
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
std::string parseFuncExpr(const char ** defineExpr) {
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
double getDou(const char ** strp) {
  char * endp;
  double ans = strtod(*strp, &endp);
  if (endp == *strp) {
    std::cerr << "Expected a number, but found " << *strp;
    exit(EXIT_FAILURE);
  }
  *strp = endp;
  return ans;
}
/*
std::vector<double> dfs(int pos,
                        std::vector<std::pair<double, double> > & ranges,
                        double step,
                        std::vector<double> & res) {
  if (pos == ranges.size()) {
  }
}
*/
/*
void parseNumInt(
    const char ** strp,
    std::map<std::string, std::pair<std::vector<std::string>, std::string> > & myFuncs) {
  std::string funcName = parseFuncName(strp);
  std::vector<std::string> defArgv = myFuncs[funcName].first;
  std::string expr = myFuncs[funcName].second;
  std::vector<std::pair<double, double> > ranges;
  //skipSpace(strp);
  std::vector<double> res;
  res.resize(defArgv.size());
  double step = getDou(strp);
  for (size_t i = 0; i < defArgv.size(); ++i) {
    double low = getDou(strp);
    double high = getDou(strp);
    ranges.push_back(std::pair<double, double>(low, high));
  }
}
*/
void parseDefine(
    const char ** defineExpr,
    std::map<std::string, std::pair<std::vector<std::string>, std::string> > & myFuncs) {
  skipSpace(defineExpr);
  if (**defineExpr == '\0') {
    std::cerr << "End of line found in the expression! Please try again.\n";
    return;
  }
  else if (**defineExpr == '(') {
    *defineExpr = *defineExpr + 1;
    std::string defFuncName = parseFuncName(defineExpr);
    if (defFuncName.size() == 0) {
      //Invalid function name
      return;
    }
    std::vector<std::string> defFuncArgs = parseFuncArgs(defineExpr);
    if (defFuncArgs.size() == 0) {
      //Invalid function args
      return;
    }
    *defineExpr = *defineExpr + 1;  //skip ')'
    std::string defFuncExpr = parseFuncExpr(defineExpr);
    if (defFuncExpr.size() == 0) {
      //Invalid function expression
      return;
    }
    //try to insert to myFuncs
    if (myFuncs.count(defFuncName) > 0) {
      std::cerr << "Already defined!\n";
      return;
    }
    else {
      std::pair<std::vector<std::string>, std::string> mypair(defFuncArgs, defFuncExpr);

      // myFuncs.insert({defFuncName, mypair});
      myFuncs.insert(std::pair<std::string, std::pair<std::vector<std::string>, std::string> >(
          defFuncName, mypair));
      printDefFunc(defFuncName, myFuncs);
    }
  }
  else {
    std::cerr << "Invalid defination syntax!\n";
    return;
  }
}
int main(void) {
  char * line = NULL;
  size_t sz;
  std::map<std::string, std::pair<std::vector<std::string>, std::string> > myFuncs;
  while (getline(&line, &sz, stdin) != -1) {
    const char * temp = line;
    const char * printPointer = line;
    std::cout << "Read expression: " << line;
    //find key words first
    //try to find valid key word--define
    if (std::string(line).find("define") == 0) {
      //valid define found, then parse it
      //skip "define" first
      // *defineExpr = *defineExpr + 6;
      temp = temp + 6;
      parseDefine(&temp, myFuncs);
    }
    else if (std::string(line).find("test") == 0) {
      //skip "test"
      temp = temp + 4;
      printPointer = printPointer + 4;
      Expression * expr = parse(&temp, myFuncs);
      if (expr == NULL) {
        std::cout << "Could not parse the expression of the function, please try again.\n";
        delete expr;
        continue;
      }
      Expression * ans = parse(&temp, myFuncs);
      if (ans == NULL) {
        std::cout << "Could not parse the expression of the answer, please try again.\n";
        delete expr;
        delete ans;
        continue;
      }
      Expression * extra = parse(&temp, myFuncs);
      if (extra != NULL) {
        std::cout << "More than one answer.\n";
        delete expr;
        delete ans;
        delete extra;
        continue;
      }
      else {
        delete extra;
      }
      std::string testFuncName = getPrintFuncName(&printPointer);
      /*
      std::cout << "-------\n"
                << *printPointer << "\n"
                << "------"
                << "\n";
      */
      if (testFuncName.size() == 0) {
        if (std::abs(expr->evaluate() - ans->evaluate()) < 0.0000000000001) {
          std::cout << expr->toString() << " = " << ans->evaluate() << " [CORRECT]\n";
        }
        else {
          std::cout << expr->toString() << " = " << ans->evaluate()
                    << " [INCORRECT: expected: " << expr->evaluate() << "]\n";
        }
      }
      else {
        if (std::abs(expr->evaluate() - ans->evaluate()) < 0.000001) {
          std::cout << testFuncName << "(";
          printArgs(&printPointer, testFuncName, myFuncs);
          std::cout << ")"
                    << " = " << ans->evaluate() << " [CORRECT]\n";
        }
        else {
          std::cout << "(" << testFuncName;
          printArgs(&printPointer, testFuncName, myFuncs);
          std::cout << ")"
                    << " = " << ans->evaluate() << " [INCORRECT: expected: " << expr->evaluate()
                    << "]\n";
        }
      }

      delete expr;
      delete ans;
      /*
      if (ans != NULL) {
        std::cout << "Parsed expression to: " << ans->toString() << "\n";
        std::cout << "Evaluated expression to: " << ans->evaluate() << "\n";

        delete ans;
      }
      else {
        std::cout << "Could not parse expression, please try again.\n";
      }
      */
    }
    else {
      std::cout << "No key words. Try again please.\n";
    }
  }

  free(line);
  return EXIT_SUCCESS;
}
