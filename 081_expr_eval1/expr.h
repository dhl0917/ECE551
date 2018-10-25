#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
class Expression
{
 public:
  virtual std::string toString() const = 0;
  virtual ~Expression() {}
};

class NumExpression : public Expression
{
 private:
  long number;

 public:
  NumExpression(long num) : number(num) {}
  virtual std::string toString() const {
    std::stringstream s;
    s << number;
    std::string str;
    s >> str;
    return str;
  }
  virtual ~NumExpression() {}
};

class PlusExpression : public Expression
{
 private:
  Expression * lhs;
  Expression * rhs;

 public:
  PlusExpression(Expression * lhs, Expression * rhs) : lhs(lhs), rhs(rhs) {}
  virtual std::string toString() const {
    std::string left = "(" + lhs->toString();
    std::string right = rhs->toString() + ")";
    std::string plus = " + ";
    std::string s = left + plus + right;
    return s;
  }
  virtual ~PlusExpression() {
    delete lhs;
    delete rhs;
  }
};
