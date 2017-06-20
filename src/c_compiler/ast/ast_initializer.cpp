#include "ast_initializer.hpp"

InitializerList::InitializerList(){}
void InitializerList::add(Expression* _exp){
  initializers.push_back(_exp);
}
uint32_t InitializerList::getSize(Context& context) const{
  uint32_t sum = 0;
  for (Expression* par: initializers){
    sum+= par->getSize(context);
  }
  return sum;
}
string InitializerList::print(const bool& complete) const{
  stringstream ss;
  ss<<"<InitList>";
    for (Expression* exp: initializers){
      ss<<exp->print(complete);
    }
  ss<<"</InitList>";
  return ss.str();
}
void InitializerList::setType(const string &_type){
  for (Expression* exp: initializers){
    exp->setType(_type);
  }
}
string InitializerList::getType() const{
  return "init_list";
}
string InitializerList::getVal() const{
  return "";
}
void InitializerList::codeGen(const string& destReg, Context& context){
  for (size_t i = 0; i<initializers.size(); i++){
    string dest_reg = context.getReg(destReg);
    string fp = context.getVarAddress(destReg);
    string scratch_reg = context.getFreeRegister("");
    string scratch = context.makeLabel("scratch");
    context.makeBinding(scratch, scratch_reg, "scratch");
    cout<<"#new one"<<endl;
    cout<<"\t"<<"li "<<scratch_reg<<","<<to_string(i)<<endl;
    cout<<"\t"<<"move $t9, $0"<<endl;
    cout<<"\t"<<"addu "<<scratch_reg<<","<<scratch_reg<<",1"<<endl;
    cout<<"\t"<<"li $t9, 4"<<endl;
    cout<<"\t"<<"mult "<<scratch_reg<<",$t9"<<endl;
    cout<<"\t"<<"mflo "<<scratch_reg<<endl;
    cout<<"\t"<<"lw $t9,"<<fp<<"($fp)"<<endl;
    cout<<"\t"<<"addu "<<scratch_reg<<","<<scratch_reg<<",$t9"<<endl;
    initializers[i]->codeGen(dest_reg,context);
    cout<<"\t"<<"sw "<<dest_reg<<",0("<<scratch_reg<<")"<<endl;
    cout<<"\t"<<"move $t9, $0"<<endl;
    cout<<"\t"<<"move "<<scratch_reg<<", $0"<<endl;
    context.releaseBinding(scratch);
    cout<<"#new one"<<endl;
  }
}
