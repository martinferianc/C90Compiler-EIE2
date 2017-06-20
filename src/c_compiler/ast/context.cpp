#include "context.hpp"

using namespace std;

Context::Context(){
  for (size_t i = 0; i<32; i++){
    Reg r("");
    registers.push_back(r);
    r.setFP(-1);
  }
  registers[0].setRegId("$zero");
  registers[1].setRegId("$at");
  registers[2].setRegId("$v0");
  registers[3].setRegId("$v1");
  registers[4].setRegId("$a0");
  registers[5].setRegId("$a1");
  registers[6].setRegId("$a2");
  registers[7].setRegId("$a3");
  for (size_t i = 1; i <=8; i++) {
    registers[7+i].setRegId("$t"+to_string(i-1));
  }
  for (size_t i = 1; i <=8; i++) {
    registers[15+i].setRegId("$s"+to_string(i-1));
  }
  registers[24].setRegId("$t8");
  registers[25].setRegId("$t8");
  registers[26].setRegId("$k0");
  registers[27].setRegId("$k1");
  registers[28].setRegId("$gp");
  registers[28].setRegId("$sp");
  registers[30].setRegId("$fp");
  registers[31].setRegId("$ra");
  scope_counter = 0;
  stack_pointer = 0;
  label_counter = 0;
  frame_pointer = 0;
  function_counter = 0;
  list_counter = 0;
  loop_counter = 0;
  case_counter = 0;
  update_counter = 0;
}

string Context::getFreeRegister(const string& parameter_flag){
  uint32_t index = -1;
  if (parameter_flag == "parameter"){
    for (size_t i = 4; i <= 7; i++) {
      if(registers[i].isFree()){
        index = i;
        break;
      }
    }
  }
  // Hack for arguments :( very sad
  if (parameter_flag == "0"){index = 4;}
  if (parameter_flag == "1"){index = 5;}
  if (parameter_flag == "2"){index = 6;}
  if (parameter_flag == "3"){index = 7;}
  if (parameter_flag == ""){
    for (size_t i = 8; i <= 24; i++) {
      if(registers[i].isFree()){
        index = i;
        break;
      }
    }
  }
  if (parameter_flag == "all"){
    for (size_t i = 4; i <= 24; i++) {
      if(registers[i].isFree()){
        index = i;
        break;
      }
    }
  }
  if ((index>=16)&&(index<=23)){
    //These registers have to be saved according to the convention, only one necessry address
    string reg_id = registers[index].getRegId();
    if (registers[index].getFP().compare("4294967295")==0){
      registers[index].setFP(frame_pointer);
      cout<<"\t"<<"sw "<<reg_id<<","<<frame_pointer<<"($fp)"
      <<"\t"<<"#Saving temporary to be restored"<<endl;
      frame_pointer+=4;
    }
  }
  if (index!=4294967295){
    //We have found a free register!
    return registers[index].getRegId();
  }

  //Find the minimum scope number and function number,
  //probably it is least used
  size_t not_used = 0;
  for (size_t i = 0; i<variables.size(); i++) {
    if (variables[not_used].getFPStackSize()>variables[i].getFPStackSize()){
      not_used = i;
    }
  }
  //Fetch the unused variable and store it in memory
  string reg_id = variables[not_used].getRegId();
  string var_id = variables[not_used].getVarId();
  variables[not_used].setFP(frame_pointer);
  frame_pointer+=4;
  saveVariable(var_id,false);
  for (size_t i = 8; i <= 24; i++) {
    if (registers[i].getRegId().compare(reg_id) == 0){
        registers[i].setVarId("");
      }
    }
  //Set the variable to sleep
  variables[not_used].setRegId("");

  //Release the binding for now
  map<string,string>::iterator it;
  it = bindings.find(var_id);
  bindings.erase(it);

  return reg_id;
}
bool Context::isInContext(const string& var_id){
  //Find the variable if it is in the current scope
  map<string,string>::iterator it;
  it = bindings.find(var_id);
  if (it != bindings.end()){
    for (size_t i = 0; i<variables.size(); i++){
      if ((variables[i].getVarId().compare(var_id)==0)
          &&(variables[i].getRegId().compare("")!=0)){
        return true;
      }
    }
  } else {
    //Otherwise try to fetch it from memory
    string var_name = "";
    uint32_t var_index = 0;
    for (size_t i = 0; i < variables.size(); i++) {
      if (variables[i].getVarId() == var_id){
        var_name = variables[i].getVarId();
        var_index = i;
      }
    }
    //If found in memory, then bind it to a new free register
    if(var_name.compare("")!=0){
      string reg_id = getFreeRegister("");
      loadVariable(var_id, reg_id,true);
      //Update the binding and register vector
      bindings[var_id] = reg_id;
      for (size_t i = 0; i <= 31; i++) {
        if (registers[i].getRegId() == reg_id){
          registers[i].setVarId(var_id);
        }
      }
      //Update the variables vector as well
      variables[var_index].setRegId(reg_id);
      return true;
    } else {
      //Not found at all
      return false;
    }
  }
}
void Context::saveVariable(const string& var_id, const bool& erase){
  for (size_t i = 0; i < variables.size(); i++) {
    if ((variables[i].getVarId().compare(var_id)==0)&&(variables[i].getFP(false).compare("4294967295")!=0)
        &&(variables[i].getType().compare("scratch")!=0)){
        string frame_pointer = variables[i].getFP(erase);
        cout<<"\t"<<"sw "<<bindings[variables[i].getVarId()]<<","<<frame_pointer<<"($fp)"
        <<"\t #Saving variable: "<<variables[i].getVarId()<<endl;
        continue;
    }
    if ((variables[i].getVarId().compare(var_id)==0)&&(variables[i].getType().compare("global")==0)){
      cout<<"\t"<<"move $t9,$0"<<endl;
      cout<<"\t"<<"lui $t9,"<<"%hi("<<variables[i].getVarId()<<")"<<endl;
      cout<<"\t"<<"sw "<<bindings[variables[i].getVarId()]
      <<",%lo("<<variables[i].getVarId()<<")"
      <<"($t9)"<<endl;
      cout<<"\t"<<"move $t9,$0"<<endl;
    }
  }
}


