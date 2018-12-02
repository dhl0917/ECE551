#include <stdio.h>

#include <cstdlib>

#include "calculator.h"
#include "function.h"
#include "vector.h"
int main() {
  Calculator myCalculator;

  myCalculator.run();
  return EXIT_SUCCESS;

  /*
  std::map<std::string, Function *> myFuncs;
  std::vector<std::string> argv;
  argv.push_back("x");
  //  argv.push_back("y");
  Function f("f", argv, " x  ", &myFuncs);
  std::pair<std::string, Function *> mypair("f", &f);
  myFuncs.insert(mypair);
  // Function g("g", argv, "(f x (sin y))", &myFuncs);
  std::vector<double> testArgs;
  testArgs.push_back(1000);
  //  testArgs.push_back(3);
  //  std::string args("1 2");
  // const char * p = &args[0];
  f.setViaDou(testArgs);
  double ans = f.evaluate();
  std::cout << "value:" << ans << "\n";
  f.setViaDou(testArgs);
  ans = f.gradient(Vector(testArgs)).getCoords()[0];
  std::cout << "gradient:" << ans << "\n";
  //  f.setViaPointer(&p);
  //  f.setViaDou(testArgs);
  //  ans = f.evaluate();
  //  std::cout << ans << "\n";

  // g.setViaDou(testArgs);
  // ans = g.evaluate();
  // std::cout << ans << "\n";
  */
}
