#ifndef ast_program_hpp
#define ast_program_hpp

#include "context.hpp"

class Program: public Expression{
public:
  Program();
  void add(Expression* _exp);
  uint32_t getSize(Context& context) const;
  string print(const bool& complete) const;
  void setType(const string &_type);
  string getType() const;
  string getVal() const;
  void codeGen(const string& destReg, Context& context);
private:
  vector<Expression*> statements;
};

#endif
