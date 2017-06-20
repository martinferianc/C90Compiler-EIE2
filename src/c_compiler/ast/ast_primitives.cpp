#include "ast_primitives.hpp"

  NumberDouble::NumberDouble(const double &_val): val(_val){}
  void NumberDouble::add(Expression* _exp){}
  uint32_t NumberDouble::getSize(Context& context) const{
    return 8;
  }
  string NumberDouble::print(const bool& complete) const{
    stringstream ss;
      ss<<"<NumberDouble value=\""<<val<<"\">"<<endl;
      ss<<"</NumberDouble>"<<endl;
    return ss.str();
  }
  string NumberDouble::getVal() const{
    ostringstream strs;
    strs << val;
    return strs.str();
  }
  string NumberDouble::getType() const{
    return "doubleCon";
  }
  void NumberDouble::setType(const string &_type){}
  void NumberDouble::codeGen(const string& destReg, Context& context){
    cout<<"\t"<<"li "<<destReg<<","<<to_string(int(val))
    <<"\t #Value to register "<<to_string(val)
    <<endl;
  }

  NumberInt::NumberInt(const int &_val): val(_val){}
  string NumberInt::print(const bool& complete) const{
    stringstream ss;
      ss<<"<NumberInt value=\""<<val<<"\">"<<endl;
      ss<<"</NumberInt>"<<endl;
    return ss.str();
  }
  void NumberInt::add(Expression* _exp){}
  uint32_t NumberInt::getSize(Context& context) const{
    return 4;
  }
  string NumberInt::getType() const{
    return "intCon";
  }
  void NumberInt::setType(const string &_type){}
  string NumberInt::getVal() const{
    ostringstream strs;
    strs << val;
    return strs.str();
  }
  void NumberInt::codeGen(const string& destReg, Context& context){
    cout<<"\t"<<"li "<<destReg<<","<<to_string(val)
    <<"\t #Value to register "<<to_string(val)
    <<endl;
  }

  Char::Char(const string &_val){
    val = _val.c_str();
  }
  string Char::print(const bool& complete) const{
    stringstream ss;
    ss<<"<Char value=\""<<string(val)<<"\">"<<endl;
    ss<<"</Char>"<<endl;
    return ss.str();
  }
  void Char::add(Expression* _exp){}
  uint32_t Char::getSize(Context& context) const{
    return 4;
  }
  string Char::getType() const{
    return "charCon";
  }
  void Char::setType(const string &_type){}
  string Char::getVal() const{
    string input = string(val);
    size_t i = input.find("\'", 0);
    size_t j = input.find("\'", i+1);
    if ((i!=string::npos) && (j!=string::npos)){
      input = input.erase(j,input.length());
      input = input.substr(i+1,j-1);
    }
    char c = input.back();
    return to_string(int(c));
  }
  void Char::codeGen(const string& destReg, Context& context){
    cout<<"\t"<<"li "<<destReg<<","<<getVal()
    <<"\t #Char to register "<<string(val)
    <<endl;
  }

  String::String(const string &_val){
    val = _val;
  }
  string String::print(const bool& complete) const{
    stringstream ss;
    ss<<"<String value=\""<<string(val)<<"\">"<<endl;
    ss<<"</String>"<<endl;
    return ss.str();
  }
  void String::add(Expression* _exp){}
  uint32_t String::getSize(Context& context) const{
    return 4;
  }
  string String::getType() const{
    return "StringCon";
  }
  void String::setType(const string &_type){}
  string String::getVal() const{
    /*
    string input = string(val);
    size_t i = input.find("\'", 0);
    size_t j = input.find("\'", i+1);
    if ((i!=string::npos) && (j!=string::npos)){
      input = input.erase(j,input.length());
      input = input.substr(i+1,j-1);
    }
    String c = input.back();
    return to_string(int(c));
    */
  }
  void String::codeGen(const string& destReg, Context& context){
    /*
    cout<<"\t"<<"li "<<destReg<<","<<getVal()
    <<"\t #String to register "<<string(val)
    <<endl;
    */
  }
