#ifndef ast_parameter_hpp
#define ast_parameter_hpp

#include <vector>
#include <sstream>
#include <string>

using namespace std;

class Parameter : public Expression {
private:
  string id;
public:
  Parameter(const string &_id): id(_id){}
  string print(const bool& complete) const{
    stringstream ss;
    ss<<"<Parameter id=\""<<id<<"\"/>";
    return ss.str();
  }
  void add(Expression* _exp){}
  string getType() const{
    return "param";
  }
  string getVal() const {
    return id;
  }
  bool isLeaf() const{
    return true;
  }
  bool isScopeEmpty() const {
    return true;
  }
};

class ParameterList: public Expression{
public:
  ParameterList(){}
  void add(Expression* _exp) override{
    parameters.push_back(_exp);
  }
  bool find(const string& id){
    for (Expression* exp: parameters){
      if(exp->getType()==id){
        return true;
      }
    }
    return false;
  }
  string print(const bool& complete) const{
    stringstream ss;
      for (Expression* exp: parameters){
        ss<<exp->print(complete);
      }
    return ss.str();
  }
  string getType() const{
    return "param_list";
  }
  bool isLeaf() const{
    return true;
  }
  bool isScopeEmpty() const {
    return parameters.empty();
  }
  string getVal() const{
    return "";
  }
private:
  vector<Expression*> parameters;
};

#endif
