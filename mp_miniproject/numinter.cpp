#include "numinter.h"

double Numinter::integrate() {
  std::vector<double> values;
  values.resize(loopDepth);
  accumulate(0, argv, step, values);
  return sum;
}

void Numinter::accumulate(int pos,
                          std::vector<std::pair<double, double> > & ranges,
                          double step,
                          std::vector<double> & values) {
  if (pos == loopDepth) {
    std::vector<double> res;
    res.resize(loopDepth);
    span(0, values, step, res);
    //    func->setViaDou(values);
    // sum += (func->evaluate() * factor);
  }
  else {
    for (double curr = ranges[pos].first; curr <= ranges[pos].second; curr += step) {
      values[pos] = curr;
      accumulate(pos + 1, ranges, step, values);
    }
  }
}
void Numinter::initialize() {
  Parser myParser(myFuncs);
  std::string funcName = myParser.parseFuncName(expr);
  func = (*myFuncs)[funcName];
  Expression * myStep = myParser.parse(expr);
  step = myStep->evaluate();
  delete myStep;
  for (size_t i = 0; i < func->getArgs().size(); ++i) {  //what if not enough
    Expression * low = myParser.parse(expr);
    Expression * high = myParser.parse(expr);  //check result???
    argv.push_back(std::pair<double, double>(low->evaluate(), high->evaluate()));
    delete low;
    delete high;
  }
  loopDepth = func->getArgs().size();
  factor = pow(step, loopDepth);
  divider = pow(2, loopDepth);
  /*
  std::pair<int, int> myPair(0, 1);
  for (size_t i = 0; i < func->getArgs().size(); ++i) {
    spanHelper.push_back(myPair);
  }
  */
}
void Numinter::span(int pos,
                    std::vector<double> & helperVector,
                    double step,
                    std::vector<double> & res) {
  if (pos == loopDepth) {
    func->setViaDou(res);
    sum += (func->evaluate() * factor) / divider;
  }
  else {
    for (double curr = helperVector[pos]; curr <= helperVector[pos] + step; curr += step) {
      res[pos] = curr;
      span(pos + 1, helperVector, step, res);
    }
  }
}
