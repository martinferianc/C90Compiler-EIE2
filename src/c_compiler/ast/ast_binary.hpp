#ifndef ast_binary_hpp
#define ast_binary_hpp

#include "context.hpp"

class BinaryExpression: public Expression{
public:
  BinaryExpression(Expression* _left, const string& _op, Expression* _right);
  void add(Expression* _exp);
  uint32_t getSize(Context& context) const;
  string print(const bool& complete) const;
  void setType(const string &_type);
  string getType() const;
  string getVal() const;
  void codeGen(const string& destReg, Context& context);
private:
  Expression* left;
  Expression* right;
  string op;
};

#endif
