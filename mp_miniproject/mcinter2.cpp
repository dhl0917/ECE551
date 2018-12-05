#include "mcinter2.h"

double Mcinter::getRanDou(double low, double high) {
  double myDouble = ((double)rand() * ((high - low) / RAND_MAX) + low);
  return myDouble;
}
std::vector<double> Mcinter::getRanDouVec() {
  std::vector<double> douVec;
  for (size_t i = 0; i < getFunction()->getArgs().size(); ++i) {
    douVec.push_back(getRanDou(getArgv()[i].first, getArgv()[i].second));
  }
  return douVec;
}
bool Mcinter::integrate() {
  if (getExpr() == NULL) {
    return false;
  }
  //small demo to see if it is legal
  getFunction()->setViaDou(getRanDouVec());
  if (getFunction()->evaluate() == DBL_MIN) {
    std::cerr << "Invalid integrand.\n";
    return false;  //Did not pass demo test
  }
  //Have passed demo test
  double funcAvg = 0;
  for (int i = 0; i < getSteps(); ++i) {
    getFunction()->setViaDou(getRanDouVec());
    funcAvg += (getFunction()->evaluate() / getSteps());
  }
  double ans = funcAvg * multipleRanges();
  std::cout.precision(13);  // display;
  if (abs(ans) < 1) {
    std::cout.setf(std::ios::fixed, std::ios::floatfield);
    std::cout << ans << "\n";
    std::cout.unsetf(std::ios::fixed);
    return true;
  }
  else {
    std::cout << ans << "\n";
    return true;
  }
}
double Mcinter::multipleRanges() {
  double product = 1;
  for (size_t i = 0; i < getArgv().size(); i++) {
    product *= (getArgv()[i].second - getArgv()[i].first);
  }
  return product;
}
