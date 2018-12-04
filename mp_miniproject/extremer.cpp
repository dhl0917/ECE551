#include "extremer.h"

void Extremer::initialize() {
  //parse expr to get necessary information of the fucntion and requist
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
void Extremer::getMaximum() {
  int times = 0;
  //calculate the next point
  Vector newPoint = startPoint + func->gradient(startPoint) * gamma;
  times += 1;
  while (startPoint.calDist(newPoint) > convergedDistance && times < trials) {
    //update current point and the next point
    startPoint = newPoint;
    newPoint = startPoint + func->gradient(startPoint) * gamma;
    times += 1;
  }
  //Find the requested point
  if (startPoint.calDist(newPoint) <= convergedDistance) {
    func->setViaDou(startPoint.getCoords());
    double ans = func->evaluate();
    std::cout.precision(13);  // display;
    if (abs(ans) < 1) {
      std::cout.setf(std::ios::fixed, std::ios::floatfield);
      std::cout << ans << "\n";
      std::cout.unsetf(std::ios::fixed);
    }
    else {
      std::cout << ans << "\n";
    }
    return;
  }
  //run out of time
  else {
    std::cout << "Alread reach giving up number of trials. Did not find.\n";
    return;
  }
}
void Extremer::getMinimum() {
  int times = 0;
  //calculate the next point
  Vector newPoint = startPoint - func->gradient(startPoint) * gamma;
  times += 1;
  while (startPoint.calDist(newPoint) > convergedDistance && times < trials) {
    //update current point and the next point
    startPoint = newPoint;
    newPoint = startPoint - func->gradient(startPoint) * gamma;
    times += 1;
  }
  //Find the requested point
  if (startPoint.calDist(newPoint) <= convergedDistance) {
    func->setViaDou(startPoint.getCoords());
    double ans = func->evaluate();
    std::cout.precision(13);  // display;
    if (abs(ans) < 1) {
      std::cout.setf(std::ios::fixed, std::ios::floatfield);
      std::cout << ans << "\n";
      std::cout.unsetf(std::ios::fixed);
    }
    else {
      std::cout << ans << "\n";
    }
    return;
  }
  //run out of time
  else {
    std::cout << "Alread reach giving up number of trials. Did not find.\n";
    return;
  }
}
