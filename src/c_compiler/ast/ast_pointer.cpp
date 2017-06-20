#include "ast_pointer.hpp"

Pointer::Pointer(Expression* exp){
  id = exp->getVal();
  type = exp->getType();
}

string Pointer::print(const bool& complete) const{
  stringstream ss;
  ss<<"<Pointer id=\""<<id<<"\" type=\""<<type<<"\"/>"<<endl;
  return ss.str();
}
void Pointer::add(Expression* _exp){}
uint32_t Pointer::getSize(Context& context) const{
    return context.getSize(id);
}
void Pointer::setType(const string &_type){
  type = _type;
}
string Pointer::getType() const{
  return "pointer";
}
string Pointer::getVal() const{
  return id;
}
void Pointer::codeGen(const string& destReg, Context& context){
    if(!(context.isInContext(id))){
      //This means that what the compiler sees is a DECLARATION
      if (   (type.compare("char")==0)          || (type.compare("unsigned char")==0)
          || (type.compare("signed char")==0)   || (type.compare("int")==0)
          || (type.compare("unsigned int")==0)        || (type.compare("long")==0)
          || (type.compare("unsigned long")==0)      || (type.compare("short")==0)
          || (type.compare("unsigned short")==0) || (type.compare("double")==0)
          || (type.compare("float")==0)
        ){
          string reg1 = context.getFreeRegister("");
          context.makeBinding(id, reg1,"pointer");
          cout<<"\t"<<"#Making Pointer Binding "<<id
          <<endl;
        }
    } else {
      //REDECLARATION
      if (   (type.compare("char")==0)          || (type.compare("unsigned char")==0)
          || (type.compare("signed char")==0)   || (type.compare("int")==0)
          || (type.compare("unsigned int")==0)        || (type.compare("long")==0)
          || (type.compare("unsigned long")==0)      || (type.compare("short")==0)
          || (type.compare("unsigned short")==0) || (type.compare("double")==0)
          || (type.compare("float")==0)){
        context.updateBinding(id,"pointer");
      }
      if (destReg.compare("")!=0){
        cout<<"\t"<<"move "<<destReg<<","<<context.getReg(id)
        <<"\t #Moving var "<<id<<" to destination"
        <<endl;
      }
    }
}

Reference::Reference(Expression* exp){
  id= exp->getVal();
}
string Reference::print(const bool& complete) const{
  stringstream ss;
  ss<<"<Reference id=\""<<id<<"\"/>"<<endl;
  return ss.str();
}
void Reference::add(Expression* _exp){}
uint32_t Reference::getSize(Context& context) const{
    return context.getSize(id);
}
void Reference::setType(const string &_type){}
string Reference::getType() const{
  return "reference";
}
string Reference::getVal() const{
  return id;
}
void Reference::codeGen(const string& destReg, Context& context){}
