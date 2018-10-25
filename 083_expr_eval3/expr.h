#include <cstdio>
#include <iostream>
#include <sstream>

class Expression
{
 public:
  Expression() {}
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
    std::string ss;
    s << number;
    s >> ss;
    return ss;
  }
  virtual ~NumExpression() {}
};

class OpExpression : public Expression
{
 private:
  Expression * left;
  Expression * right;

 public:
  OpExpression(Expression * lhs, Expression * rhs) : left(lhs), right(rhs) {}
  std::string leftToString() const {
    std::string l = "(" + left->toString();
    return l;
  }
  std::string rightToString() const {
    std::string r = right->toString() + ")";
    return r;
  }

  virtual ~OpExpression() {
    delete left;
    delete right;
  }
};

class PlusExpression : public OpExpression
{
 public:
  PlusExpression(Expression * l, Expression * r) : OpExpression(l, r) {}
  virtual std::string toString() const { return leftToString() + " + " + rightToString(); }
  virtual ~PlusExpression() {}
};

class MinusExpression : public OpExpression
{
 public:
  MinusExpression(Expression * l, Expression * r) : OpExpression(l, r) {}
  virtual std::string toString() const { return leftToString() + " - " + rightToString(); }
  virtual ~MinusExpression() {}
};

class TimesExpression : public OpExpression
{
 public:
  TimesExpression(Expression * l, Expression * r) : OpExpression(l, r) {}
  virtual std::string toString() const { return leftToString() + " * " + rightToString(); }
  virtual ~TimesExpression() {}
};

class DivExpression : public OpExpression
{
 public:
  DivExpression(Expression * l, Expression * r) : OpExpression(l, r) {}
  virtual std::string toString() const { return leftToString() + " / " + rightToString(); }
  virtual ~DivExpression() {}
};
