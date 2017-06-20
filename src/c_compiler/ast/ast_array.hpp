#ifndef ast_array_hpp
#define ast_array_hpp

#include "context.hpp"

class Array: public Expression{
public:
  Array(Expression* _id, Expression* _exp);
  Array(Expression* _id, const uint32_t& _counter);
  void add(Expression* _exp);
  uint32_t getSize(Context& context) const;
  string print(const bool& complete) const;
  void setType(const string &_type);
  string getType() const;
  string getVal() const;
  void codeGen(const string& destReg, Context& context);
private:
  uint32_t size;
  string id;
  string type;
  Expression* counter;
};

#endif
