#include "vector.h"

std::vector<double> Vector::getCoords() {
  return coords;
}

double Vector::calDist(Vector rhs) {
  if (coords.size() != rhs.coords.size()) {
    std::cerr << "Different Dimensions. Cannot calculate the distance.\n";
    return DBL_MIN;
  }
  double dist = 0;
  for (size_t i = 0; i < coords.size(); i++) {
    dist += (coords[i] - rhs.getCoords()[i]) * (coords[i] - rhs.getCoords()[i]);
  }
  dist = sqrt(dist);
  return dist;
}
Vector Vector::operator+(const Vector & rhs) const {
  if ((*this).getSize() != rhs.getSize()) {
    std::cerr << "Different Dimensions. Cannot make a plus.\n";
    return Vector();
  }
  std::vector<double> res;
  res.resize(coords.size());
  for (size_t i = 0; i < (*this).getSize(); i++) {
    res[i] = coords[i] + rhs.coords[i];
  }
  return Vector(res);
}
Vector Vector::operator-(const Vector & rhs) const {
  if ((*this).getSize() != rhs.getSize()) {
    std::cerr << "Different Dimensions. Cannot make a plus.\n";
    return Vector();
  }
  std::vector<double> res;
  res.resize(coords.size());
  for (size_t i = 0; i < (*this).getSize(); i++) {
    res[i] = coords[i] - rhs.coords[i];
  }
  return Vector(res);
}
Vector Vector::operator*(const double & rhs) const {
  std::vector<double> res;
  res.resize(coords.size());
  for (size_t i = 0; i < (*this).getSize(); i++) {
    res[i] = coords[i] * rhs;
  }
  return Vector(res);
}
void Vector::printVector() {
  if (coords.size() == 0) {
    return;
  }
  else {
    std::cout.precision(13);
    std::cout << "(" << coords[0];
    for (size_t i = 1; i < coords.size(); i++) {
      std::cout << ", " << coords[i];
    }
    std::cout << ")\n";
  }
}
