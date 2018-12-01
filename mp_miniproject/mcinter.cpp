#include "mcinter.h"

void Mcinter::initialize() {
  srand((unsigned)time(NULL));
  Parser myParser(myFuncs);
  std::string funcName = myParser.parseFuncName(expr);
  func = (*myFuncs)[funcName];
  Expression * myTrials = myParser.parse(expr);
  trials = myTrials->evaluate();
  delete myTrials;
  for (size_t i = 0; i < func->getArgs().size(); ++i) {  //what if not enough
    Expression * low = myParser.parse(expr);
    Expression * high = myParser.parse(expr);  //check result???
    argv.push_back(std::pair<double, double>(low->evaluate(), high->evaluate()));
    delete low;
    delete high;
  }
}
double Mcinter::getRanDou(double low, double high) {
  double myDouble = ((double)rand() * ((high - low) / RAND_MAX) + low);
  return myDouble;
}
std::vector<double> Mcinter::getRanDouVec() {
  std::vector<double> douVec;
  for (size_t i = 0; i < func->getArgs().size(); ++i) {
    douVec.push_back(getRanDou(argv[i].first, argv[i].second));
  }
  return douVec;
}
double Mcinter::integrate() {
  double funcAvg = 0;
  for (int i = 0; i < trials; ++i) {
    func->setViaDou(getRanDouVec());
    funcAvg += (func->evaluate() / trials);
  }
  return funcAvg * multipleRanges();
}
double Mcinter::multipleRanges() {
  double product = 1;
  for (size_t i = 0; i < argv.size(); i++) {
    product *= (argv[i].second - argv[i].first);
  }
  return product;
}
