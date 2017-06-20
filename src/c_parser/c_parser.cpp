#include "ast.hpp"
#include "tinyxml2/tinyxml2.h"

#include <fstream>


using namespace std;

int main(int argc, char *argv[]){
  Expression *ast=parseAST();
  //string pretty_print = ast->print(false);
  //cout<<pretty_print<<endl;


  tinyxml2::XMLDocument doc;
  string pretty_print = ast->print(false);

  doc.Parse((const char*)pretty_print.c_str());

  tinyxml2::XMLPrinter printer;
  doc.Accept(&printer);

  cout<<printer.CStr();

  return 0;
}
