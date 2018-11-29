#include <stdio.h>

#include <cstdlib>

#include "calculator.h"
#include "function.h"

int main() {
  Calculator myCalculator;

  myCalculator.run();
  return EXIT_SUCCESS;

  /*
  std::map<std::string, Function *> myFuncs;
  std::vector<std::string> argv;
  argv.push_back("x");
  argv.push_back("y");
  Function f("f", argv, "(+ x y)", &myFuncs);
  std::pair<std::string, Function *> mypair("f", &f);
  myFuncs.insert(mypair);
  Function g("g", argv, "(f x (sin y))", &myFuncs);
  std::vector<double> testArgs;
  testArgs.push_back(2);
  testArgs.push_back(3);
  std::string args("1 2");
  const char * p = &args[0];
  f.setViaPointer(&p);
  double ans = f.evaluate();
  f.setViaDou(testArgs);
  ans = f.evaluate();
  std::cout << ans << "\n";
  //  f.setViaPointer(&p);
  f.setViaDou(testArgs);
  ans = f.evaluate();
  std::cout << ans << "\n";

  g.setViaDou(testArgs);
  ans = g.evaluate();
  std::cout << ans << "\n";
  */
}
