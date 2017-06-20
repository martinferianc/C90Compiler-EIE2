%option noyywrap
%option nounput
%option noinput

%{
  #include <stdlib.h>
  #include <string>
  #include <iostream>
  #include <stdio.h>

  #include "c_parser.tab.hpp"
  using namespace std;

  string source_file = "";
  int stream_line = 1;
  int source_line = 1;
  int column = 1;
%}

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
IDENTIFIER                ({NONDIGIT}({DIGIT}|{NONDIGIT})*)
STRINGLITERAL             (L?\"([^"\\\n]|{ESCAPE_SEQ})*\")

COMMENT                   (\/\/[^\n]*)
WHITE_SPACE               [ ]
TAB                       [\t]
NEW_LINE                  [\n\r]
PREPROCESSOR              (\#[^\n]*)
INVALID                   (.)

%%
{COMMENT}                 {;}
{NEW_LINE}                {source_line++; stream_line++; column = 1;}
{WHITE_SPACE}             {column++;}
{TAB}                     {column+=8;}
(int)                     {return tInt;}
(return)                  {return tReturn;}
(for)                     {return tFor;}
(if)                      {return tIf;}
(while)                   {return tWhile;}
(sizeof)                  {return tSizeof;}
(auto)                    {return tAuto;}
(break)                   {return tBreak;}
(case)                    {return tCase;}
(char)                    {return tChar;}
(const)                   {return tConst;}
(continue)                {return tContinue;}
(default)                 {return tDefault;}
(do)                      {return tDo;}
(double)                  {return tDouble;}
(else)                    {return tElse;}
(enum)                    {return tEnum;}
(extern)                  {return tExtern;}
(float)                   {return tFloat;}
(goto)                    {return tGoTo;}
(long)                    {return tLong;}
(register)                {return tRegister;}
(short)                   {return tShort;}
(signed)                  {return tSigned;}
(static)                  {return tStatic;}
(struct)                  {return tDefault;}
(switch)                  {return tSwitch;}
(typedef)                 {return tTypedef;}
(union)                   {return tUnion;}
(unsigned)                {return tUnsigned;}
(void)                    {return tVoid;}
(volatile)                {return tVolatile;}
\|                        {return tPipe;}
\=                        {return tEqual;}
\(                        {return tLBracket;}
\)                        {return tRBracket;}
\.{3}                     {return tDotDotDot;}
\.                        {return tDot;}
\!                        {return tExMark;}
\+                        {return tPlus;}
\-                        {return tMinus;}
\+\+                      {return tPlusPlus;}
\-\-                      {return tMinusMinus;}
\[                        {return tLSBracket;}
\]                        {return tRSBracket;}
\>                        {return tMore;}
\&                        {return tAnd;}
\/                        {return tDivision;}
\%                        {return tModulo;}
\^                        {return tXor;}
\*                        {return tMultiply;}
\,                        {return tComma;}
\#                        {return tHash;}
\?                        {return tQuesMark;}
\:                        {return tColon;}
\~                        {return tTilde;}
\;                        {return tSemiColon;}
\}                        {return tCScope;}
\{                        {return tOScope;}
\&\&                      {return tAndAnd;}
\|\=                      {return tPipeEqual;}
\|\|                      {return tPipePipe;}
\-\>                      {return tAssOperator;}
\!\=                      {return tExMarkEqual;}
\=\=                      {return tEqualEqual;}
\>\=                      {return tMoreEqual;}
\<\=                      {return tLessEqual;}
\>\>                      {return tMoreMore;}
\<\<                      {return tLessLess;}
\-\=                      {return tMinusEqual;}
\+\=                      {return tPlusEqual;}
\%\=                      {return tModuloEqual;}
\/\=                      {return tDivisionEqual;}
\*\=                      {return tMultiplyEqual;}
\^\=                      {return tXorEqual;}
\&\=                      {return tAndEqual;}
\>\>\=                    {return tMoreMoreEqual;}
\<\<\=                    {return tLessLessEqual;}
\<                        {return tLess;}
{STRINGLITERAL}           {yylval.string = new string(yytext);              return tStringLiteral;}
{IDENTIFIER}              {yylval.string = new string(yytext);              return tIdentifier; }
{INTEGER_CONSTANT}        {yylval.integer_constant = atoi(yytext);          return tIntegerConstant;}
{CHARACTER_CONSTANT}      {yylval.string = new string(yytext);              return tCharacterConstant;}
{FLOATING_CONSTANT}       {yylval.double_constant = atof(yytext);           return tFloatingConstant;}
{INVALID}                 {;}
%%

void yyerror(char const* c){
  fprintf (stderr, "Flex Error: String: %s, Source Line: %d\n", yytext, source_line);
  exit(1);
}
