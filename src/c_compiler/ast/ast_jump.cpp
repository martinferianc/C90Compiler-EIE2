#include "ast_jump.hpp"

Return::Return(Expression* _ret){
  ret = _ret;
}
void Return::add(Expression* _exp){}
uint32_t Return::getSize(Context& context) const{
  if(ret){
      return ret->getSize(context);
  }
  return 0;
}
string Return::print(const bool& complete) const{
  stringstream ss;
  if (ret){
    ss<<"<Return>"<<endl;
    ss<<ret->print(complete);
    ss<<"</Return>"<<endl;
  }
  return ss.str();
}
void Return::setType(const string &_type){}
string Return::getType() const{
  return "return";
}
string Return::getVal() const{
  return "";
}
void Return::codeGen(const string& destReg, Context& context){
  if(ret){
    cout<<"\t"<<"move $2,$0"<<endl;
    if ((ret->getType().compare("intCon")==0) || (ret->getType().compare("doubleCon")==0) || (ret->getType().compare("charCon")==0)){
      cout<<"\t"<<"li $2,"<<ret->getVal()<<endl;
    } else {
      ret->codeGen("$2", context);
    }
    cout<<"\t"<<"b $EXIT_FUNC"<<to_string(context.getFunctionCounter())<<endl;
    cout<<"\t"<<"nop"<<endl;
  }
}

Continue::Continue(){}
void Continue::add(Expression* _exp){}
uint32_t Continue::getSize(Context& context) const{
  return 0;
}
string Continue::print(const bool& complete) const{
  stringstream ss;
  ss<<"<Continue>"<<endl;
  ss<<"</Continue>"<<endl;
  return ss.str();
}
void Continue::setType(const string &_type){}
string Continue::getType() const{
  return "Continue";
}
string Continue::getVal() const{
  return "";
}
void Continue::codeGen(const string& destReg, Context& context){
    cout<<"\t"<<"b $UPDATE"<<to_string(context.getUpdateCounter())<<endl;
    cout<<"\t"<<"nop"<<endl;
}

Break::Break(){}
void Break::add(Expression* _exp){}
uint32_t Break::getSize(Context& context) const{
  return 0;
}
string Break::print(const bool& complete) const{
  stringstream ss;
  ss<<"<Break>"<<endl;
  ss<<"</Break>"<<endl;
  return ss.str();
}
void Break::setType(const string &_type){}
string Break::getType() const{
  return "Break";
}
string Break::getVal() const{
  return "";
}
void Break::codeGen(const string& destReg, Context& context){
    cout<<"\t"<<"b $EXIT"<<to_string(context.getLoopCounter())<<endl;
    cout<<"\t"<<"nop"<<endl;
}
