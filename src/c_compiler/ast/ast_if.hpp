#ifndef ast_if_hpp
#define ast_if_hpp

#include "context.hpp"

class If: public Expression{
public:
  If(Expression* _conditions, Expression* _scope_true, Expression* _scope_else);
  void add(Expression* _exp);
  uint32_t getSize(Context& context) const;
  string print(const bool& complete) const;
  void setType(const string &_type);
  string getType() const;
  string getVal() const;
  void codeGen(const string& destReg, Context& context);
private:
  Expression* scope_true;
  Expression* scope_false;
  Expression* conditions;
};
#endif
