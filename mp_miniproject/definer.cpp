#include "definer.h"

bool Definer::define() {
  //skip "define"
  *defineExpr = *defineExpr + 6;
  //parse the input to a function *
  Parser myParser(myFuncs);
  Function * myFuncPointer = myParser.parseDef(defineExpr);
  if (myFuncPointer == NULL) {
    //then what?
    return false;
  }
  else {
    //insert the function name and its function * to the map
    std::pair<std::string, Function *> myPair(myFuncPointer->getName(), myFuncPointer);
    (*myFuncs).insert(myPair);
    if ((*myFuncs).count(myFuncPointer->getName()) > 0) {  //check if insert succeeded
      print(myFuncPointer);
      return true;
    }
    else {
      std::cerr << "Insert failed.\n";
      delete myFuncPointer;
      return false;
    }
  }
}
void Definer::print(Function * myFuncPter) {
  std::vector<std::string> args = myFuncPter->getArgs();
  std::cout << "defined " << myFuncPter->getName() << "(" << args << ")\n";
}
std::ostream & operator<<(std::ostream & s, std::vector<std::string> & v) {
  std::vector<std::string>::const_iterator it = v.begin();
  for (it = v.begin(); it != v.end() - 1; ++it) {
    s << *it << " ";
  }
  s << *it;
  return s;
}
