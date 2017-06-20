#include "ast_function.hpp"

Function::Function(const string &_id, Expression* _parameters, Expression* _scope):id(_id){
  parameters = _parameters;
  scope = _scope;
}
void Function::add(Expression* _exp){}
uint32_t Function::getSize(Context& context) const{
  return scope->getSize(context) + parameters->getSize(context);
}
string Function::print(const bool& complete) const{
  stringstream ss;
  ss<<"<Function id=\""<<id<<"\" type=\""<<type<<"\">"<<endl;
  if(parameters){
    ss<<parameters->print(complete);
  }
  if (scope){
    ss<<scope->print(complete);
  }
  ss<<"</Function>";
  return ss.str();
}
void Function::setType(const string &_type){
  type = _type;
}
string Function::getType() const{
  return type;
}
string Function::getVal() const{
  return id;
}
void Function::codeGen(const string& destReg, Context& context){
  uint32_t stack_size = getSize(context)*3;

  cout<<"\t.align	2"<<endl
  <<"\t.globl	"<<id<<endl
  <<"\t.set	nomips16"<<endl
  <<"\t.set	nomicromips"<<endl
  <<"\t.ent	"<<id<<endl;
  cout<<"\t.type\t"<<id<<", @function"<<endl;
  cout<<id<<":"<<endl;

  context.incrementFunctionCounter();
  context.allocateStack(8+stack_size);
  //Versatile register, clean it just in case
  cout<<"\t"<<"move $t9,$0"<<endl;
  parameters->codeGen("", context);

  if (id.compare("main")==0){
    cout<<"\t"<<"move $2,$0"<<endl;
    vector<Expression*> global;
    context.loadGlobalExpression(global);
    for (Expression* exp: global){
      exp->codeGen("", context);
    }
  }

  scope->codeGen(destReg,context);

  cout<<"$EXIT_FUNC"<<to_string(context.getFunctionCounter())<<":"<<endl;

  context.loadLocalVariables();
  context.deallocateStack(8+stack_size);

  cout<<"\t"<<"j $31"<<endl;
  cout<<"\t"<<"nop" <<endl;
  cout<<endl<<"\t.set	macro"<<endl
	<<"\t.set	reorder"<<endl
	<<"\t.end	"<<id<<endl
	<<"\t.size	"<<id<<", .-"<<id<<endl;
}

FunctionCall::FunctionCall(const string &_id, Expression* _arguments):id(_id){
  arguments = _arguments;
}
void FunctionCall::add(Expression* _exp){
}
uint32_t FunctionCall::getSize(Context& context) const{
  if (arguments){
    return arguments->getSize(context);
  }
}
string FunctionCall::print(const bool& complete) const{
  stringstream ss;
  ss<<"<FunctionCall id=\""<<id<<"\">"<<endl;

  if (arguments){
    ss<<arguments->print(complete);
  }
  ss<<"</FunctionCall>"<<endl;
  return ss.str();
}
void FunctionCall::setType(const string &_type){}
string FunctionCall::getType() const{
  return "func_call";
}
string FunctionCall::getVal() const{
  return id;
}
void FunctionCall::codeGen(const string& destReg, Context& context){
  uint32_t stack_pointer = context.getStackPointer();
  //Especially for return address
  stack_pointer-=4;

  context.saveCurrentVariables();
  if (arguments){
    arguments->codeGen("parameters", context);
  }

  cout<<"\t"<<"sw	$31,"<<to_string(stack_pointer)<<"($sp)"<<endl;
  cout<<"\t"<<".option pic0"<<endl;
  cout<<"\t"<<"jal "<<id
  <<"\t #Branching for function call"
  <<endl;

  cout<<"\t"<<"nop"<<endl;
  cout<<"\t"<<".option	pic2"<<endl;
  context.loadCurrentVariables();
  cout<<"\t"<<"lw	$31,"<<to_string(stack_pointer)<<"($sp)"<<endl;
  if (destReg.compare("")!=0){
    cout<<"\t"<<"move "<<destReg<<",$2"<<endl;
  }
}

FunctionDec::FunctionDec(const string &_id, Expression* _parameters):id(_id){
  parameters = _parameters;
}
void FunctionDec::add(Expression* _exp){
}
uint32_t FunctionDec::getSize(Context& context) const{
  if (parameters){
    return parameters->getSize(context);
  }
}
string FunctionDec::print(const bool& complete) const{
  stringstream ss;
  ss<<"<FunctionDec id=\""<<id<<"\">"<<endl;
  if (parameters){
    ss<<parameters->print(complete);
  }
  ss<<"</FunctionDec>"<<endl;
  return ss.str();
}
void FunctionDec::setType(const string &_type){
  if (parameters){
    parameters->setType(_type);
  }
}
string FunctionDec::getType() const{
  return "func_dec";
}
string FunctionDec::getVal() const{
  return id;
}
void FunctionDec::codeGen(const string& destReg, Context& context){
}
