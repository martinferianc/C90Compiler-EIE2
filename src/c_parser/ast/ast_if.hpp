#ifndef ast_if_hpp
#define ast_if_hpp

class If: public Expression{
public:
  If(Expression* _conditions, Expression* _scope_true, Expression* _scope_else){
    conditions = _conditions;
    scope_true = _scope_true;
    scope_else = _scope_else;
  }
  void add(Expression* _exp){
  }
  string print(const bool& complete) const{
    stringstream ss;
    if (scope_true){
      ss<<"<Scope>"<<endl;
      ss<<scope_true->print(complete)<<endl;
      ss<<"</Scope>"<<endl;
    }
    if (scope_else){
      ss<<"<Scope>"<<endl;
      ss<<scope_else->print(complete);
      ss<<"</Scope>"<<endl;
    }
    return ss.str();
  }
  bool isLeaf() const {
    return false;
  }
  bool isScopeEmpty() const {
    if (scope_else)
      return scope_true->isScopeEmpty() || scope_else->isScopeEmpty();
    else
      return scope_true->isScopeEmpty();
  }
  string getType() const{
    return "if";
  }
  string getVal() const{
    return "";
  }
private:
  Expression* scope_true;
  Expression* scope_else;
  Expression* conditions;
};
#endif
