#ifndef ast_variable_hpp
#define ast_variable_hpp

#include "context.hpp"

class Variable : public Expression {
public:
  Variable(const string &_id);
  void add(Expression* _exp);
  uint32_t getSize(Context& context) const;
  string print(const bool& complete) const;
  void setType(const string &_type);
  string getType() const;
  string getVal() const;
  void codeGen(const string& destReg, Context& context);
private:
  string type;
  string id;
};

class VariableList: public Expression{
public:
  VariableList();
  void add(Expression* _exp);
  uint32_t getSize(Context& context) const;
  string print(const bool& complete) const;
  void setType(const string &_type);
  string getType() const;
  string getVal() const;
  void codeGen(const string& destReg, Context& context);
private:
  vector<Expression*> variables;
};

#endif
