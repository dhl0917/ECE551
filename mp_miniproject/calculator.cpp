#include "calculator.h"

#include <iostream>

void Calculator::run() {
  char * line = NULL;
  size_t sz;
  while (getline(&line, &sz, stdin) != -1) {
    const char * temp = line;
    const char * printPtr = line;
    //Not write printPointer here now

    //DEFINE
    if (std::string(line).find("define") == 0) {
      Definer myDefiner(&temp, myFuncs);
      if (!myDefiner.define()) {
        std::cerr << "Define failed.\n";
      }
    }

    //TEST
    else if (std::string(line).find("test") == 0) {
      Tester myTester(&temp, &printPtr, myFuncs);
      myTester.test();
    }

    //numint
    //remember to check exceptions
    else if (std::string(line).find("numint") == 0) {
      Numinter myNuminter(&temp, myFuncs);
      double numintAns = myNuminter.integrate();
      std::cout.precision(13);  //display
      std::cout << numintAns << "\n";
    }
    else if (std::string(line).find("mcint") == 0) {
      Mcinter myMcinter(&temp, myFuncs);
      double mcintAns = myMcinter.integrate();
      std::cout.precision(13);  //display
      std::cout << mcintAns << "\n";
    }
    else {
      std::cerr << "No valid key word.\n";
    }
  }
  free(line);
}
