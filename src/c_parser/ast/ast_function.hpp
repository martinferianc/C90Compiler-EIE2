#ifndef ast_function_hpp
#define ast_function_hpp

#include <string>
#include <sstream>

using namespace std;

class Function: public Expression{
public:
  Function(const string &_id, ParameterList* _parameters, Expression* _scope):id(_id){
    parameters = _parameters;
    scope = _scope;
  }
  void add(Expression* _exp){
    if (!(parameters->find(_exp->getVal()))){
      scope->add(_exp);
    }
  }
  string print(const bool& complete) const{
    stringstream ss;
    ss<<"<Function id=\""<<id<<"\">"<<endl;
    if(parameters){
      ss<<parameters->print(complete);
    }
    if (scope){
      ss<<scope->print(complete);
    }
    ss<<"</Function>";
    return ss.str();
  }
  string getType() const{
    return "func";
  }
  bool isLeaf() const{
    return false;
  }
  bool isScopeEmpty() const {
    return scope->isScopeEmpty();
  }
  string getVal() const{
    return id;
  }
private:
  string id;
  ParameterList* parameters;
  Expression* scope;
};

class FunctionCall:public Expression{
public:
  FunctionCall(const string &_id, Expression* _arguments):id(_id){
    arguments = _arguments;
  }
  void add(Expression* _exp){
  }
  string print(const bool& complete) const{
    stringstream ss;
    if (complete){
      ss<<"<Function Call id=\""<<id<<"\"/>"<<endl;
    }
    return ss.str();
  }
  string getType() const{
    return "funccall";
  }
  bool isLeaf() const{
    return true;
  }
  bool isScopeEmpty() const {
    return true;
  }
  string getVal() const{
    return id;
  }
private:
  string id;
  Expression* arguments;
};


#endif
