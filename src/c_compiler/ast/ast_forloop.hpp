#ifndef ast_forloop_hpp
#define ast_forloop_hpp

#include "context.hpp"

class ForLoop: public Expression{
public:
  ForLoop(Expression* _var, Expression* _cond, Expression* _act, Expression* _statement);
  void add(Expression* _exp);
  uint32_t getSize(Context& context) const;
  string print(const bool& complete) const;
  void setType(const string &_type);
  string getType() const;
  string getVal() const;
  void codeGen(const string& destReg, Context& context);
private:
  Expression* variable;
  Expression* condition;
  Expression* action;
  Expression* statement;
};

#endif
