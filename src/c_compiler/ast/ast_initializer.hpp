#ifndef ast_initializer_hpp
#define ast_initializer_hpp

#include "context.hpp"


class InitializerList: public Expression{
public:
  InitializerList();
  void add(Expression* _exp);
  uint32_t getSize(Context& context) const;
  string print(const bool& complete) const;
  void setType(const string &_type);
  string getType() const;
  string getVal() const;
  void codeGen(const string& destReg, Context& context);
private:
  vector<Expression*> initializers;
};


#endif
