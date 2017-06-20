#ifndef ast_dowhileloop_hpp
#define ast_dowhileloop_hpp

#include "context.hpp"

class DoWhileLoop: public Expression{
public:
  DoWhileLoop(Expression* _conditions, Expression* _statement);
  void add(Expression* _exp);
  uint32_t getSize(Context& context) const;
  string print(const bool& complete) const;
  void setType(const string &_type);
  string getType() const;
  string getVal() const;
  void codeGen(const string& destReg, Context& context);
private:
  Expression* statement;
  Expression* conditions;
};

#endif
