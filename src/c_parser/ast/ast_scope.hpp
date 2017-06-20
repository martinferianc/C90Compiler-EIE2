#ifndef ast_scope_hpp
#define ast_scope_hpp

#include <vector>
#include <string>
#include <sstream>

using namespace std;

class Scope: public Expression{
public:
  Scope(){}
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
    ss<<endl<<"<Scope>"<<endl;
      for (Expression* exp: expressions){
        ss<<exp->print(complete);
      }
      ss<<"</Scope>"<<endl;
      return ss.str();
  }
  string getType() const{
    return "scope";
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
