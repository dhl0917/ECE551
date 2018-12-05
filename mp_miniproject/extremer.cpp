#include "extremer.h"

void Extremer::initialize() {
  //parse expr to get necessary information of the fucntion and requist
  Parser myParser(myFuncs);
  std::string funcName = myParser.parseFuncName(expr);
  if ((*myFuncs).count(funcName) <= 0) {  //invalid funcname
    std::cerr << "Invalid function name.\n";
    expr = NULL;
    return;
  }
  func = (*myFuncs)[funcName];
  Expression * myGamma = myParser.parse(expr);
  if (myGamma == NULL) {  //invalid gamma
    std::cerr << "Invalid input for gamma.\n";
    expr = NULL;
    return;
  }
  gamma = myGamma->evaluate();
  delete myGamma;
  Expression * myConverDist = myParser.parse(expr);
  if (myConverDist == NULL) {  //invalid Converdged distance
    std::cerr << "Invalid input for converdged distance.\n";
    expr = NULL;
    return;
  }
  convergedDistance = myConverDist->evaluate();
  delete myConverDist;

  std::vector<double> temp;
  for (size_t i = 0; i < func->getArgs().size(); ++i) {
    Expression * coord = myParser.parse(expr);
    if (coord == NULL) {  //invalid parameter
      std::cerr << "Invalid start point.\n";
      expr = NULL;
      return;
    }
    temp.push_back(coord->evaluate());
    delete coord;
  }
  startPoint = Vector(temp);
  Expression * myTrials = myParser.parse(expr);
  if (myTrials == NULL) {  //invalid trials
    std::cerr << "Invalid input for trials.\n";
    expr = NULL;
    return;
  }
  trials = myTrials->evaluate();
  delete myTrials;
  //Check if more arguments than need
  Expression * checkItsBack = myParser.parse(expr);
  if (checkItsBack != NULL) {
    std::cerr << "Unnecessary parameters.\n";
    expr = NULL;
    delete checkItsBack;
    return;
  }
}
bool Extremer::getMaximum() {
  if (expr == NULL) {
    return false;
  }
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
      std::cout << ans;
      std::cout.unsetf(std::ios::fixed);
    }
    else {
      std::cout << ans;
    }
    std::cout << " @ ";
    startPoint.printVector();
    return true;
  }
  //run out of time
  else {
    std::cout << "Alread reach giving up number of trials. Did not find. Last working point:\n";
    newPoint.printVector();
    return true;
  }
}
bool Extremer::getMinimum() {
  if (expr == NULL) {
    return false;
  }
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
      std::cout << ans;
      std::cout.unsetf(std::ios::fixed);
    }
    else {
      std::cout << ans;
    }
    std::cout << " @ ";
    startPoint.printVector();
    return true;
  }
  //run out of time
  else {
    std::cout << "Alread reach giving up number of trials. Did not find. Last working point:\n";
    newPoint.printVector();
    return true;
  }
}
