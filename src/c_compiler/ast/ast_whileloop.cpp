#include "ast_whileloop.hpp"

WhileLoop::WhileLoop(Expression* _conditions, Expression* _statement){
  conditions = _conditions;
  if (_statement){
    statement = _statement;
  }
}
void WhileLoop::add(Expression* _exp){
    statement->add(_exp);
}
uint32_t WhileLoop::getSize(Context& context) const{
  if (statement){
    return statement->getSize(context) + conditions->getSize(context);
  } else {
    return conditions->getSize(context);
  }
}
string WhileLoop::print(const bool& complete) const{
  stringstream ss;
  ss<<"<WhileLoop>"<<endl;
  ss<<"<Condition>"<<endl;
  ss<<conditions->print(complete)<<endl;
  ss<<"</Condition>"<<endl;
  ss<<"<Scope>"<<endl;
  if (statement){
    ss<<statement->print(complete);
  }
  ss<<"</Scope>"<<endl;
  ss<<"</WhileLoop>"<<endl;

  return ss.str();
}
void WhileLoop::setType(const string &_type){}
string WhileLoop::getType() const{
  return "whileloop";
}
string WhileLoop::getVal() const{
  return "";
}
void WhileLoop::codeGen(const string& destReg, Context& context){
  //Create labels and scratch registers
  context.incrementLoopCounter();
  string L1 = string("$LOOP"+to_string(context.getLoopCounter()));
  string L2 = string("$EXIT"+to_string(context.getLoopCounter()));

  string reg1 = context.getFreeRegister("");
  string scratch_id1 = context.makeLabel("scratch_while");
  context.makeBinding(scratch_id1, reg1,"scratch");

  cout<<L1<<":"<<endl;
  //Codegen the condition
  conditions->codeGen(reg1, context);
  cout<<"\t"<<"beq "<<reg1<<",$0,"<<L2
  <<"\t #Branching for End of loop"
  <<endl;
  cout<<"\t"<<"nop"<<endl;
  if (statement){
    statement->codeGen(destReg, context);
  }
  cout<<"\t"<<"b "<<L1<<endl;
  cout<<"\t"<<"nop"<<endl;
  cout<<L2<<":"<<endl;
  context.releaseBinding(scratch_id1);
}
