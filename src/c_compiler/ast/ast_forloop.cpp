#include "ast_forloop.hpp"

ForLoop::ForLoop(Expression* _var, Expression* _cond, Expression* _act, Expression* _statement){
  action = _act;
  variable = _var;
  condition = _cond;
  statement = _statement;
}
void ForLoop::add(Expression* _exp){
  if (statement){
    statement->add(_exp);
  }
}
uint32_t ForLoop::getSize(Context& context) const{
  if (action){
    if (statement){
      return action->getSize(context) + variable->getSize(context) + statement->getSize(context);
    } else {
      return action->getSize(context) + variable->getSize(context);
    }
  } else {
    return variable->getSize(context) + statement->getSize(context);
  }
  return 0;
}
string ForLoop::print(const bool& complete) const{
  stringstream ss;
  ss<<"<ForLoop>"<<endl;
  ss<<"<Condition>"<<endl;
  ss<<condition->print(complete)<<endl;
  ss<<"</Condition>"<<endl;
  if (action){
    ss<<"<Action>"<<endl;
    ss<<action->print(complete)<<endl;
    ss<<"</Action>"<<endl;
  }
  ss<<"<Scope>"<<endl;
  if (statement){
    ss<<statement->print(complete);
  }
  ss<<"</Scope>"<<endl;
  ss<<"</ForLoop>"<<endl;
  return ss.str();
}
void ForLoop::setType(const string &_type){}
string ForLoop::getType() const{
  return "forloop";
}
string ForLoop::getVal() const{
  return "";
}
void ForLoop::codeGen(const string& destReg, Context& context){
  context.incrementLoopCounter();
  context.incrementUpdateCounter();
  string L1 = string("$LOOP"+to_string(context.getLoopCounter()));
  string L2 = string("$EXIT"+to_string(context.getLoopCounter()));
  string L3 = string("$UPDATE"+to_string(context.getUpdateCounter()));

  string scratch_id1 = context.makeLabel("scratch_for");
  string reg1 = context.getFreeRegister("");
  context.makeBinding(scratch_id1, reg1,"scratch");

  variable->codeGen("", context);

  cout<<L1<<":"<<endl;
  condition->codeGen(reg1, context);
  cout<<"\t"<<"beq "<<reg1<<",$0,"<<L2
  <<"\t #Branching for End of loop"
  <<endl;
  cout<<"\t"<<"nop"<<endl;
  if (statement){
    statement->codeGen(destReg, context);
  }
  if (action){
    cout<<L3<<":"<<endl;
    action->codeGen("", context);
  }
  cout<<"\t"<<"b "<<L1<<endl;
  cout<<"\t"<<"nop"<<endl;
  cout<<L2<<":"<<endl;

  context.releaseBinding(scratch_id1);
}
