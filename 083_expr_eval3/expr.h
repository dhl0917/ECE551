#include <cstdio>
#include <iostream>
#include <sstream>

class Expression
{
 public:
  Expression() {}
  virtual std::string toString() const = 0;
  virtual ~Expression() {}
  virtual double evaluate() const = 0;
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
  virtual double evaluate() const { return -100.0; }
  virtual ~NumExpression() {}
};

class OpExpression : public Expression
{
 private:
  Expression * left;
  Expression * right;
  std::string op;

 public:
  OpExpression(Expression * lhs, Expression * rhs, std::string opSign) :
      left(lhs),
      right(rhs),
      op(opSign) {}
  virtual std::string toString() const {
    return "(" + left->toString() + op + right->toString() + ")";
  }
  virtual double evaluate() const {
    std::stringstream s;
    long a = 0.0;
    long b = 0.0;
    if (op == " + ") {
      s << left->toString();
      s >> a;
      s.clear();
      s << right->toString();
      s >> b;
      return a + b;
    }
    if (op == " - ") {
      s << left->toString();
      s >> a;
      s.clear();
      s << right->toString();
      s >> b;
      return a - b;
    }
    if (op == " * ") {
      s << left->toString();
      s >> a;
      s.clear();
      s << right->toString();
      s >> b;
      return a * b;
    }
    if (op == " / ") {
      s << left->toString();
      s >> a;
      s.clear();
      s << right->toString();
      s >> b;
      return a / (1.0 * b);
    }
    return -50.0;
  }
  virtual ~OpExpression() {
    delete left;
    delete right;
  }
};

class PlusExpression : public OpExpression
{
 public:
  PlusExpression(Expression * l, Expression * r) : OpExpression(l, r, " + ") {}
  virtual ~PlusExpression() {}
};

class MinusExpression : public OpExpression
{
 public:
  MinusExpression(Expression * l, Expression * r) : OpExpression(l, r, " - ") {}
  virtual ~MinusExpression() {}
};

class TimesExpression : public OpExpression
{
 public:
  TimesExpression(Expression * l, Expression * r) : OpExpression(l, r, " * ") {}
  virtual ~TimesExpression() {}
};

class DivExpression : public OpExpression
{
 public:
  DivExpression(Expression * l, Expression * r) : OpExpression(l, r, " / ") {}
  virtual ~DivExpression() {}
};
