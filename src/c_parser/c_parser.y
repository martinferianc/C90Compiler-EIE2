%code requires{
  #include <string>
  #include <stdio.h>
  #include <cassert>
  #include <iostream>

  #include "ast.hpp"

  extern Program *g_root;

  int yylex(void);
  void yyerror(const char* );

  using namespace std;
}
%right "then" tElse
%union{
  Expression *expr;
  Function *func;
  Parameter *param;
  ParameterList *param_list;
  int integer_constant;
  double double_constant;
  std::string *string;
}

%token tDivision tDivisionEqual tPipeEqual tStringLiteral tIdentifier tIntegerConstant tCharacterConstant tFloatingConstant tInt tFor tWhile tSizeof tAuto tBreak tCase tChar tConst tContinue tDo tDouble tElse tEnum tExtern tFloat tGoTo tIf tLong tRegister tReturn tShort tSigned tStatic tDefault tSwitch tTypedef tUnion tUnsigned tVoid tVolatile tPipe tLBracket tRBracket tDot tExMark tPlus tMinus tPlusPlus tMinusMinus tLSBracket tRSBracket tMore tAnd tDivison tModulo tXor tMultiply tComma tHash tQuesMark tColon tTilde tSemiColon tCScope tOScope tAndAnd tPipePipe tAssOperator tExMarkEqual tEqualEqual tMoreEqual tLessEqual tMoreMore tLessLess tMinusEqual tPlusEqual tModuloEqual tMultiplyEqual tEqual tXorEqual tAndEqual tDotDotDot tMoreMoreEqual tLessLessEqual tLess
%type <integer_constant> tIntegerConstant
%type <string> tIdentifier
%type <double_constant> tFloatingConstant
%type <expr> PROGRAM CONSTANT_EXPRESSION DIRECT_DECLARATOR DECLARATOR INITIALIZER INIT_DECLARATOR INIT_DECLARATOR_LIST INITIALIZER_LIST LOGICAL_OR_EXPRESSION LOGICAL_AND_EXPRESSION INCLUSIVE_OR_EXPRESSION EXCLUSIVE_OR_EXPRESSION AND_EXPRESSION EQUALITY_EXPRESSION RELATIONAL_EXPRESSION SHIFT_EXPRESSION ADDITIVE_EXPRESSION MULTIPLICATIVE_EXPRESSION CAST_EXPRESSION UNARY_EXPRESSION STATEMENT JUMP_STATEMENT DECLARATION ARGUMENT_EXPRESSION_LIST DECLARATION_STATEMENT ASSIGNMENT_EXPRESSION EXPRESSION PARTS PRIMARY_EXPRESSION POSTFIX_EXPRESSION EXPRESSION_STATEMENT ITERATION_STATEMENT CONDITIONAL_EXPRESSION SELECTION_STATEMENT COMPOUND_STATEMENT STATEMENT_LIST
%type <func> FUNCTION
%type <param_list> PARAMETERS PARAMETERS_LIST

%start PROGRAM
%%

PROGRAM: PARTS

PARTS
  : FUNCTION                                                      {g_root->add($1);}
  | STATEMENT                                                     {g_root->add($1);}
  | PARTS FUNCTION                                                {g_root->add($2);}
  | PARTS STATEMENT                                               {g_root->add($2);}
  ;

STATEMENT
  : EXPRESSION_STATEMENT                                            {$$ = $1;}
  | COMPOUND_STATEMENT                                              {$$ = $1;}
  | ITERATION_STATEMENT                                             {$$ = $1;}
  | SELECTION_STATEMENT                                             {$$ = $1;}
  | DECLARATION_STATEMENT                                           {$$ = $1;}
  | JUMP_STATEMENT                                                  {$$ = $1;}
  ;

EXPRESSION_STATEMENT
  : tSemiColon                                                      {$$ = NULL;}
	| EXPRESSION tSemiColon                                           {$$ = $1;}
  ;

PRIMARY_EXPRESSION
  : tIdentifier                                                     {$$ = new Variable(*$1);}
  | tIntegerConstant                                                {$$ = new NumberInt($1);}
  | tFloatingConstant                                               {$$ = new NumberDouble($1);}
  | tStringLiteral                                                  {;}
  | tLBracket EXPRESSION tRBracket                                  {$$ = $2;}
  ;


POSTFIX_EXPRESSION
	: PRIMARY_EXPRESSION
	| POSTFIX_EXPRESSION tLSBracket EXPRESSION tRSBracket
  | POSTFIX_EXPRESSION tLBracket tRBracket                          {;}
	| POSTFIX_EXPRESSION tLBracket ARGUMENT_EXPRESSION_LIST tRBracket {;}
	| POSTFIX_EXPRESSION tDot tIdentifier
	| POSTFIX_EXPRESSION tAssOperator tIdentifier
	| POSTFIX_EXPRESSION tPlusPlus
	| POSTFIX_EXPRESSION tMinusMinus
	;


