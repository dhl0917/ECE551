#ifndef FUNCTION_H
#define FUNCTION_H

#include <float.h>
#include <stdio.h>
#include <string.h>

#include <cstdlib>
#include <iostream>
#include <map>
#include <vector>

#include "parser.h"
#include "vector.h"
/*
Function class makes a good abstraction for functions. 

#name: Function name.
#defArgv: Arguements vector according to defination.
#defExpr: Function's expression according to defination(right side of the "=" sign).
#evalExpr: Function's expression used to replace alphabetic arguments with numeric
           parameters.
#myFuncs: A map * points to the map where we store all functions.*/

/*
______________________
Private member methods:

skipSpace(..): Skip space when needs.

dou2Str(..): Convert double to string.

_____________________
Public member methods:

constructor: Take four arguments to initialize the object.

setViaDou(..): Replace alphabetic arguments with numeric parameters via a vector 
               of double.

setViapointer(..): Replace alphabetic arguments with numeric parameters via a pointer
                   to a string a expression objects.

evaluate(): Evaluate the function value out.

gradient(..): Take a Vector and calculate the gradient of the function at this Vector.
              And return the gradient which is a Vector.*/

class Function
{
 private:
  std::string name;
  std::vector<std::string> defArgv;
  std::string defExpr;
  std::string evalExpr;
  std::map<std::string, Function *> * myFuncs;
  bool valid;
  void skipSpace(const char ** strp);
  std::string dou2str(double arg);

 public:
  Function(std::string funcName,
           std::vector<std::string> argv,
           std::string funcExpr,
           std::map<std::string, Function *> * myMap) :
      name(funcName),
      defArgv(argv),
      defExpr(funcExpr),
      myFuncs(myMap),
      valid(true) {
    demoTest();
  };
  void demoTest();
  std::string getEvalExpr() const { return evalExpr; }
  void setViaDou(std::vector<double> valVector);
  void setViaPointer(const char ** strp);
  double evaluate();
  std::string getName() const { return name; }
  std::vector<std::string> getArgs() { return defArgv; }
  bool isValid() { return valid; }
  Vector gradient(Vector v);
  ~Function(){};
};
#endif
