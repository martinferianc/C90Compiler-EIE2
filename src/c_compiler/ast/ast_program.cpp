#include "ast_program.hpp"

Program::Program(){}
void Program::add(Expression* _exp){
  if (_exp){
    statements.push_back(_exp);
  }
}
uint32_t Program::getSize(Context& context) const{
  uint32_t sum = 0;
  for (Expression* sta: statements){
    sum+= sta->getSize(context);
  }
  return sum;
}
string Program::print(const bool& complete) const{
  stringstream ss;
  if (statements.size()>=1){
    ss<<"<?xml version=\"1.0\"?>"<<"<Program>"<<endl;
    for (Expression* exp: statements){
      ss<<exp->print(complete);
    }
    ss<<"</Program>"<<endl;
  }
  return ss.str();
}
void Program::setType(const string &_type){}
string Program::getType() const{
  return "prog";
}
string Program::getVal() const{
  return "";
}
void Program::codeGen(const string& destReg, Context& context){
  for (Expression* exp: statements){
    if (exp->getType().compare("variable_list")==0){
      exp->codeGen("global", context);
      continue;
    }
    exp->codeGen("", context);
  context.clearContext();
  }
}
