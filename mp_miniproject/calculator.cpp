#include "calculator.h"

#include <iostream>

bool Calculator::run() {
  char * line = NULL;
  size_t sz;
  //read line from stdin
  while (getline(&line, &sz, stdin) != -1) {
    const char * temp = line;      //temp used to parse
    const char * printPtr = line;  //printPtr used to print when test

    //DEFINE
    if (std::string(line).find("define") == 0) {
      Definer myDefiner(&temp, myFuncs);
      if (!myDefiner.define()) {
        std::cerr << "Define failed.\n";
        free(line);
        return false;
      }
    }

    //TEST
    else if (std::string(line).find("test") == 0) {
      Tester myTester(&temp, &printPtr, myFuncs);
      if (!myTester.test()) {
        std::cerr << "Test failed.\n";
        free(line);
        return false;
      }
    }

    //numint
    //remember to check exceptions
    else if (std::string(line).find("numint") == 0) {
      Numinter myNuminter(&temp, myFuncs);
      if (!myNuminter.integrate()) {
        std::cerr << "numint failed.\n";
        free(line);
        return false;
      }
    }
    //mcint
    else if (std::string(line).find("mcint") == 0) {
      Mcinter myMcinter(&temp, myFuncs);
      if (!myMcinter.integrate()) {
        std::cerr << "mcint failed.\n";
        free(line);
        return false;
      }
    }
    //max
    else if (std::string(line).find("max") == 0) {
      Extremer myMaxer(&temp, myFuncs);
      if (!myMaxer.getMaximum()) {
        std::cerr << "Find maximum failed.\n";
        free(line);
        return false;
      }
    }
    //min
    else if (std::string(line).find("min") == 0) {
      Extremer myMiner(&temp, myFuncs);
      if (!myMiner.getMinimum()) {
        std::cerr << "Find minimum failed.\n";
        free(line);
        return false;
      }
    }
    //No key words.
    else {
      std::cerr << "No valid key word.\n";
      free(line);
      return false;
    }
  }
  free(line);
  return true;
}
