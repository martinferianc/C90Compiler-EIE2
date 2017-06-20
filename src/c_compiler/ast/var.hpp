#ifndef var_hpp
#define var_hpp

#include <string>
#include <stack>

using namespace std;

class Var{
public:
  Var(const string& _id, const string& _reg_id, const string& _type);
  string getVarId() const;
  string getRegId() const;
  string getFP(const bool& erase);
  string getType() const;
  size_t getSN(const bool& erase);
  size_t getSize() const;

  void setVarId(const string& _id);
  void setRegId(const string& _id);
  void setFP(const uint32_t& _fp);
  void setType(const string& _type);
  void setSN(const uint32_t& _sn);
  size_t getFPStackSize() const;
  size_t getSNStackSize() const;
private:
  string var_id;
  string type;
  string reg_id;
  stack<uint32_t> frame_pointer;
  stack<uint32_t> scope_number;
};

#endif