void Context::loadVariable(const string& var_id, const string& reg_id, const bool& erase){
  for (size_t i = 0; i < variables.size(); i++) {
    if ((variables[i].getVarId().compare(var_id)==0)&&(variables[i].getFP(false).compare("4294967295")!=0)
        &&(variables[i].getType().compare("scratch")!=0)&&(variables[i].getType().compare("array")!=0)){
        string frame_pointer = variables[i].getFP(erase);
        cout<<"\t"<<"lw "<<reg_id<<","<<frame_pointer<<"($fp)"
        <<"\t #Loading variable: "<<variables[i].getVarId()<<endl;
        continue;
    }
    if ((variables[i].getVarId().compare(var_id)==0)&&(variables[i].getType().compare("global")==0)){
      cout<<"\t"<<"move $t9,$0"<<endl;
      cout<<"\t"<<"lui $t9,"<<"%hi("<<var_id<<")"<<endl;
      cout<<"\t"<<"lw "<<reg_id<<","<<"%lo("<<var_id<<")"<<"($t9)"<<endl;
      cout<<"\t"<<"move $t9,$0"<<endl;
    }
  }
}


void Context::makeBinding(const string& var_id, const string& reg_id, const string& type){
    bindings[var_id] = reg_id;
    for (size_t i = 0; i <= 31; i++) {
      if (registers[i].getRegId().compare(reg_id)==0){
        registers[i].setVarId(var_id);
      }
    }
    //Create the new variable and set parameters
    Var v(var_id, reg_id, type);
    if ((type.compare("pointer")!=0)&&
        (type.compare("scratch")!=0)&&
        (type.compare("global")!=0)){

      if ((reg_id.compare("$a0")!=0) &&
          (reg_id.compare("$a1")!=0) &&
          (reg_id.compare("$a2")!=0) &&
          (reg_id.compare("$a3")!=0) &&
          (type.compare("array")!=0)){
            cout<<"\t"<<"move "<<reg_id<<",$0"
            <<"\t #Making Binding "<<var_id
            <<endl;
          }
      v.setFP(frame_pointer);
      frame_pointer+=4;
    } else {
      v.setFP(-1);
    }
    v.setSN(scope_counter);
    variables.push_back(v);
    if (type.compare("global")!=0){
      saveVariable(var_id,false);
    }
 }
