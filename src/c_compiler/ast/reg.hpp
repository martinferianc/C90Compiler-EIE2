#ifndef reg_hpp
#define reg_hpp

#include <string>

using namespace std;

class Reg{
public:
  Reg(const string& _reg_id);

  void setVarId(const string& _var_id);
  void setRegId(const string& _reg_id);
  void setFP(const uint32_t& _fp);
  
  string getVarId() const;
  string getFP() const;
  string getRegId() const;
  bool isFree() const;
private:
  string var_id;
  string reg_id;
  uint32_t frame_pointer;
};

#endif
