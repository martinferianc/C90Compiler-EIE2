#ifndef ast_primitives_hpp
#define ast_primitives_hpp

#include <vector>
#include <sstream>
#include <string>

using namespace std;

class Variable : public Expression {
public:
  Variable(const string &_id): id(_id){
    value = NULL;
  }
  Variable(const string &_id, Expression* _val): id(_id){
    value = _val;
  }
  string print(const bool& complete) const{
    stringstream ss;
    ss<<"<Variable id=\""<<id<<"\"/>"<<endl;
    return ss.str();
  }
  void add(Expression* _exp){
  }
  string getType() const{
    return "var";
  }
  string getVal() const{
    return id;
  }
  bool isLeaf() const{
    return true;
  }
  bool isScopeEmpty() const {
    return true;
  }
private:
  Expression* next;
  string id;
  Expression* value;
};
class VariableList: public Expression{
public:
  VariableList(){}
  void add(Expression* _exp) override{
    if(_exp==NULL){return;}
    size_t found;
    for (Expression* exp: variables){
      found=exp->getVal().find(_exp->getVal());
      if (found!=string::npos){
        return;
      }
    }
    variables.push_back(_exp);
  }
  string print(const bool& complete) const{
    stringstream ss;
      for (Expression* exp: variables){
        ss<<exp->print(complete);
      }
    return ss.str();
  }
  string getType() const{
    return "variable_list";
  }
  bool isLeaf() const{
    return true;
  }
  bool isScopeEmpty() const {
    return variables.empty();
  }
  string getVal() const{
    stringstream ss;
    for (Expression* exp: variables){
      ss<<exp->getVal()<<" ";
    }
    return ss.str();
  }
private:
  vector<Expression*> variables;
};

class NumberDouble: public Expression{
public:
  NumberDouble(const double &_val): val(_val){}
  string print(const bool& complete) const{
    ostringstream strs;
    strs << val;
    return strs.str();
  }
  void add(Expression* _exp){}
  string getType() const{
    return "double";
  }
  string getVal() const{
    ostringstream strs;
    strs << val;
    return strs.str();
  }
  void setVal(const double &_val){
    val = _val;
  }
  bool isLeaf() const{
    return true;
  }
  bool isScopeEmpty() const {
    return true;
  }
private:
  double val;
};


class NumberInt: public Expression{
public:
  NumberInt(const int &_val): val(_val){}
  string print(const bool& complete) const{
    ostringstream strs;
    strs << val;
    return strs.str();
  }
  void add(Expression* _exp){}
  string getType() const{
    return "int";
  }
  string getVal() const{
    ostringstream strs;
    strs << val;
    return strs.str();
  }
  void setVal(const int &_val){
    val = _val;
  }
  bool isLeaf() const{
    return true;
  }
  bool isScopeEmpty() const {
    return true;
  }
private:
  int val;
};

#endif