UNARY_EXPRESSION
	: POSTFIX_EXPRESSION                                                       {$$ = NULL;}
	| tPlusPlus UNARY_EXPRESSION                                               {$$ = NULL;}
	| tMinusMinus UNARY_EXPRESSION                                             {$$ = NULL;}
	| UNARY_OPERATOR CAST_EXPRESSION                                           {$$ = NULL;}
	| tSizeof UNARY_EXPRESSION                                                 {$$ = NULL;}
	| tSizeof tLBracket TYPE_NAME tRBracket                                    {$$ = NULL;}
	;

UNARY_OPERATOR
	: tAnd
	| tMultiply
	| tPlus
	| tMinus
	| tTilde
	| tExMark
	;

CAST_EXPRESSION
  : UNARY_EXPRESSION
  | tLBracket TYPE_NAME tRBracket CAST_EXPRESSION                            {$$ = $4;}
  ;

MULTIPLICATIVE_EXPRESSION
	: CAST_EXPRESSION
	| MULTIPLICATIVE_EXPRESSION tMultiply CAST_EXPRESSION
	| MULTIPLICATIVE_EXPRESSION tDivision CAST_EXPRESSION
	| MULTIPLICATIVE_EXPRESSION tModulo CAST_EXPRESSION
	;

ADDITIVE_EXPRESSION
	: MULTIPLICATIVE_EXPRESSION
	| ADDITIVE_EXPRESSION tPlus MULTIPLICATIVE_EXPRESSION
	| ADDITIVE_EXPRESSION tMinus MULTIPLICATIVE_EXPRESSION
	;

SHIFT_EXPRESSION
	: ADDITIVE_EXPRESSION
	| SHIFT_EXPRESSION tLessLess ADDITIVE_EXPRESSION
	| SHIFT_EXPRESSION tMoreMore ADDITIVE_EXPRESSION
	;

RELATIONAL_EXPRESSION
	: SHIFT_EXPRESSION
	| RELATIONAL_EXPRESSION tLess SHIFT_EXPRESSION
	| RELATIONAL_EXPRESSION tMore SHIFT_EXPRESSION
	| RELATIONAL_EXPRESSION tLessEqual SHIFT_EXPRESSION
	| RELATIONAL_EXPRESSION tMoreEqual SHIFT_EXPRESSION
	;

EQUALITY_EXPRESSION
	: RELATIONAL_EXPRESSION
	| EQUALITY_EXPRESSION tEqualEqual RELATIONAL_EXPRESSION
	| EQUALITY_EXPRESSION tExMarkEqual RELATIONAL_EXPRESSION
	;

AND_EXPRESSION
	: EQUALITY_EXPRESSION
	| AND_EXPRESSION tAnd EQUALITY_EXPRESSION
	;

EXCLUSIVE_OR_EXPRESSION
	: AND_EXPRESSION
	| EXCLUSIVE_OR_EXPRESSION tXor AND_EXPRESSION
	;

INCLUSIVE_OR_EXPRESSION
	: EXCLUSIVE_OR_EXPRESSION
	| INCLUSIVE_OR_EXPRESSION tPipe EXCLUSIVE_OR_EXPRESSION
	;

LOGICAL_AND_EXPRESSION
	: INCLUSIVE_OR_EXPRESSION
	| LOGICAL_AND_EXPRESSION tAndAnd INCLUSIVE_OR_EXPRESSION
	;

LOGICAL_OR_EXPRESSION
	: LOGICAL_AND_EXPRESSION
	| LOGICAL_OR_EXPRESSION tPipePipe LOGICAL_AND_EXPRESSION
	;

CONDITIONAL_EXPRESSION
	: LOGICAL_OR_EXPRESSION                                                      {$$ = $1;}
	| LOGICAL_OR_EXPRESSION tQuesMark EXPRESSION tColon CONDITIONAL_EXPRESSION   {$$ = $1;}
	;

ASSIGNMENT_EXPRESSION
	: CONDITIONAL_EXPRESSION                                                     {$$ = NULL;}
	| UNARY_EXPRESSION ASSIGNMENT_OPERATOR ASSIGNMENT_EXPRESSION                 {$$ = NULL;}
	;

ASSIGNMENT_OPERATOR
  : tEqual
  | tPlusEqual
  | tModuloEqual
  | tMinusEqual
  | tDivisionEqual
  | tXorEqual
  | tAndEqual
  | tMoreMoreEqual
  | tLessLessEqual
  | tPipeEqual
  | tMultiplyEqual
  ;

EXPRESSION
  : ASSIGNMENT_EXPRESSION
  | EXPRESSION tComma ASSIGNMENT_EXPRESSION
  ;

ARGUMENT_EXPRESSION_LIST
  : ASSIGNMENT_EXPRESSION
  | ARGUMENT_EXPRESSION_LIST tComma ASSIGNMENT_EXPRESSION
  ;

COMPOUND_STATEMENT
  : tOScope tCScope                                                     {$$ = new Scope();}
  | tOScope STATEMENT_LIST tCScope                                      {$$ = $2;}
  ;

