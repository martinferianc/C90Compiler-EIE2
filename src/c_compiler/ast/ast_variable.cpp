#include "ast_variable.hpp"

Variable::Variable(const string &_id): id(_id),type(""){}
string Variable::print(const bool& complete) const{
  stringstream ss;
  ss<<"<Variable id=\""<<id<<"\" type=\""<<type<<"\"/>"<<endl;
  return ss.str();
}
void Variable::add(Expression* _exp){}
uint32_t Variable::getSize(Context& context) const{
    return context.getSize(id);
}
void Variable::setType(const string &_type){
  type = _type;
}
string Variable::getType() const{
  return type;
}
string Variable::getVal() const{
  return id;
}
void Variable::codeGen(const string& destReg, Context& context){
    if(!(context.isInContext(id))){
      //This means that what the compiler sees is a DECLARATION
      if (   (type.compare("char")==0)          || (type.compare("unsigned char")==0)
          || (type.compare("signed char")==0)   || (type.compare("int")==0)
          || (type.compare("unsigned int")==0)        || (type.compare("long")==0)
          || (type.compare("unsigned long")==0)      || (type.compare("short")==0)
          || (type.compare("unsigned short")==0) || (type.compare("double")==0)
          || (type.compare("float")==0)
        ){
        //Might be an expression
        if (destReg.compare("global_expression")==0){
          cout<<"\t"<<".globl "<<id<<endl;
          cout<<"\t"<<".data"<<endl;
          cout<<"\t"<<".align 2"<<endl;
          cout<<"\t"<<".type "<<id<<", @object"<<endl;
          cout<<"\t"<<".size "<<id<<", 4"<<endl;
          cout<<id<<":"<<endl;
          cout<<"\t"<<".word 0"<<endl;
          cout<<"\t"<<".text"<<endl;
        } else if (destReg.compare("global")==0){
          cout<<"\t"<<".comm	"<<id<<",4,4"<<endl;
        } else {
          string reg1 = context.getFreeRegister("");
          context.makeBinding(id, reg1,type);
        }
      } else {
        //GLOBAL VARIABLE
        string reg_id = context.getFreeRegister("");
        context.makeBinding(id, reg_id,"global");
        if (destReg.compare("")!=0){
          context.loadVariable(id, destReg, false);
        }
      }
    } else {
      //REDECLARATION
      if (   (type.compare("char")==0)          || (type.compare("unsigned char")==0)
          || (type.compare("signed char")==0)   || (type.compare("int")==0)
          || (type.compare("unsigned int")==0)        || (type.compare("long")==0)
          || (type.compare("unsigned long")==0)      || (type.compare("short")==0)
          || (type.compare("unsigned short")==0) || (type.compare("double")==0)
          || (type.compare("float")==0)
        ){
        context.updateBinding(id,type);
      }
      if (destReg.compare("")!=0){
        cout<<"\t"<<"move "<<destReg<<","<<context.getReg(id)
        <<"\t #Moving var "<<id<<" to destination"
        <<endl;
      }
    }
}

VariableList::VariableList(){}
void VariableList::add(Expression* _exp) {
  variables.push_back(_exp);
}
uint32_t VariableList::getSize(Context& context) const{
  uint32_t sum = 0;
  for (Expression* var: variables){
    sum+= var->getSize(context);
  }
  return sum;
}
string VariableList::print(const bool& complete) const{
  stringstream ss;
    for (Expression* exp: variables){
      ss<<exp->print(complete);
    }
  return ss.str();
}
void VariableList::setType(const string &_type){
  for (Expression* exp: variables){
    exp->setType(_type);
  }
}
string VariableList::getType() const{
  return "variable_list";
}
string VariableList::getVal() const{
  return "";
}
void VariableList::codeGen(const string& destReg, Context& context){
  for (Expression* var: variables){
    var->codeGen(destReg,context);
  }
}
