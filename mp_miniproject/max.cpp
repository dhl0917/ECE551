#include "maxer.h"

void Maxer::initialize() {
  Parser myParser(myFuncs);
  std::string funcName = myParser.parseFuncName(expr);
  func = (*myFuncs)[funcName];
  Expression * myGamma = myParser.parse(expr);
  gamma = myGamma->evaluate();
  delete myGamma;
  Expression * myCoverDist = myParser.parse(expr);
  convergedDistance = myCoverDist->evaluate();
  delete myCoverDist;

  std::vector<double> temp;
  for (size_t i = 0; i < func->getArgs().size(); ++i) {  //what if not enough
    Expression * coord = myParser.parse(expr);           //check result???
    temp.push_back(coord->evaluate());
    delete coord;
  }
  startPoint = Vector(temp);
  Expression * myTrials = myParser.parse(expr);
  trials = myTrials->evaluate();
  delete myTrials;  //what if more arguments???
}
double Maxer::getMaximum() {
  int times = 0;
  Vector newPoint = func->gradient(startPoint) + startPoint * gamma;
  times += 1;
  while (startPoint.calDist(newPoint) > convergedDistance && times < trials) {
    startPoint = newPoint;
    newPoint = func->gradient(startPoint) + startPoint * gamma;
  }
  if (times >= trials) {
    std::cout << "Alread reach giving up number of trials. Did not find.\n";
    return DBL_MIN;
  }
  if (startPoint.calDist(newPoint) <= convergedDistance) {
    func->setViaDou(startPoint.getCoords());
    return func->evaluate();
  }
  std::cerr << "Ops, here comes the accident!.\n";
  return DBL_MIN;
}
