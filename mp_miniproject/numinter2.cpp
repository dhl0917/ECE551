#include "numinter2.h"

bool Numinter::integrate() {
  if (getExpr() == NULL) {
    return false;
  }
  std::vector<double> values;
  values.resize(loopDepth);
  std::vector<std::pair<double, double> > argv = getArgv();
  //small demo to see if it is legal
  std::vector<double> demoArgv;
  for (size_t i = 0; i < argv.size(); ++i) {
    demoArgv.push_back(argv[i].first);
  }
  getFunction()->setViaDou(demoArgv);
  if (getFunction()->evaluate() == DBL_MIN) {
    std::cerr << "Invalid integrand.\n";
    return false;  //Did not pass demo test
  }
  //Have passed demo test
  accumulate(0, argv, getSteps(), values);
  std::cout.precision(13);
  //display integrated value
  //when its absolute value is less than 1,
  //modify its displaying format
  if (abs(sum) < 1) {
    std::cout.setf(std::ios::fixed, std::ios::floatfield);
    std::cout << sum << "\n";
    std::cout.unsetf(std::ios::fixed);
    return true;
  }
  else {
    std::cout << sum << "\n";
    return true;
  }
}

void Numinter::accumulate(int pos,
                          std::vector<std::pair<double, double> > & ranges,
                          double step,
                          std::vector<double> & values) {
  if (pos == loopDepth) {
    std::vector<double> res;
    res.resize(loopDepth);
    span(0, values, step, res);
  }
  else {
    for (double curr = ranges[pos].first; curr <= ranges[pos].second; curr += step) {
      values[pos] = curr;
      accumulate(pos + 1, ranges, step, values);
    }
  }
}

void Numinter::span(int pos,
                    std::vector<double> & helperVector,
                    double step,
                    std::vector<double> & res) {
  if (pos == loopDepth) {
    getFunction()->setViaDou(res);
    sum += (getFunction()->evaluate() * factor) / divider;
  }
  else {
    for (double curr = helperVector[pos]; curr <= helperVector[pos] + step; curr += step) {
      res[pos] = curr;
      span(pos + 1, helperVector, step, res);
    }
  }
}
