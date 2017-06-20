#include "reg.hpp"

Reg::Reg(const string& _reg_id):reg_id(_reg_id){
  frame_pointer = -1;
}
string Reg::getFP() const{
  return to_string(frame_pointer);
}
void Reg::setFP(const uint32_t& _fp){
  frame_pointer = _fp;
}
string Reg::getVarId() const {
  return var_id;
}
void Reg::setVarId(const string& _var_id){
  var_id = _var_id;
}
void Reg::setRegId(const string& _reg_id){
  reg_id = _reg_id;
}
string Reg::getRegId() const {
  return reg_id;
}
bool Reg::isFree() const {
  if (var_id.compare("")==0){
    return true;
  } else {
    return false;
  }
}
