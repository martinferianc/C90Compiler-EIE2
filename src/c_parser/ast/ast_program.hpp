#ifndef ast_program_hpp
#define ast_program_hpp

#include <vector>
#include <string>
#include <sstream>

using namespace std;

class Program: public Expression{
public:
  Program(){}
  void add(Expression* _exp){
    if(_exp==NULL){return;}
    size_t found;
    for (Expression* exp: expressions){
      found=exp->getVal().find(_exp->getVal());
      if ((exp->getVal()=="")||(_exp->getVal()=="")){
        continue;
      }
      if (found!=string::npos){
        return;
      }
    }
      expressions.push_back(_exp);
  }
  string print(const bool& complete) const{
    stringstream ss;
    if (expressions.size()>=1){
      ss<<"<?xml version=\"1.0\"?>"<<"<Program>"<<endl;
      for (Expression* exp: expressions){
        ss<<exp->print(complete);
      }
      ss<<"</Program>"<<endl;
    }
    return ss.str();
  }
  string getType() const{
    return "prog";
  }
  bool isLeaf() const{
    return false;
  }
  bool isScopeEmpty() const {
    return expressions.empty();
  }
  string getVal() const{
    return "";
  }
private:
  vector<Expression*> expressions;
};

#endif
