#ifndef ast_argument_hpp
#define ast_argument_hpp

#include "context.hpp"

class ArgumentList: public Expression{
public:
  ArgumentList();
  void add(Expression* _exp);
  uint32_t getSize(Context& context) const;
  string print(const bool& complete) const;
  void setType(const string &_type);
  string getType() const;
  string getVal() const;
  void codeGen(const string& destReg, Context& context);
private:
  vector<Expression*> arguments;
};

#endif
