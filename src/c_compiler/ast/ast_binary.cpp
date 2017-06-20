#include "ast_binary.hpp"

BinaryExpression::BinaryExpression(Expression* _left, const string& _op, Expression* _right){
  if (_left){
    left = _left;
  }
  if (_right){
    right = _right;
  }
  op = _op;
}
void BinaryExpression::add(Expression* _exp){}
uint32_t BinaryExpression::getSize(Context& context) const{
  if (right && left){
    return left->getSize(context) + right->getSize(context);
  } else {
    if (left){
      return left->getSize(context);
    }
  }
  return 0;
}
string BinaryExpression::print(const bool& complete) const{
  stringstream ss;
    ss<<"<BinaryExpression>"<<endl;
    ss<<"<Left>"<<endl;
    ss<<left->print(complete);
    ss<<"</Left>"<<endl;
    ss<<"<Operator op = \""<<op<<"\"/>"<<endl;
    if (right){
      ss<<"<Right>"<<endl;
      ss<<right->print(complete);
      ss<<"</Right>"<<endl;
    }
  ss<<"</BinaryExpression>"<<endl;
  return ss.str();
}

void BinaryExpression::setType(const string &_type){
  if (left){
    left->setType(_type);
  }
}
string BinaryExpression::getType() const{
  return "binexp";
}
string BinaryExpression::getVal() const{
  return "";
}
void BinaryExpression::codeGen(const string& destReg, Context& context){
  if (destReg.compare("global")==0){
    left->codeGen("global_expression", context);
    left->setType("");
    context.saveGlobalExpression(this);
  } else {
  string reg1 = "";
  string reg2 = "";

  // Assignment operations
  if    ((op.compare("=")==0)  || (op.compare("-=")==0)  || (op.compare("+=")==0)  || (op.compare("/=")==0)
      || (op.compare("%=")==0) || (op.compare("<<=")==0) || (op.compare(">>=")==0) || (op.compare("^=")==0)
      || (op.compare("&=")==0) || (op.compare("|=")==0)  || (op.compare("*=")==0)  || (op.compare("++")==0)
      || (op.compare("--")==0)){
    //Left side of expression

    left->codeGen("", context);
    reg1 = context.getReg(left->getVal());


    //Right side of expression, if there is one
    if (right){
      if (right->getType().compare("init_list")!=0){
        reg2 = context.getFreeRegister("");
        string scratch_id = context.makeLabel("scratch");
        context.makeBinding(scratch_id, reg2,"scratch");
        right->codeGen(reg2, context);
        context.releaseBinding(scratch_id);
      }
    }
    /* ASSIGNMENT EXPRESSIONS */
    if (op.compare("=")==0){
      //Compare if on the left side is a pointer
      if ((context.getVarType(left->getVal()).compare("pointer")==0)
          && (left->getType().compare("pointer")!=0)){
        string frame_pointer = context.getVarAddress(right->getVal());
        if (context.getVarType(right->getVal()).compare("array")==0){
          uint32_t temp = atoi(frame_pointer.c_str()) + 4;
          frame_pointer = to_string(temp);
        }
        context.setVarAddress(left->getVal(), frame_pointer);
      } else {
        if (right->getType().compare("init_list")!=0){
          cout<<"\t"<<"move "<<reg1<<","<<reg2
          <<"\t #Assigning value "
          <<endl;
        } else {
          right->codeGen(left->getVal(), context);
        }
      }
    }
    if (op.compare("+=")==0){
      cout<<"\t"<<"add "<<reg1<<","<<reg1<<","<<reg2
      <<"\t #Assigning and Adding a value "
      <<endl;
    }
    if (op.compare("-=")==0){
      cout<<"\t"<<"sub "<<reg1<<","<<reg1<<","<<reg2
      <<"\t #Assigning and Subtracting a value "
      <<endl;
    }
    if (op.compare("--")==0){
      cout<<"\t"<<"sub "<<reg1<<","<<reg1<<", 1"
      <<"\t #Subtracting a 1 -- "
      <<endl;
    }
    if (op.compare("<<=")==0){
      cout<<"\t"<<"sll "<<reg1<<","<<reg1<<","<<reg2
      <<"\t #Assigning and Shifting left a value "
      <<endl;
    }
    if (op.compare("++")==0){
      cout<<"\t"<<"addi "<<reg1<<","<<reg1<<", 1"
      <<"\t #Adding a 1 ++ "
      <<endl;
    }
    if (op.compare(">>=")==0){
      cout<<"\t"<<"sra "<<reg1<<","<<reg1<<","<<reg2
      <<"\t #Assigning and Shifting right a value "
      <<endl;
    }
    if (op.compare("&=")==0){
      cout<<"\t"<<"and "<<reg1<<","<<reg1<<","<<reg2
      <<"\t #Assigning and Anding a value "
      <<endl;
    }
    if (op.compare("|=")==0){
      cout<<"\t"<<"or "<<reg1<<","<<reg1<<","<<reg2
      <<"\t #Assigning and Oring a value "
      <<endl;
    }
    if (op.compare("^=")==0){
      cout<<"\t"<<"xor "<<reg1<<","<<reg1<<","<<reg2
      <<"\t #Assigning and Xoring a value "
      <<endl;
    }
    if (op.compare("*=")==0){
      cout<<"\t"<<"mult "<<reg1<<","<<reg2
      <<"\t #Multypling values "
      <<endl;
      cout<<"\t"<<"mflo "<<reg1
      <<"\t #Fetching from LO and storing in destination "
      <<endl;
    }
    if (op.compare("/=")==0){
      cout<<"\t"<<"div "<<reg1<<","<<reg2
      <<"\t #Divide values "
      <<endl;
      cout<<"\t"<<"mflo "<<reg1
      <<"\t #Fetching from LO and storing in destination "
      <<endl;
    }
    if (op.compare("%=")==0){
      cout<<"\t"<<"div "<<reg1<<","<<reg2
      <<"\t #Divide values "
      <<endl;
      cout<<"\t"<<"mfhi "<<reg1
      <<"\t #Fetching from HI and storing in destination "
      <<endl;
    }
    //Only assign if there is need for destination
    if (destReg.compare("")!=0){
      cout<<"\t"<<"move "<<destReg<<","<<reg1
      <<"\t #Assigning value to Destination "<<destReg
      <<endl;
    }
    if (!((context.getVarType(left->getVal()).compare("pointer")==0)
        && (left->getType().compare("pointer")!=0))){
          if (context.getVarType(left->getVal()).compare("array")!=0){
            context.saveVariable(left->getVal(),false);
          }
        }
    if ((context.getVarType(left->getVal()).compare("array")==0) && (right->getType().compare("init_list")!=0)){
      left->codeGen("s_a_v_e", context);
    }
  }


  // Mathematical and logical binary operations
  if    ((op.compare("+")==0) || (op.compare("-")==0) || (op.compare("<<")==0) || (op.compare(">>")==0)
      || (op.compare("&")==0) || (op.compare("|")==0) || (op.compare("*")==0)
      || (op.compare("^")==0) || (op.compare("%")==0) || (op.compare("/")==0)

      || (op.compare("<")==0) || (op.compare(">")==0) || (op.compare("==")==0) || (op.compare("!=")==0)
      || (op.compare("<=")==0)|| (op.compare(">=")==0)|| (op.compare("&&")==0) || (op.compare("||")==0)
      || (op.compare("sizeof")==0)){

    //Get Tempotary variable names
    string scratch_id1 = context.makeLabel("scratch");
    string scratch_id2 = context.makeLabel("scratch");
    //Left side of expression
    if (context.isInContext(left->getVal())
        && (context.getVarType(left->getVal()).compare("array")!=0)){
      reg1 = context.getReg(left->getVal());
    } else {
      reg1 = context.getFreeRegister("");
      context.makeBinding(scratch_id1, reg1,"scratch");
      left->codeGen(reg1, context);
    }
    //Right side of expression, might be empty if number is negative
    if (right){
      if (context.isInContext(right->getVal())
        && (context.getVarType(right->getVal()).compare("array")!=0)){
        reg2 = context.getReg(right->getVal());
      } else {
        reg2 = context.getFreeRegister("");
        context.makeBinding(scratch_id2, reg2,"scratch");
        right->codeGen(reg2, context);
      }
    }
    //Release the binding of variables
    context.releaseBinding(scratch_id1);
    context.releaseBinding(scratch_id2);

    /* MATHEMATICAL OPPERATIONS */
    if (op.compare("+")==0){
      if (reg2.compare("")!=0){
        cout<<"\t"<<"add "<<destReg<<","<<reg1<<","<<reg2
        <<"\t #Adding values "
        <<endl;
      } else {
        cout<<"\t"<<"add "<<destReg<<",$0,"<<reg1
        <<"\t #Adding values "
        <<endl;
      }
    }
    if (op.compare("-")==0){
      if (reg2.compare("")!=0){
        cout<<"\t"<<"sub "<<destReg<<","<<reg1<<","<<reg2
        <<"\t #Subtracting values "
        <<endl;
      } else {
        cout<<"\t"<<"sub "<<destReg<<",$0,"<<reg1
        <<"\t #Subtracting values "
        <<endl;
      }
    }
    if (op.compare("<<")==0){
      cout<<"\t"<<"sll "<<destReg<<","<<reg1<<","<<reg2
      <<"\t #Shifting values left "
      <<endl;
    }
    if (op.compare(">>")==0){
      cout<<"\t"<<"sra "<<destReg<<","<<reg1<<","<<reg2
      <<"\t #Shifting values right"
      <<endl;
    }
    if (op.compare("&")==0){
      cout<<"\t"<<"and "<<destReg<<","<<reg1<<","<<reg2
      <<"\t #And values "
      <<endl;
    }
    if (op.compare("|")==0){
      cout<<"\t"<<"or "<<destReg<<","<<reg1<<","<<reg2
      <<"\t #Or values"
      <<endl;
    }
    if (op.compare("^")==0){
      cout<<"\t"<<"xor "<<destReg<<","<<reg1<<","<<reg2
      <<"\t #Xor values"
      <<endl;
    }
    if (op.compare("*")==0){
      cout<<"\t"<<"mult "<<reg1<<","<<reg2
      <<"\t #Multypling values "
      <<endl;
      cout<<"\t"<<"mflo "<<destReg
      <<"\t #Fetching from LO and storing in destination "
      <<endl;
    }
    if (op.compare("/")==0){
      cout<<"\t"<<"move $t9,"<<reg1<<endl;
      cout<<"\t"<<"div $t9,"<<reg2
      <<"\t #Divide values "
      <<endl;
      cout<<"\t"<<"mflo "<<destReg
      <<"\t #Fetching from LO and storing in destination "
      <<endl;
      cout<<"\t"<<"move $t9,"<<"$0"<<endl;
    }
    if (op.compare("%")==0){
      cout<<"\t"<<"move $t9,"<<reg1<<endl;
      cout<<"\t"<<"div $t9,"<<reg2
      <<"\t #Divide values "
      <<endl;
      cout<<"\t"<<"mfhi "<<destReg
      <<"\t #Fetching from HI and storing in destination "
      <<endl;
      cout<<"\t"<<"move $t9,$0"<<endl;
    }
    /* LOGICAL OPPERATIONS */
    if (op.compare("<")==0){
      cout<<"\t"<<"slt "<<destReg<<","<<reg1<<","<<reg2
      <<"\t #Set less than <"
      <<endl;
    }
    if (op.compare(">")==0){
      cout<<"\t"<<"slt "<<destReg<<","<<reg2<<","<<reg1
      <<"\t #Set more than >"
      <<endl;
    }
    if (op.compare("==")==0){
      string L1 = context.makeLabel("L");
      string L2 = context.makeLabel("L");
      cout<<"\t"<<"bne "<<reg1<<","<<reg2<<","<<L1
      <<"\t #Evaluation =="
      <<endl;
      cout<<"\t"<<"nop"<<endl;
      cout<<"\t"<<"li "<<destReg<<", 1"<<endl;
      cout<<"\t"<<"b "<<L2<<endl;
      cout<<"\t"<<"nop"<<endl;
      cout<<L1<<":"<<endl;
      cout<<"\t"<<"li "<<destReg<<", 0"<<endl;
      cout<<L2<<":"<<endl;
    }
    if (op.compare("!=")==0){
      cout<<"\t"<<"xor "<<destReg<<","<<reg2<<","<<reg1
      <<"\t #Xor the values"
      <<endl;
      cout<<"\t"<<"sltu "<<destReg<<",$0,"<<destReg
      <<"\t #Compare result for !="
      <<endl;
      cout<<"\t"<<"andi "<<destReg<<","<<destReg<<","<<"0x00ff"
      <<"\t #And the final result"
      <<endl;

    }
    if (op.compare("sizeof")==0){
      uint32_t size = left->getSize(context);
      cout<<"\t"<<"li "<<destReg<<","<<to_string(size)<<endl;
    }
    if (op.compare("<=")==0){
      string L1 = context.makeLabel("L");
      string L2 = context.makeLabel("L");
      cout<<"\t"<<"bgt "<<reg1<<","<<reg2<<","<<L1
      <<"\t #Evaluation <="
      <<endl;
      cout<<"\t"<<"nop"<<endl;
      cout<<"\t"<<"li "<<destReg<<", 1"<<endl;
      cout<<"\t"<<"b "<<L2<<endl;
      cout<<"\t"<<"nop"<<endl;
      cout<<L1<<":"<<endl;
      cout<<"\t"<<"li "<<destReg<<", 0"<<endl;
      cout<<L2<<":"<<endl;
    }
    if (op.compare(">=")==0){
      string L1 = context.makeLabel("L");
      string L2 = context.makeLabel("L");
      cout<<"\t"<<"blt "<<reg1<<","<<reg2<<","<<L1
      <<"\t #Evaluation >="
      <<endl;
      cout<<"\t"<<"nop"<<endl;
      cout<<"\t"<<"li "<<destReg<<", 1"<<endl;
      cout<<"\t"<<"b "<<L2<<endl;
      cout<<"\t"<<"nop"<<endl;
      cout<<L1<<":"<<endl;
      cout<<"\t"<<"li "<<destReg<<", 0"<<endl;
      cout<<L2<<":"<<endl;
    }
    if (op.compare("&&")==0){
      cout<<"\t"<<"move $t9, $0"<<endl;
      cout<<"\t"<<"sltu $t9, $0,"<<reg1<<endl;
      cout<<"\t"<<"sltu "<<destReg<<", $0,"<<reg2<<endl;
      cout<<"\t"<<"and "<<destReg<<",$t9,"<<destReg<<endl;
      cout<<"\t"<<"move $t9, $0"<<endl;
    }
    if (op.compare("||")==0){
      string L1 = context.makeLabel("L");
      string L2 = context.makeLabel("L");
      cout<<"\t"<<"or "<<destReg<<","<<reg1<<","<<reg2<<endl;
      cout<<"\t"<<"beq "<<destReg<<",$0,"<<L1
      <<"\t #Evaluation ||"
      <<endl;
      cout<<"\t"<<"nop"<<endl;
      cout<<"\t"<<"li "<<destReg<<", 1"<<endl;
      cout<<"\t"<<"b "<<L2<<endl;
      cout<<"\t"<<"nop"<<endl;
      cout<<L1<<":"<<endl;
      cout<<"\t"<<"li "<<destReg<<", 0"<<endl;
      cout<<L2<<":"<<endl;

    }
  }
  }
}
