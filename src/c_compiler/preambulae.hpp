#ifndef ast_preambulae_hpp
#define ast_preambulae_hpp

#include <string>
#include <sstream>

using namespace std;

const string addHeader(const string& fileName){

    string input = string(fileName);

    size_t i = input.find("\"", 0);
    size_t j = input.find("\"", i+1);
    if ((i!=string::npos) && (j!=string::npos)){
      input = input.erase(j,input.length());
      input= input.substr(i+1,j-1);
    }

  stringstream ss;
  ss<<"\t.file	1 " <<"\""<<input<<"\""<<endl
  <<"\t.section .mdebug.abi32"<<endl
  <<"\t.previous"<<endl
  <<"\t.nan	legacy"<<endl
  <<"\t.module	fp=xx"<<endl
  <<"\t.module	nooddspreg"<<endl
  <<"\t.abicalls"<<endl
  <<"\t.text"<<endl;
  return ss.str();
}

const string addFooter(){
  stringstream ss;
	ss<<"\t.ident	\"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.1) 5.4.0 20160609\""<<endl;
  return ss.str();
}

#endif
