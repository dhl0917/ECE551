#include <ctype.h>
#include <float.h>
#include <math.h>
#include <stdio.h>

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "expr.cpp"

int isPreDef(std::string funcName) {
  std::vector<std::string> target(5);
  target[0] = "sin";
  target[1] = "cos";
  target[2] = "sqrt";
  target[3] = "ln";
  target[4] = "pow";
  for (int i = 0; i < 5; i++) {
    if (funcName == target[i]) {
      return i;
    }
  }
  return -1;
}
double getPreDefExpr(std::string funcName, std::vector<double> argv) {
  int key = isPreDef(funcName);
  switch (key) {
    case 0:
      return sin(argv[0]);
    case 1:
      return cos(argv[0]);
    case 2:
      return sqrt(argv[0]);
    case 3:
      return log(argv[0]);
    case 4:
      return pow(argv[0], argv[1]);
  }
  return DBL_MIN;
}

void preDefine(std::map<std::string, std::pair<std::vector<std::string>, std::string> > & myFuncs) {
  std::vector<std::string> argv(1);
  //sin(x)
  argv[0] = "x";
  std::pair<std::vector<std::string>, std::string> mypair(argv, "sin(x)");
  // myFuncs.insert({defFuncName, mypair});
  myFuncs.insert(
      std::pair<std::string, std::pair<std::vector<std::string>, std::string> >("sin", mypair));
  //cos(x)
  mypair.second = "cos(x)";
  myFuncs.insert(
      std::pair<std::string, std::pair<std::vector<std::string>, std::string> >("cox", mypair));
  //sqrt(x)
  mypair.second = "sqrt(x)";
  myFuncs.insert(
      std::pair<std::string, std::pair<std::vector<std::string>, std::string> >("sqrt", mypair));
  //ln(x)
  mypair.second = "ln(x)";
  myFuncs.insert(
      std::pair<std::string, std::pair<std::vector<std::string>, std::string> >("ln", mypair));
  //pow(x,y)
  mypair.second = "pow(x,y)";
  std::vector<std::string> argvPow(2);
  mypair.first = argvPow;
  myFuncs.insert(
      std::pair<std::string, std::pair<std::vector<std::string>, std::string> >("pow", mypair));
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
double calAns(const char * temp) {
  //const char * temp = line;
  //std::cout << "Read expression: " << line;
  Expression * expr = parse(&temp);
  if (expr != NULL) {
    std::cout << "Parsed expression to: " << expr->toString() << "\n";
    std::cout << "Evaluated expression to: " << expr->evaluate() << "\n";
    return expr->evaluate();
    delete expr;
  }
  else {
    std::cout << "Could not parse expression, please try again.\n";
    return DBL_MIN;
  }

  //free(line);
  //return EXIT_SUCCESS;
}
/*
void skipSpace(const char ** expression) {
  while (isspace(**expression)) {
    *expression = *expression + 1;
  }
}
*/
std::string parseFuncName(const char ** defineExpr) {
  std::string funcName;
  skipSpace(defineExpr);
  while (!isspace(**defineExpr)) {
    if (isalpha(**defineExpr)) {
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
std::vector<double> parseTestArgs(const char ** testExpr) {
  std::vector<double> argv;
  try {
    skipSpace(testExpr);
    std::string::size_type sz;
    while (**testExpr != ')') {
      double temp = std::stod(*testExpr, &sz);
      argv.push_back(temp);
      *testExpr = *testExpr + sz;
      skipSpace(testExpr);
    }
    return argv;
  }
  catch (std::invalid_argument & e) {
    std::cerr << "Invalid arguments!\n";
    argv.clear();
    return argv;
  }
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
double parseTestAns(const char ** testExpr) {
  skipSpace(testExpr);
  try {
    std::string::size_type sz;
    double temp = std::stod(*testExpr, &sz);
    *testExpr = *testExpr + sz;
    skipSpace(testExpr);
    if (**testExpr == '\0') {
      return temp;
    }
    else {
      std::cerr << "More than one answer!\n";
      return DBL_MIN;
    }
  }
  catch (std::invalid_argument & e) {
    std::cerr << "Invalid answer!\n";
    return DBL_MIN;
  }
}

void printDefFunc(
    std::string defFuncName,
    std::map<std::string, std::pair<std::vector<std::string>, std::string> > & myFuncs) {
  if (myFuncs.count(defFuncName) > 0) {
    std::cout << "defined " << defFuncName << "(" << myFuncs[defFuncName].first << ")\n";
  }
}
void parseDefine(
    const char ** defineExpr,
    std::map<std::string, std::pair<std::vector<std::string>, std::string> > & myFuncs) {
  //skip "define" first
  *defineExpr = *defineExpr + 6;
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
std::string buildExpr(
    std::string testName,
    std::vector<double> testArgv,
    std::map<std::string, std::pair<std::vector<std::string>, std::string> > & myFuncs) {
  std::vector<std::string> funcArgv = myFuncs[testName].first;
  std::string expr = myFuncs[testName].second;
  if (isPreDef(testName) != -1) {
    double ans = getPreDefExpr(testName, testArgv);
    if (ans == DBL_MIN) {
      //need exit or return???
      std::cerr << "Cannot calculate by default definations!\n";
      exit(EXIT_FAILURE);
    }
    else {
      return std::to_string(ans);
    }
  }
  else {
    for (size_t i = 0; i < funcArgv.size(); i++) {
      int pos = expr.find(funcArgv[i]);
      while (pos != -1) {
        expr.replace(pos, funcArgv[i].length(), std::to_string(testArgv[i]));
        pos = expr.find(funcArgv[i]);
      }
    }
    return expr;
  }
  //  return expr;
}

void parseTest(const char ** testExpr,
               std::map<std::string, std::pair<std::vector<std::string>, std::string> > & myFuncs) {
  //skip "test" first
  *testExpr = *testExpr + 4;
  skipSpace(testExpr);
  if (**testExpr == '\0') {
    std::cerr << "End of line found in the expression! Please try again.\n";
    exit(EXIT_FAILURE);
    // return;
  }
  else if (**testExpr == '(') {
    *testExpr = *testExpr + 1;
    std::string testFuncName = parseFuncName(testExpr);
    if (myFuncs.count(testFuncName) <= 0) {
      std::cout << "Undefined function!\n";
      exit(EXIT_FAILURE);
      // return;
    }
    //begin
    skipSpace(testExpr);
    if (**testExpr == '(') {
    }
    //end
    if (testFuncName.size() == 0) {
      std::cout << "Invalid test function name!\n";
      exit(EXIT_FAILURE);
      // return;
    }
    std::vector<double> testFuncArgs = parseTestArgs(testExpr);
    if (testFuncArgs.size() == 0) {
      exit(EXIT_FAILURE);
      // return;
    }
    *testExpr = *testExpr + 1;  //skip ')'
    double testFuncAns = parseTestAns(testExpr);
    if (testFuncAns == DBL_MIN) {
      exit(EXIT_FAILURE);
      // return;
    }
    std::string resultExpr = buildExpr(testFuncName, testFuncArgs, myFuncs);
    //    std::cout << resultExpr;
    double realAns = calAns(resultExpr.c_str());
    // std::cout << realAns;

    if (std::abs(testFuncAns - realAns) > 0.00001) {
      std::cout << "(" << testFuncName << " " << testFuncArgs << ")"
                << " = " << testFuncAns << " [INCORRECT: expected: " << realAns << "]\n";
    }
    else {
      std::cout << testFuncName << "(" << testFuncArgs << ")"
                << " = " << testFuncAns << " [CORRECT]\n";
    }
  }
  else {
    std::cerr << "Invalid test syntax!\n";
    return;
  }
}

int main(void) {
  char * line = NULL;
  size_t sz;
  std::map<std::string, std::pair<std::vector<std::string>, std::string> > myFuncs;
  preDefine(myFuncs);
  while (getline(&line, &sz, stdin) != -1) {
    const char * temp = line;
    //find key words first
    //try to find valid key word--define
    if (std::string(line).find("define") == 0) {
      //valid define found, then parse it
      parseDefine(&temp, myFuncs);
    }
    //try to find valid key word--test
    else if (std::string(line).find("test") == 0) {
      //valid test found, then parse it
      parseTest(&temp, myFuncs);
    }
    //no valid key words found
    else {
      std::cerr << "No valid key words! Please try again.\n";
    }
  }
  free(line);
  return EXIT_SUCCESS;
}