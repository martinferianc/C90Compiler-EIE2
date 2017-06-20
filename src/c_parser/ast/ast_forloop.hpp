#ifndef ast_forloop_hpp
#define ast_forloop_hpp

#include <string>
#include <sstream>

class ForLoop: public Expression{
public:
  ForLoop(Expression* _var, Expression* _cond, Expression* _act, Expression* _scope){
    action = _act;
    variable = _var;
    condition = _cond;
    scope = _scope;
  }
  void add(Expression* _exp){
      scope->add(_exp);
  }
  string print(const bool& complete) const{
    stringstream ss;
    if (scope){
      ss<<"<Scope>"<<endl;
      ss<<scope->print(complete);
      ss<<"</Scope>"<<endl;
    }
    return ss.str();
  }
  bool isLeaf() const {
    return false;
  }
  bool isScopeEmpty() const {
    return scope->isScopeEmpty();
  }
  string getType() const{
    return "forloop";
  }
  string getVal() const{
    return "";
  }

private:
  Expression* variable;
  Expression* condition;
  Expression* action;
  Expression* scope;
};

#endif
