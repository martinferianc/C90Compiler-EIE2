#ifndef ast_function_hpp
#define ast_function_hpp

#include "context.hpp"

class Function: public Expression{
public:
  Function(const string &_id, Expression* _parameters, Expression* _scope);
  void add(Expression* _exp);
  uint32_t getSize(Context& context) const;
  string print(const bool& complete) const;
  void setType(const string &_type);
  string getType() const;
  string getVal() const;
  void codeGen(const string& destReg, Context& context);
private:
  string id, type;
  Expression* parameters;
  Expression* scope;
};

class FunctionCall: public Expression{
public:
  FunctionCall(const string &_id, Expression* _arguments);
  void add(Expression* _exp);
  uint32_t getSize(Context& context) const;
  string print(const bool& complete) const;
  void setType(const string &_type);
  string getType() const;
  string getVal() const;
  void codeGen(const string& destReg, Context& context);
private:
  string id;
  Expression* arguments;
};

class FunctionDec: public Expression{
public:
  FunctionDec(const string &_id, Expression* _parameters);
  void add(Expression* _exp);
  uint32_t getSize(Context& context) const;
  string print(const bool& complete) const;
  void setType(const string &_type);
  string getType() const;
  string getVal() const;
  void codeGen(const string& destReg, Context& context);
private:
  string id;
  Expression* parameters;
};

#endif
