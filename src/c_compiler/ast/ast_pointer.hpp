#ifndef ast_pointer_hpp
#define ast_pointer_hpp

#include "context.hpp"

class Pointer : public Expression {
public:
  Pointer(Expression* exp);
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


class Reference : public Expression {
public:
  Reference(Expression* exp);
  void add(Expression* _exp);
  uint32_t getSize(Context& context) const;
  string print(const bool& complete) const;
  void setType(const string &_type);
  string getType() const;
  string getVal() const;
  void codeGen(const string& destReg, Context& context);
private:
  string id;
};

#endif
