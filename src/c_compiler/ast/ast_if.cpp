#include "ast_if.hpp"

If::If(Expression* _conditions, Expression* _scope_true, Expression* _scope_false){
  conditions = _conditions;
  if (_scope_true){
    scope_true = _scope_true;
  }
  if (_scope_false){
    scope_false = _scope_false;
  }
}
void If::add(Expression* _exp){}
uint32_t If::getSize(Context& context) const{
  if (scope_false && scope_true){
    return conditions->getSize(context) + scope_true->getSize(context) + scope_false->getSize(context);
  } else {
    if (scope_true){
      return conditions->getSize(context) + scope_true->getSize(context);
    } else {
      return 0;
    }
  }
}
string If::print(const bool& complete) const{
  stringstream ss;

  ss<<"<If>"<<endl;
  ss<<"<Condition>"<<endl;
  ss<<conditions->print(complete)<<endl;
  ss<<"</Condition>"<<endl;

  if (scope_true){
    ss<<"<True>"<<endl;
    ss<<scope_true->print(complete)<<endl;
    ss<<"</True>"<<endl;
  }
  if (scope_false){
    ss<<"<Else>"<<endl;
    ss<<scope_false->print(complete);
    ss<<"</Else>"<<endl;
  }
  ss<<"</If>"<<endl;
  return ss.str();
}
void If::setType(const string &_type){
  scope_true->setType(_type);
}
string If::getType() const{
  return "if";
}
string If::getVal() const{
  return "";
}
void If::codeGen(const string& destReg, Context& context){
  string L1 = context.makeLabel("If_FALSE");
  string L2 = context.makeLabel("If_EXIT");

  string reg1 = context.getFreeRegister("");
  string scratch_id1 = context.makeLabel("scratch_if");
  context.makeBinding(scratch_id1, reg1, "scratch");

  conditions->codeGen(reg1, context);
  cout<<"\t"<<"beq "<<reg1<<",$0,"<<L1
  <<"\t #Branching for False"
  <<endl;
  cout<<"\t"<<"nop"<<endl;
  if (scope_true){
    scope_true->codeGen(destReg, context);
  }

  cout<<"\t"<<"b "<<L2<<endl;
  cout<<"\t"<<"nop"<<endl;
  cout<<L1<<":"<<endl;
  if(scope_false){
    scope_false->codeGen(destReg, context);
  }
  cout<<L2<<":"<<endl;
  context.releaseBinding(scratch_id1);
}
