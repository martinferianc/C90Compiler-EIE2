#ifndef ast_switch_hpp
#define ast_switch_hpp

#include "context.hpp"

class Switch: public Expression{
public:
  Switch(Expression* _exp, Expression* _scope);
  void add(Expression* _exp);
  uint32_t getSize(Context& context) const;
  string print(const bool& complete) const;
  void setType(const string &_type);
  string getType() const;
  string getVal() const;
  void codeGen(const string& destReg, Context& context);
private:
  Expression* exp;
  Expression* scope;
};

class Case: public Expression{
public:
  Case(Expression* _exp, Expression* _sta);
  void add(Expression* _exp);
  uint32_t getSize(Context& context) const;
  string print(const bool& complete) const;
  void setType(const string &_type);
  string getType() const;
  string getVal() const;
  void codeGen(const string& destReg, Context& context);
private:
  Expression* exp;
  Expression* sta;
  string type;
};

#endif
