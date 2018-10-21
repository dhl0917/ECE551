#ifndef __T_MATRIX_H___
#define __T_MATRIX_H___

#include <assert.h>

#include <cstdlib>
#include <iostream>
#include <vector>

//YOUR CODE GOES HERE!
template<typename T>
class Matrix
{
 private:
  int numRows;
  int numColumns;
  std::vector<std::vector<T> > rows;

 public:
  Matrix() : numRows(0), numColumns(0), rows(0) {}
  Matrix(int r, int c) : numRows(r), numColumns(c), rows(numRows) {
    for (int i = 0; i < numRows; i++) {
      std::vector<T> line(numColumns);
      rows[i] = line;
    }
  }
  Matrix(const Matrix & rhs) : numRows(rhs.numRows), numColumns(rhs.numColumns), rows(rhs.rows) {}
  ~Matrix() {}
  Matrix & operator=(const Matrix & rhs) {
    if (this != &rhs) {
      rows = rhs.rows;
      numRows = rhs.numRows;
      numColumns = rhs.numColumns;
    }
    return *this;
  }
  int getRows() const { return numRows; }
  int getColumns() const { return numColumns; }

  const std::vector<T> & operator[](int index) const {
    assert(index >= 0 && index <= numRows - 1);
    return rows[index];  //return the reference of a int*
  }
  std::vector<T> & operator[](int index) {
    assert(index >= 0 && index <= numRows - 1);
    return rows[index];  //return the reference of a int*
  }

  bool operator==(const Matrix & rhs) const {
    if (numRows != rhs.numRows) {
      return false;
    }
    if (numColumns != rhs.numColumns) {
      return false;
    }
    for (int i = 0; i < numRows; i++) {
      if (rows[i] != rhs.rows[i]) {
        return false;
      }
    }
    return true;
  }
  Matrix operator+(const Matrix & rhs) const {
    assert(numRows == rhs.numRows);
    assert(numColumns == rhs.numColumns);
    Matrix sum(numRows, numColumns);
    for (int i = 0; i < numRows; i++) {
      for (int j = 0; j < numColumns; j++) {
        sum[i][j] = (*this)[i][j] + rhs[i][j];
      }
    }
    return sum;
  }
};

template<typename T>
std::ostream & operator<<(std::ostream & s, const std::vector<T> & rhs) {
  if (rhs.size() <= 0) {
    s << "{}";
    return s;
  }
  s << "{" << rhs[0];
  for (size_t i = 1; i < rhs.size(); i++) {
    s << ", " << rhs[i];
  }
  s << "}";
  return s;
}

template<typename T>
std::ostream & operator<<(std::ostream & s, const Matrix<T> & rhs) {
  if (rhs.getRows() <= 0) {
    s << "[  ]";
    return s;
  }

  s << "[ " << rhs[0];
  for (int i = 1; i < rhs.getRows(); i++) {
    s << ",\n" << rhs[i];
  }
  s << " ]";
  return s;
}

#endif
