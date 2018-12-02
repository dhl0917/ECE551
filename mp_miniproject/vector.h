#ifndef VECTOR_H
#define VECTOR_H
#include <float.h>
#include <math.h>
#include <stdio.h>

#include <cstdlib>
#include <iostream>
#include <vector>
class Vector
{
 private:
  std::vector<double> coords;

 public:
  Vector() {}
  Vector(std::vector<double> location) : coords(location) {}
  Vector(const Vector & rhs) : coords(rhs.coords) {}
  Vector & operator=(const Vector & rhs) {
    if (this != &rhs) {
      coords = rhs.coords;
    }
    return *this;
  }
  std::vector<double> getCoords();
  double calDist(Vector rhs);
  size_t getSize() const { return coords.size(); }
  Vector operator+(const Vector & rhs) const;
  Vector operator-(const Vector & rhs) const;
  Vector operator*(const double & rhs) const;
  ~Vector() {}
};

#endif
