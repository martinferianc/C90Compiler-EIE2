#include "ast_scope.hpp"

Scope::Scope(){}
void Scope::add(Expression* _sta){
  if (_sta){
    statements.push_back(_sta);
  }
}
uint32_t Scope::getSize(Context& context) const{
  uint32_t sum = 0;
  for (Expression* sta: statements){
    sum+= sta->getSize(context);
  }
  return sum;
}
string Scope::print(const bool& complete) const{
  stringstream ss;
  ss<<"<Scope>"<<endl;
    for (Expression* sta: statements){
      ss<<sta->print(complete);
    }
  ss<<"</Scope>"<<endl;
  return ss.str();
}
void Scope::setType(const string &_type){}
string Scope::getType() const{
  return "scope";
}
string Scope::getVal() const{
  return "";
}
void Scope::codeGen(const string& destReg, Context& context){
  context.incrementScopeCounter();
  for (Expression* sta: statements){
    sta->codeGen(destReg,context);
  }
  context.clearScopeContext();
  context.decrementScopeCounter();
}
