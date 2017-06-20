#include "ast.hpp"
#include "tinyxml2/tinyxml2.h"
#include "preambulae.hpp"

#include <string>
#include <fstream>
using namespace std;

int main(int argc, char const *argv[]) {
    Expression *ast=parseAST();

    Context context = Context();
    cout<<addHeader("POTATO")<<endl;
    ast->codeGen("$2",context);
    cout<<addFooter()<<endl;

    return 0;
}
