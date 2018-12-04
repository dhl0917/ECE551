#ifndef VECTOR_H
#define VECTOR_H
#include <float.h>
#include <math.h>
#include <stdio.h>

#include <cstdlib>
#include <iostream>
#include <vector>

/*
Vector is a class to represent a vector in a coordinate system. 

#coords: A vector of double to represent the coord for a point or a vector.*/

/*
(default constructor): Take no arguments and initialize the coords an empty vector.

(constructor): Take one argument which is a vector of double and use it to initialize
the vector coords.

(copy constructor): Use the rhs's coords to initialize the coords vector.

assignment operator=: Resize the coords vector and copy every element in the rhs's
coords vector to the corresponding place of this coords vector.

calDist(..): Take a Vector object as right hand side. Use the mathematic formula
to calculate the distance between two Vectors.

operator+: Overload the + opeartor to add two vetor follow the rules that add 
every corresponding elements to give birth to the element in the result vector.

operator-: Overload the - opeartor to minus the corresponding element in rhs's
coords vector with the one the this coords vector to come up with the result vector.

opeartor*: Overload the * opeartor which take a double as its right hand side. Times
every element with the double respectly to form the new element in the result vector.*/

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
      coords.resize(rhs.getSize());
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
