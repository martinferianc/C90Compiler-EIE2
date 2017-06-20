#include "ast_switch.hpp"

Switch::Switch(Expression* _exp, Expression* _scope){
  exp = _exp;
  scope = _scope;
}
void Switch::add(Expression* _exp){
}
uint32_t Switch::getSize(Context& context) const{
  if(scope){
    return exp->getSize(context) + scope->getSize(context);
  } else {
    return exp->getSize(context);
  }
}
string Switch::print(const bool& complete) const{
  stringstream ss;

  ss<<"<Switch>"<<endl;
  ss<<"<Condition>"<<endl;
  ss<<exp->print(complete)<<endl;
  ss<<"</Condition>"<<endl;

  if(scope){
    ss<<scope->print(complete)<<endl;
  }
  ss<<"</Switch>"<<endl;
  return ss.str();
}
void Switch::setType(const string &_type){}
string Switch::getType() const{
  return "switch";
}
string Switch::getVal() const{
  return "";
}
void Switch::codeGen(const string& destReg, Context& context){
  context.incrementLoopCounter();
  context.incrementCaseCounter();
  string L1 = string("$EXIT"+to_string(context.getLoopCounter()));

  string reg1 = context.getFreeRegister("");
  string scratch_id1 = context.makeLabel("scratch_switch");
  context.makeBinding(scratch_id1, reg1, "scratch");

  exp->codeGen(reg1, context);
  if (scope){
    scope->codeGen(reg1, context);
  }
  cout<<L1<<":"<<endl;
  string L2 = string("$CASE"+to_string(context.getCaseCounter()+1));
  cout<<L2<<":"<<endl;
  context.releaseBinding(scratch_id1);
}


Case::Case(Expression* _exp, Expression* _sta){
  exp = _exp;
  if (_sta){
    sta = _sta;
  }
  type = "";
}
void Case::add(Expression* _exp){}
uint32_t Case::getSize(Context& context) const{
  if(sta){
    return sta->getSize(context);
  }
}
string Case::print(const bool& complete) const{
  stringstream ss;

  ss<<"<Case type=\""<<type<<"\">"<<endl;
  ss<<"<Condition>"<<endl;
  if (type.compare("default")!=0){
    ss<<exp->print(complete)<<endl;
  }
  ss<<"</Condition>"<<endl;
  ss<<"</Case>"<<endl;
  if(sta){
    ss<<sta->print(complete)<<endl;
  }
  return ss.str();
}
void Case::setType(const string &_type){
  type = _type;
}
string Case::getType() const{
  return type;
}
string Case::getVal() const{
  return "";
}
void Case::codeGen(const string& destReg, Context& context){
  context.incrementCaseCounter();
  string L0 = string("$CASE"+to_string(context.getCaseCounter()));
  string L1 = string("$CASE"+to_string(context.getCaseCounter()+1));


  string reg1 = context.getFreeRegister("");
  string scratch_id1 = context.makeLabel("scratch_case");
  context.makeBinding(scratch_id1, reg1, "scratch");

  cout<<L0<<":"<<endl;
  if (type.compare("default")!=0){
    exp->codeGen(reg1, context);
    cout<<"\t"<<"bne "<<reg1<<","<<destReg<<","<<L1
    <<"\t #Branching for next Case"
    <<endl;
    cout<<"\t"<<"nop"<<endl;
  }
  context.releaseBinding(scratch_id1);
  if (sta){
    sta->codeGen(destReg, context);
  }
}
