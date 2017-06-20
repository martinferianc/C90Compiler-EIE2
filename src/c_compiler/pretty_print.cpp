#include "ast.hpp"
#include "tinyxml2/tinyxml2.h"
#include "preambulae.hpp"

#include <string>
#include <fstream>
using namespace std;

int main(int argc, char const *argv[]) {
    Expression *ast=parseAST();
    //Print the abstract description
    if (argc!=1){

      tinyxml2::XMLDocument doc;
      string pretty_print = ast->print(true);
      doc.Parse((const char*)pretty_print.c_str());

      tinyxml2::XMLPrinter printer;
      doc.Accept(&printer);

      cout<<printer.CStr();
  } else {

      Context context = Context();
      cout<<addHeader("POTATO")<<endl;
      ast->codeGen("$2",context);
      cout<<addFooter()<<endl;
  }
    return 0;
}