void Context::updateBinding(const string& var_id, const string& type){
  string reg = bindings[var_id];
  for (size_t i = 0; i < variables.size(); i++) {
    if (variables[i].getVarId().compare(var_id)==0){
        variables[i].setFP(frame_pointer);
        variables[i].setSN(scope_counter);
    }
  }
  //Save the register to memory so it can be reallocated
  cout<<"\t"<<"move "<<reg<<",$0"
  <<"\t #Updating binding: "<<var_id
  <<endl;
  saveVariable(var_id, false);
  frame_pointer+=4;
}
void Context::releaseBinding(const string& var_id){
  //Try to release a var reg binding
  map<string,string>::iterator it;
  it = bindings.find(var_id);
  if (it == bindings.end()){
    // The variable does not have a binding
    return;
  }
  // Find the register which holds the binding
  for (size_t i = 0; i <= 31; i++) {
    if (registers[i].getRegId() == bindings[var_id]){
      registers[i].setVarId("");
    }
  }
  //Find the variable in binding
  for (size_t i = 0; i < variables.size(); i++) {
    if (variables[i].getVarId() == var_id){
      variables.erase(variables.begin()+i);
    }
  }
  it = bindings.find(var_id);
  bindings.erase(it);
}
string Context::getReg(const string& var_id){
  //Try to find the register which holds the variable
  map<string,string>::iterator it;
  it = bindings.find(var_id);
  if (it!= bindings.end()){
    if (isInContext(var_id)){
      loadVariable(var_id, bindings[var_id], false);
      return bindings[var_id];
    }
  }
}
string Context::getVarAddress(const string& var_id){
  for (size_t i = 0; i < variables.size(); i++) {
    if (variables[i].getVarId() == var_id){
      return variables[i].getFP(false);
    }
  }
}

void Context::setVarAddress(const string& var_id,const string& fp){
  for (size_t i = 0; i < variables.size(); i++) {
    if (variables[i].getVarId() == var_id){
      variables[i].getFP(true);
      variables[i].setFP(atoi(fp.c_str()));
    }
  }
}
string Context::getVarType(const string& var_id){
  for (size_t i = 0; i < variables.size(); i++) {
    if (variables[i].getVarId() == var_id){
      return variables[i].getType();
    }
  }
}
void Context::allocateStack(const int32_t& val){
  //Allocate stack
  cout<<"\t"<<"addiu $sp,$sp,"<<to_string(-1*(val + stack_pointer))<<endl;
  cout<<"\t"<<"sw $31,"<<to_string(val+ stack_pointer-4)<<"($sp)"
  <<"\t"<<"# Storing return address"<<endl;
  cout<<"\t"<<"sw $fp,"<<to_string(val+ stack_pointer-8)<<"($sp)"
  <<"\t"<<"# Storing current frame pointer"<<endl;
  cout<<"\t"<<"move $fp,$sp"<<endl;
  stack_pointer+= val;
  //Reset the frame pointer
  frame_pointer=0;

}
void Context::deallocateStack(const int32_t& val){
  cout<<"\t"<<"move $sp,$fp"<<endl;
  cout<<"\t"<<"lw $fp,"<<to_string(stack_pointer-8)<<"($sp)"
  <<"\t"<<"# Loading current frame pointer"<<endl;
  cout<<"\t"<<"lw $31,"<<to_string(stack_pointer-4)<<"($sp)"
  <<"\t"<<"# Loading return address"<<endl;
  cout<<"\t"<<"addiu $sp,$sp,"<<to_string(stack_pointer)<<endl;
  //Reset again the frame pointer
  frame_pointer=0;
}
void Context::clearContext(){
  //Completerly clear context after a function
  bindings.clear();
  variables.clear();
  for (size_t i = 0; i <= 31; i++) {
    registers[i].setVarId("");
    registers[i].setFP(-1);
  }
  scope_counter = 0;
  frame_pointer = 0;
}
void Context::clearScopeContext(){
  //Iterate through the current scope and clear all bindings for that scope
  map<string, string>::iterator it;
  for (it = bindings.begin(); it != bindings.end(); it++){
    string var_id = string(it->first);
    for (size_t i = 0; i<variables.size(); i++){
      if ((variables[i].getVarId() == var_id)
      && (variables[i].getSN(false)==scope_counter)
      && (variables[i].getFPStackSize()==1)){
        //Does not need to be loaded
        cout<<"\t #Releasing binding: "<<var_id<<endl;
        releaseBinding(var_id);
        continue;
      }
      //Comparing with -1
      if ((variables[i].getSN(false)==scope_counter)
      &&  (variables[i].getFPStackSize()!=1)
      &&  (variables[i].getRegId().compare("")!=0)){
        string reg = bindings[variables[i].getVarId()];
        //Load all the values from memory which were previously deallocated
        loadVariable(variables[i].getVarId(), bindings[variables[i].getVarId()], true);
        variables[i].getSN(true);
      }
      if ((variables[i].getSN(false)>scope_counter)){
        cout<<"\t # Decrementing SN, FP"<<endl;
        variables[i].getSN(true);
        variables[i].getFP(true);

      }
    }
  }
  cout<<"\t #==Clearing scope context=="<<endl;
}

