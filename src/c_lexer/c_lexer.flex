%option noyywrap

%{
  #include <stdlib.h>
  #include <string>
  #include <iostream>
  #include <stdio.h>
  #include <algorithm>


  using namespace std;
%}

KEYWORD                   (sizeof|int|auto|break|case|char|const|continue|default|do|double|else|enum|extern|float|for|goto|if|long|register|return|short|signed|static|struct|switch|typedef|union|unsigned|void|volatile|while)


FLOATING_SUFFIX           [flFL]
SIGN                      [+-]
DIGIT                     [0-9]
DIGIT_SEQUENCE            ([0-9]+)
EXPONEN_PART              ([eE]{SIGN}?{DIGIT}+)
FRACTIONAL_CONSTANT       ((({DIGIT_SEQUENCE})?\.{DIGIT_SEQUENCE})|({DIGIT_SEQUENCE}\.))
FLOATING_CONSTANT         ({SIGN}?(({FRACTIONAL_CONSTANT}{EXPONEN_PART}?{FLOATING_SUFFIX}?)|({DIGIT_SEQUENCE}{EXPONEN_PART}{FLOATING_SUFFIX}?)))

LONG_SUFFIX               [lL]
UNSIGNED_SUFFIX           [uU]
INTEGER_SUFFIX            (({UNSIGNED_SUFFIX}{LONG_SUFFIX}?)|({LONG_SUFFIX}{UNSIGNED_SUFFIX}?))
HEXADECIMAL_DIGIT         [0-9a-fA-F]
NONDIGIT                  [_a-zA-Z]
OCTAL_DIGIT               [0-7]
NONZERO_DIGIT             [1-9]
HEXADECIMAL_CONSTANT      (0[xX]{HEXADECIMAL_DIGIT}+)
OCTAL_CONSTANT            (0{OCTAL_DIGIT}+)
DECIMAL_CONSTANT          (0|({NONZERO_DIGIT}{DIGIT}*))
INTEGER_CONSTANT          (({DECIMAL_CONSTANT}|{OCTAL_CONSTANT}|{HEXADECIMAL_CONSTANT}){INTEGER_SUFFIX}?)

OCTAL_ESCAPE_SEQ          (\\{OCTAL_DIGIT}{1,3})
SIMPLE_ESCAPE_SEQ         [\'\"\?\\abfnrtv]
HEXADECIMAL_ESCAPE_SEQ    (\\x{HEXADECIMAL_DIGIT}+)
ESCAPE_SEQ                ((\\{SIMPLE_ESCAPE_SEQ})|({OCTAL_ESCAPE_SEQ})|({HEXADECIMAL_ESCAPE_SEQ}))
CHARACTER_CONSTANT        (L?\'([^\\\'\n]|{ESCAPE_SEQ})+\')
CONSTANT                  ({CHARACTER_CONSTANT}|{INTEGER_CONSTANT}|{FLOATING_CONSTANT})
IDENTIFIER                ({NONDIGIT}({DIGIT}|{NONDIGIT})*)
OPERATOR                  (\||\=|\(|\)|\.|\!|\+|\-|\+\+|\-\-|\[|\]|\>|\&|\/|\%|\^|\*|\,|\#|\?|\:|\~|\;|\{|\}|\&\&|\|\||\-\>|\!\=|\=\=|\>\=|\<\=|\>\>|\<\<|\-\=|\+\=|\%\=|\/\=|\*\=|\=|\^\=|\&\=|\.\.\.|\>\>\=|\<\<\=|\<)
STRINGLITERAL             (L?\"([^"\\\n]|{ESCAPE_SEQ})*\")
WHITE_SPACE               [ ]
TAB                       [\t]
NEW_LINE                  [\n\r]
PREPROCESSOR              (\#[^\n]*)
INVALID                   [.]
%{
  using namespace std;
  string source_file = "";
  int stream_line = 1;
  int source_line = 1;
  int column = 1;
%}
%{
  void getFileName(){
    string input = string(yytext);
    size_t i = input.find("\"", 0);
    size_t j = input.find("\"", i+1);
    if ((i!=string::npos) && (j!=string::npos)){
      input = input.erase(j,input.length());
      source_file = input.substr(i+1,j-1);
    }
  }
%}
%{
  void getSourceLine(){
    string input = string(yytext);
    size_t i = input.find(" ",0);
    size_t j = input.find(" ",i+1);
    source_line = stoi(input.substr(i+1, j)) - 1;
  }
%}
%{
  void formatJson(const string& Class){
    string input = string(yytext);
    if (Class == "StringLiteral" )
       input = input.substr(1, input.length()-2);

    cout
      <<"{"<<"\"Class\":"<<"\""<<Class<<"\", "
      <<"\"Text\":"<<"\""<<input<<"\", "
      <<"\"StreamLine\":"<<stream_line<<", "
      <<"\"SourceFile\":"<<"\""<<source_file<<"\", "
      <<"\"SourceLine\":"<<source_line<<", "
      <<"\"SourceCol\":"<<column
      <<"},\n";
      column+= yyleng;
  }
%}

%%
{NEW_LINE}              {source_line++; stream_line++; column = 1;}
{WHITE_SPACE}           {column++;}
{PREPROCESSOR}          {getSourceLine(); getFileName();}
{KEYWORD}               {formatJson("Keyword");}
{OPERATOR}              {formatJson("Operator");}
{IDENTIFIER}            {formatJson("Identifier");}
{CONSTANT}              {formatJson("Constant");}
{STRINGLITERAL}         {formatJson("StringLiteral");}
{INVALID}               {formatJson("Invalid");}
{TAB}                   {column+=8;}
%%

int main(){
  cout<<"["<<endl;
  yylex();
  cout<<"{}"<<endl<<"]"<<endl;
}
