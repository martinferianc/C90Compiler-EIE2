#ifndef ast_whileloop_hpp
#define ast_whileloop_hpp

class WhileLoop: public Expression{
public:
  WhileLoop(Expression* _conditions, Expression* _scope){
    conditions = _conditions;
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
    return "whileloop";
  }
  string getVal() const{
    return "";
  }
private:
  Expression* scope;
  Expression* conditions;
};

#endif
