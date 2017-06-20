#include "var.hpp"

Var::Var(const string& _id, const string& _reg_id, const string& _type)
    :var_id(_id),reg_id(_reg_id),type(_type){
    }
size_t Var::getSize() const{
  if (   (type.compare("char")==0) || (type.compare("unsigned char")==0)
      || (type.compare("signed char")==0)){
       return 1;
  }
  if (   (type.compare("int")==0)  || (type.compare("unsigned int")==0)
      || (type.compare("long")==0) || (type.compare("unsigned long")==0)){
       return 4;
  }
  if ((type.compare("short")==0) || (type.compare("unsigned short")==0)){
       return 2;
  }
  if (type.compare("float")==0){
       return 4;
  }
  if (type.compare("double")==0){
       return 8;
  }
  if (type.compare("long double")==0){
       return 10;
  }
  return 4;

}
string Var::getVarId() const {return var_id;}
string Var::getType() const{return type;}
string Var::getRegId() const {return reg_id;}
string Var::getFP(const bool& erase){
  string temp = to_string(frame_pointer.top());
  if (erase){
    frame_pointer.pop();
  }
  return temp;
}
size_t Var::getSN(const bool& erase){
  size_t temp = scope_number.top();
  if (erase){
    scope_number.pop();
  }
  return temp;
}
void Var::setVarId(const string& _id) {var_id = _id;}
void Var::setRegId(const string& _id)  {reg_id = _id;}
void Var::setFP(const uint32_t& _fp)    {
  frame_pointer.push(_fp);
}
void Var::setSN(const uint32_t& _sn)    {
  scope_number.push(_sn);
}
void Var::setType(const string& _type){
  type = _type;
}
size_t Var::getFPStackSize() const{
  return frame_pointer.size();
}
size_t Var::getSNStackSize() const{
  return scope_number.size();
}
