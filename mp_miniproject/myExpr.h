#include <math.h>

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
  double number;

 public:
  NumExpression(double num) : number(num) {}
  virtual std::string toString() const {
    std::stringstream strStream;
    std::string myStr;
    strStream << number;
    strStream >> myStr;
    return myStr;
  }
  virtual double evaluate() const { return number; }
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
    if (op == " + ") {
      return left->evaluate() + right->evaluate();
    }
    if (op == " - ") {
      return left->evaluate() - right->evaluate();
    }
    if (op == " * ") {
      return left->evaluate() * right->evaluate();
    }
    if (op == " / ") {
      return left->evaluate() / right->evaluate();
    }
    if (op == " % ") {
      return fmod(left->evaluate(), right->evaluate());
    }

    return -50.0;
  }
  Expression * getLhs() const { return left; }
  Expression * getRhs() const { return right; }
  std::string getOp() const { return op; }

  virtual ~OpExpression() {
    delete left;
    delete right;
  }
};

class SglExpression : public Expression
{
 private:
  Expression * arg;
  std::string func;

 public:
  SglExpression(Expression * val, std::string funcName) : arg(val), func(funcName) {}
  virtual std::string toString() const { return "(" + func + arg->toString() + ")"; }
  virtual double evaluate() const {
    if (func == "sin") {
      return sin(arg->evaluate());
    }
    if (func == "cos") {
      return cos(arg->evaluate());
    }
    if (func == "sqrt") {
      return sqrt(arg->evaluate());
    }
    if (func == "ln") {
      return log(arg->evaluate());
    }
    return -50;
  }
  ~SglExpression() { delete arg; }
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
class RemainderExpression : public OpExpression
{
 public:
  RemainderExpression(Expression * l, Expression * r) : OpExpression(l, r, " % ") {}
  virtual ~RemainderExpression() {}
};
class PowExpression : public OpExpression
{
 public:
  PowExpression(Expression * l, Expression * r) : OpExpression(l, r, " pow ") {}
  virtual double evaluate() const { return pow(getLhs()->evaluate(), getRhs()->evaluate()); }
  virtual std::string toString() const {
    return " ( " + getOp() + " " + getLhs()->toString() + " " + getRhs()->toString() + " ) ";
  }
  virtual ~PowExpression() {}
};
