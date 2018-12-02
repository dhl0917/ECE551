#include "calculator.h"

#include <iostream>

void Calculator::run() {
  char * line = NULL;
  size_t sz;
  while (getline(&line, &sz, stdin) != -1) {
    const char * temp = line;
    const char * printPtr = line;

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
      myNuminter.integrate();
      /*
      double numintAns = myNuminter.integrate();
      std::cout.precision(13);  //display
      std::cout << numintAns << "\n";
      */
    }
    //mcint
    else if (std::string(line).find("mcint") == 0) {
      Mcinter myMcinter(&temp, myFuncs);
      myMcinter.integrate();
      /*
      double mcintAns = myMcinter.integrate();
      std::cout.precision(13);  //display
      std::cout << mcintAns << "\n";
      */
    }
    //max
    else if (std::string(line).find("max") == 0) {
      Extremer myMaxer(&temp, myFuncs);
      myMaxer.getMaximum();
      // double max = myMaxer.getMaximum();
      /*
      if (max != DBL_MIN) {
        std::cout.precision(13);  // display;
        if (abs(max) < 1) {
          std::cout.setf(std::ios::fixed, std::ios::floatfield);
          std::cout << max << "\n";
          std::cout.unsetf(std::ios::fixed);
        }
        else {
          std::cout << max << "\n";
        }
      }
      */
    }
    //min
    else if (std::string(line).find("min") == 0) {
      Extremer myMiner(&temp, myFuncs);
      myMiner.getMinimum();
      //     double min = myMiner.getMinimum();
      /*
      if (min != DBL_MIN) {
        std::cout.precision(13);  // display;
        if (abs(min) < 1) {
          std::cout.setf(std::ios::fixed, std::ios::floatfield);
          std::cout << min << "\n";
          std::cout.unsetf(std::ios::fixed);
        }
        else {
          std::cout << min << "\n";
        }
      }
      */
    }
    //No key words.
    else {
      std::cerr << "No valid key word.\n";
    }
  }
  free(line);
}