STATEMENT_LIST
  : STATEMENT                                                           {$$ = new Scope(); $$->add($1);}
  | STATEMENT_LIST STATEMENT                                            {$1->add($2); $$ = $1;}
  ;

DECLARATION_STATEMENT
  : DECLARATION tSemiColon                                                {$$ = $1;}
  ;

CONSTANT_EXPRESSION
	: CONDITIONAL_EXPRESSION                                                {$$ = NULL;}
	;

DECLARATION
	: TYPE_NAME                                                              {;}
	| TYPE_NAME INIT_DECLARATOR_LIST                                         {$$ = $2;}
	;

INIT_DECLARATOR_LIST
	: INIT_DECLARATOR                                                      {VariableList* v = new VariableList();
                                                                          v->add($1);
                                                                          $$ = v;}
	| INIT_DECLARATOR_LIST tComma INIT_DECLARATOR                          {$1->add($3); $$ = $1;}
	;

INIT_DECLARATOR
	: DECLARATOR                                                           {$$ = $1;}
	| DECLARATOR tEqual INITIALIZER                                        {$$ = $1;}
	;

INITIALIZER
	: ASSIGNMENT_EXPRESSION                                            {$$ = NULL;}
	| tOScope INITIALIZER_LIST tCScope                                 {$$ = NULL;}
	| tOScope INITIALIZER_LIST tComma tCScope                          {$$ = NULL;}
	;

INITIALIZER_LIST
	: INITIALIZER
	| INITIALIZER_LIST tComma INITIALIZER
	;

DECLARATOR
  : POINTER DIRECT_DECLARATOR                                       {$$ = $2;}
  | DIRECT_DECLARATOR                                               {$$ = $1;}
  ;

POINTER
	: tMultiply
	| tMultiply TYPE_NAME
	| tMultiply POINTER
	| tMultiply TYPE_NAME POINTER
	;

DIRECT_DECLARATOR
	: tIdentifier                                                        {$$ = new Variable(*$1);}
	| tLBracket DECLARATOR tRBracket                                     {$$ = NULL;}
	| DIRECT_DECLARATOR tLSBracket CONSTANT_EXPRESSION tRSBracket
	| DIRECT_DECLARATOR tLSBracket tRSBracket
  | DIRECT_DECLARATOR tLBracket PARAMETERS_LIST tRBracket
  | DIRECT_DECLARATOR tLBracket tRBracket
	;

FUNCTION
	: TYPE_NAME tIdentifier PARAMETERS COMPOUND_STATEMENT                   {$$ = new Function(*$2, $3, $4);}
	| tIdentifier COMPOUND_STATEMENT                                        {$$ = new Function(*$1, NULL, $2);}
	;

PARAMETERS
  : tLBracket tRBracket                                                 {$$ = new ParameterList();}
  | tLBracket PARAMETERS_LIST tRBracket                                 {$$ = $2;}
  ;

PARAMETERS_LIST
  : TYPE_NAME tIdentifier                                               {$$ = new ParameterList(); $$->add(new Parameter(*$2)); }
  | PARAMETERS_LIST tComma TYPE_NAME tIdentifier                        {$$->add(new Parameter(*$4));}
  ;

SELECTION_STATEMENT
	: tIf tLBracket EXPRESSION tRBracket STATEMENT  %prec "then"            {$$ = new If($3,$5,NULL);}
	| tIf tLBracket EXPRESSION tRBracket STATEMENT tElse STATEMENT          {$$ = new If($3,$5,$7);}
	;

ITERATION_STATEMENT
	: tWhile tLBracket EXPRESSION tRBracket STATEMENT                                                  {$$ = new WhileLoop($3, $5);}
	| tDo STATEMENT tWhile tLBracket EXPRESSION tRBracket tSemiColon                                   {$$ = new WhileLoop($5, $2);}
	| tFor tLBracket EXPRESSION_STATEMENT EXPRESSION_STATEMENT tRBracket STATEMENT                     {$$ = new ForLoop($3, $4, NULL, $6);}
	| tFor tLBracket EXPRESSION_STATEMENT EXPRESSION_STATEMENT EXPRESSION tRBracket STATEMENT          {$$ = new ForLoop($3, $4, $5, $7);}
  ;

TYPE_NAME
  : tVoid
  | tChar
  | tShort
  | tInt
  | tLong
  | tFloat
  | tDouble
  | tSigned
  | tUnsigned

JUMP_STATEMENT
	: tGoTo tIdentifier tSemiColon                                  {$$ = NULL;}
	| tContinue tSemiColon                                          {$$ = NULL;}
	| tBreak tSemiColon                                             {$$ = NULL;}
	| tReturn tSemiColon                                            {$$ = NULL;}
	| tReturn EXPRESSION tSemiColon                                 {$$ = NULL;}
	;


%%
Program* g_root;
Expression *parseAST(){
  g_root = new Program();
  yyparse();
  return g_root;
}