void Context::saveCurrentVariables(){
  cout<<"\t #==Saving current variables=="<<endl;
  for (size_t i = 4; i<=30; i++){
    string reg_id = registers[i].getRegId();
    if (registers[i].getVarId()!=""){
      cout<<"\t"<<"sw "<<reg_id<<","<<to_string(frame_pointer)<<"($fp)"<<endl;
      frame_pointer+=4;
    }
  }
}
void Context::loadCurrentVariables(){
  cout<<"\t #==Loading current variables=="<<endl;
  for (size_t i = 30; i>=4; --i){
    string reg_id = registers[i].getRegId();
    if (registers[i].getVarId()!=""){
      frame_pointer-=4;
      cout<<"\t"<<"lw "<<reg_id<<","<<to_string(frame_pointer)<<"($fp)"<<endl;
    }
  }
}
void Context::loadLocalVariables(){
  cout<<"\t #==Loading used variables 16-23=="<<endl;
  for (size_t i=16; i<=23; i++){
    if (registers[i].getFP().compare("4294967295")!=0){
      string reg_id = registers[i].getRegId();
      string r_frame_pointer = registers[i].getFP();
      cout<<"\t"<<"lw "<<reg_id<<","<<r_frame_pointer<<"($fp)"<<endl;
      registers[i].setFP(-1);
    }
  }
}
void Context::saveGlobalExpression(Expression* _exp){
  global.push_back(_exp);
}
void Context::loadGlobalExpression(vector<Expression*> &v){
  v = global;
}
uint32_t Context::getSize(const string& _id){
  for (size_t i = 0; i<variables.size(); i++){
    if (variables[i].getVarId().compare(_id)==0){
      return variables[i].getSize();
    }
  }
  return 4;
}
uint32_t Context::setFramePointer(const uint32_t& fp){      frame_pointer = fp;}
uint32_t Context::getFramePointer(){                        return frame_pointer;}
int32_t Context::getStackPointer(){                         return stack_pointer;}
void Context::incrementScopeCounter(){                      scope_counter++;}
void Context::decrementScopeCounter(){                      scope_counter--;}
uint32_t Context::getFunctionCounter(){                     return function_counter;}
void Context::incrementFunctionCounter(){                   function_counter++; }
void Context::decrementFunctionCounter(){                   function_counter--; }
uint32_t Context::getLoopCounter(){                         return loop_counter;  }
void Context::incrementLoopCounter(){                       loop_counter++; }
void Context::decrementLoopCounter(){                       loop_counter--; }
uint32_t Context::getUpdateCounter(){                       return update_counter;  }
void Context::incrementUpdateCounter(){                     update_counter++; }
void Context::decrementUpdateCounter(){                     update_counter--; }
uint32_t Context::getListCounter(){                         return list_counter;}
void Context::incrementListCounter(){                       list_counter++; }
void Context::decrementListCounter(){                       list_counter--; }
uint32_t Context::getCaseCounter(){                         return case_counter;}
void Context::incrementCaseCounter(){                       case_counter++; }
void Context::decrementCaseCounter(){                       case_counter--; }
string Context::makeLabel(string base){
  label_counter++;
  return "$"+base+to_string(label_counter);
}
