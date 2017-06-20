#ifndef ast_parameter_hpp
#define ast_parameter_hpp

#include "context.hpp"

class Parameter : public Expression {
public:
  Parameter(const string &_id);
  void add(Expression* _exp);
  uint32_t getSize(Context& context) const;
  string print(const bool& complete) const;
  void setType(const string &_type);
  string getType() const;
  string getVal() const;
  void codeGen(const string& destReg, Context& context);
private:
  string id,type;;
};

class ParameterList: public Expression{
public:
  ParameterList();
  void add(Expression* _exp);
  uint32_t getSize(Context& context) const;
  string print(const bool& complete) const;
  void setType(const string &_type);
  string getType() const;
  string getVal() const;
  void codeGen(const string& destReg, Context& context);
private:
  vector<Expression*> parameters;
};


#endif
