#include "ast_dowhileloop.hpp"

DoWhileLoop::DoWhileLoop(Expression* _conditions, Expression* _statement){
  conditions = _conditions;
  if (_statement){
    statement = _statement;
  }
}
void DoWhileLoop::add(Expression* _exp){
  if (statement){
    statement->add(_exp);
  }
}
uint32_t DoWhileLoop::getSize(Context& context) const{
  if (statement){
    return statement->getSize(context) + conditions->getSize(context);
  } else {
    return conditions->getSize(context);
  }
}
string DoWhileLoop::print(const bool& complete) const{
  stringstream ss;
  ss<<"<DoWhileLoop>"<<endl;
  ss<<"<Scope>"<<endl;
  if (statement){
    ss<<statement->print(complete);
  }
  ss<<"</Scope>"<<endl;
  ss<<"<Condition>"<<endl;
  ss<<conditions->print(complete)<<endl;
  ss<<"</Condition>"<<endl;
  ss<<"</DoWhileLoop>"<<endl;

  return ss.str();
}
void DoWhileLoop::setType(const string &_type){}
string DoWhileLoop::getType() const{
  return "DoWhileLoop";
}
string DoWhileLoop::getVal() const{
  return "";
}
void DoWhileLoop::codeGen(const string& destReg, Context& context){
  //Create labels and scratch registers
  context.incrementLoopCounter();
  string L1 = string("$LOOP"+to_string(context.getLoopCounter()));
  string L2 = string("$EXIT"+to_string(context.getLoopCounter()));

  string reg1 = context.getFreeRegister("");
  string scratch_id1 = context.makeLabel("scratch_dowhile");
  context.makeBinding(scratch_id1, reg1,"scratch");

  cout<<L1<<":"<<endl;
  //Codegen the condition
  if (statement){
    statement->codeGen(destReg, context);
  }
  conditions->codeGen(reg1, context);
  cout<<"\t"<<"bne "<<reg1<<",$0,"<<L1
  <<"\t #Branching for loop"
  <<endl;
  cout<<"\t"<<"nop"<<endl;
  cout<<L2<<":"<<endl;
  context.releaseBinding(scratch_id1);
}
