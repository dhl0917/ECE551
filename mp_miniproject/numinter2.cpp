#include "numinter2.h"

void Numinter::integrate() {
  std::vector<double> values;
  values.resize(loopDepth);
  std::vector<std::pair<double, double> > argv = getArgv();
  accumulate(0, argv, getSteps(), values);
  std::cout.precision(13);  // display;
  if (abs(sum) < 1) {
    std::cout.setf(std::ios::fixed, std::ios::floatfield);
    std::cout << sum << "\n";
    std::cout.unsetf(std::ios::fixed);
  }
  else {
    std::cout << sum << "\n";
  }

  //return sum;
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
