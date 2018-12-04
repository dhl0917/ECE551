#include <float.h>
#include <math.h>

#include <cstdio>
#include <iostream>
#include <sstream>
//CITE: Come up with the codes provided in assignment 083 but modified greatly.

/*Expression class is an abstract class. It has its own constructor and destructor.
And also two abstract functions.*/
class Expression
{
 public:
  Expression() {}
  virtual std::string toString() const = 0;
  virtual ~Expression() {}
  virtual double evaluate() const = 0;
};

/*NumExpression is the child class of Expression. 

#number: The double number the NumExpression represents.*/

/*
(constructor): Take one argument and use it to initialize the number field.

toString(): Overloads the toString() function to convert the number field 
to a string. 

evaluate(): Evaluate and return the result of the numeric expression.*/

class NumExpression : public Expression
{
 private:
  double number;

 public:
  NumExpression(double num) : number(num) {}
  virtual std::string toString() const {
    std::stringstream strStream;
    strStream.precision(13);
    std::string myStr;
    strStream << number;
    strStream >> myStr;
    return myStr;
  }
  virtual double evaluate() const { return number; }
  virtual ~NumExpression() {}
};
/*
SglExpression is a child class of Expression. It is used for the kind of
expression who has only one operand. 

#arg: An Expression * pointing to the Expression which is the operand.
#func: A string represents the function name. */

/*
(constructor): Take two arguments and initialize the fields properly.

toString(): Overloads the function to convert the whole SglExpression to a string.

evaluate(): Overloads the function to evaluate the value of the whole Sglexpression.

(destructor): Free its field.*/

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
    return DBL_MIN;
  }
  ~SglExpression() { delete arg; }
};

/*
OpExpression is a child class of Expression. It is used for the expression who has
two operands.

#left: Represent the left operand.
#right: Represent the right operand.
#op: Represent the operator.*/

/*
(constructor): Take three arguments and initialize corresponding fields properly.

toString(): Overloads the toString() to convert the whole expression to a string.

evaluate(): Overloads the evaluate() to evaluate and return the result.

(destructor): Free the necessary fields. */
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

    return DBL_MIN;
  }
  Expression * getLhs() const { return left; }
  Expression * getRhs() const { return right; }
  std::string getOp() const { return op; }

  virtual ~OpExpression() {
    delete left;
    delete right;
  }
};

/*
Below are 6 children classes of the OpExpression. Each of them is one kind of operation
which takes two operands. Every class has a constructor taking two arguments and calls
the parent class's constructor properly. The PowExpression overloads the evaluate() and 
toString() functions to output in a different format.*/

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
