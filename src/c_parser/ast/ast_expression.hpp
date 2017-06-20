#ifndef ast_expression_hpp
#define ast_expression_hpp

#include <string>
#include <iostream>

using namespace std;

//Base class, from which others inherit
//  - Can print in XML
//  - Add adds an expression to a Scope or ParameterList
//  - getType returns the type

class Expression {
public:
  virtual ~Expression(){}
  virtual string print(const bool& complete) const =0;
  virtual void add(Expression* _exp)= 0;
  virtual string getType() const = 0;
  virtual bool isLeaf() const = 0;
  virtual bool isScopeEmpty() const = 0;
  virtual string getVal() const = 0;
};


#endif
