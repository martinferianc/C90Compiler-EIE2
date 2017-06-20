#include "ast_argument.hpp"

ArgumentList::ArgumentList(){}
void ArgumentList::add(Expression* _exp){
  arguments.push_back(_exp);
}
uint32_t ArgumentList::getSize(Context& context) const{
  uint32_t sum = 0;
  for (Expression* arg: arguments){
    sum+= arg->getSize(context);
  }
  return sum;
}
string ArgumentList::print(const bool& complete) const{
  stringstream ss;
    for (Expression* exp: arguments){
      ss<<exp->print(complete);
    }
  return ss.str();
}
void ArgumentList::setType(const string &_type){}
string ArgumentList::getType() const{
  return "argument_list";
}
string ArgumentList::getVal() const{
  return "";
}
void ArgumentList::codeGen(const string& destReg, Context& context){
  vector<string> args;
  vector<string> scratch_reg;
  vector<string> scratch_id;

  for (Expression* exp: arguments){
    string arg = context.getFreeRegister(to_string(args.size()));
    string reg = context.getFreeRegister("");
    string scratch = context.makeLabel("scratch");
    context.makeBinding(scratch, reg, "scratch");
    exp->codeGen(reg, context);
    args.push_back(arg);
    scratch_reg.push_back(reg);
    scratch_id.push_back(scratch);
  }
  for (size_t i = 0; i<args.size(); i++){
    cout<<"\t"<<"move "<<args[i]<<","<<scratch_reg[i]<<endl;
    context.releaseBinding(scratch_id[i]);
  }
}
