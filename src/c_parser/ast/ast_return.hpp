#ifndef ast_return_hpp
#define ast_return_hpp

class Return: public Expression{
public:
  Return(Expression* _ret){
    ret = _ret;
  }
  void add(Expression* _exp){}
  string print(const bool& complete) const{
    stringstream ss;
    if ((complete) && (ret)){
      ss<<"<Return>"<<endl;
      ss<<ret->print(complete)<<endl;
      ss<<"</Return>"<<endl;
    }
    return ss.str();
  }
  bool isLeaf() const {
    return false;
  }
  bool isScopeEmpty() const {
    if (ret)
      return false;
    else
      return true;
  }
  string getType() const{
    return "return";
  }
  string getVal() const{
    return "";
  }
private:
  Expression* ret;
};
#endif
