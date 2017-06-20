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
  int integer_constant;
  double double_constant;
  std::string *string;
}

%token tDivision tPipeEqual tDivisionEqual tStringLiteral tIdentifier tIntegerConstant tCharacterConstant tFloatingConstant tInt tFor tWhile tSizeof tAuto tBreak tCase tChar tConst tContinue tDo tDouble tElse tEnum tExtern tFloat tGoTo tIf tLong tRegister tReturn tShort tSigned tStatic tDefault tSwitch tTypedef tUnion tUnsigned tVoid tVolatile tPipe tLBracket tRBracket tDot tExMark tPlus tMinus tPlusPlus tMinusMinus tLSBracket tRSBracket tMore tAnd tDivison tModulo tXor tMultiply tComma tHash tQuesMark tColon tTilde tStruct tSemiColon tCScope tOScope tAndAnd tPipePipe tAssOperator tExMarkEqual tEqualEqual tMoreEqual tLessEqual tMoreMore tLessLess tMinusEqual tPlusEqual tModuloEqual tMultiplyEqual tEqual tXorEqual tAndEqual tDotDotDot tMoreMoreEqual tLessLessEqual tLess
%type <integer_constant> tIntegerConstant
%type <string> tStringLiteral tIdentifier tPipeEqual tAssOperator TYPE_SPECIFIER tVoid tChar tShort tInt tLong tFloat tDouble tSigned tUnsigned tConst tVolatile SPECIFIER_QUALIFIER_LIST TYPE_QUALIFIER ASSIGNMENT_OPERATOR tSizeof tDivision tDivisionEqual  tPipe tLBracket tRBracket tDot tExMark tPlus tMinus tPlusPlus tMinusMinus tLSBracket tRSBracket tMore tAnd tDivison tModulo tXor tMultiply tComma tHash tQuesMark tColon tTilde tSemiColon tCScope tOScope tAndAnd tPipePipe tExMarkEqual tEqualEqual tMoreEqual tLessEqual tMoreMore tLessLess tMinusEqual tPlusEqual tModuloEqual tMultiplyEqual tEqual tXorEqual tAndEqual tDotDotDot tMoreMoreEqual tLessLessEqual tLess UNARY_OPERATOR tCharacterConstant
%type <double_constant> tFloatingConstant
%type <expr> FUNCTION PROGRAM STATEMENT JUMP_STATEMENT DECLARATION DIRECT_DECLARATOR DECLARATOR INITIALIZER INIT_DECLARATOR INIT_DECLARATOR_LIST INITIALIZER_LIST ARGUMENT_EXPRESSION_LIST DECLARATION_STATEMENT ASSIGNMENT_EXPRESSION EXPRESSION PARTS PRIMARY_EXPRESSION POSTFIX_EXPRESSION EXPRESSION_STATEMENT ITERATION_STATEMENT CONDITIONAL_EXPRESSION SELECTION_STATEMENT COMPOUND_STATEMENT STATEMENT_LIST LOGICAL_OR_EXPRESSION LOGICAL_AND_EXPRESSION INCLUSIVE_OR_EXPRESSION EXCLUSIVE_OR_EXPRESSION AND_EXPRESSION PARAMETERS LABELED_STATEMENT PARAMETERS_LIST EQUALITY_EXPRESSION RELATIONAL_EXPRESSION SHIFT_EXPRESSION ADDITIVE_EXPRESSION MULTIPLICATIVE_EXPRESSION CAST_EXPRESSION UNARY_EXPRESSION

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
  | LABELED_STATEMENT                                               {$$ = $1;}
  ;

EXPRESSION_STATEMENT
  : tSemiColon                                                      {$$ = NULL;}
	| EXPRESSION tSemiColon                                           {$$ = $1;}
  ;

PRIMARY_EXPRESSION
  : tIdentifier                                                     {$$ = new Variable(*$1);}
  | tIntegerConstant                                                {$$ = new NumberInt($1);}
  | tFloatingConstant                                               {$$ = new NumberDouble($1);}
  | tCharacterConstant                                              {$$ = new Char(*$1);}
  | tStringLiteral                                                  {$$ = new String(*$1);}
  | tLBracket EXPRESSION tRBracket                                  {$$ = $2;}
  ;

POSTFIX_EXPRESSION
	: PRIMARY_EXPRESSION                                              {$$ = $1;}
  | POSTFIX_EXPRESSION tLSBracket EXPRESSION tRSBracket             {$$ = new Array($1, $3);}
	| POSTFIX_EXPRESSION tLBracket tRBracket                          {FunctionCall* f = new FunctionCall($$->getVal(), NULL); $$ = f;}
	| POSTFIX_EXPRESSION tLBracket ARGUMENT_EXPRESSION_LIST tRBracket {FunctionCall* f = new FunctionCall($$->getVal(), $3); $$ = f;}
	| POSTFIX_EXPRESSION tDot tIdentifier                             {$$ = new BinaryExpression($1, *$2, NULL);}
	| POSTFIX_EXPRESSION tAssOperator tIdentifier                     {$$ = new BinaryExpression($1, *$2, NULL);}
	| POSTFIX_EXPRESSION tPlusPlus                                    {$$ = new BinaryExpression($1, *$2, NULL);}
	| POSTFIX_EXPRESSION tMinusMinus                                  {$$ = new BinaryExpression($1, *$2, NULL);}
	;

UNARY_EXPRESSION
	: POSTFIX_EXPRESSION                                              {$$ = $1;}
	| tPlusPlus UNARY_EXPRESSION                                      {$$ = new BinaryExpression($2, *$1, NULL);}
	| tMinusMinus UNARY_EXPRESSION                                    {$$ = new BinaryExpression($2, *$1, NULL);}
	| UNARY_OPERATOR CAST_EXPRESSION                                  { if (*$1 =="*"){$$ = new Pointer($2); } else if (*$1 =="&") {$$ = new Reference($2);} else {  $$ = new BinaryExpression($2, *$1, NULL);}}
	| tSizeof UNARY_EXPRESSION                                        {$$ = new BinaryExpression($2, *$1, NULL);}
	;

UNARY_OPERATOR
	: tAnd                                                            {$$ = $1;}
	| tMultiply                                                       {$$ = $1;}
	| tPlus                                                           {$$ = $1;}
	| tMinus                                                          {$$ = $1;}
	| tTilde                                                          {$$ = $1;}
	| tExMark                                                         {$$ = $1;}
	;

CAST_EXPRESSION
  : UNARY_EXPRESSION                                               {$$ = $1;}
  | tLBracket TYPE_SPECIFIER tRBracket CAST_EXPRESSION             {$4->setType(*$2); $$ = $4;}
  ;

MULTIPLICATIVE_EXPRESSION
	: CAST_EXPRESSION                                                            {$$ = $1;}
	| MULTIPLICATIVE_EXPRESSION tMultiply CAST_EXPRESSION                        {$$ = new BinaryExpression($1, *$2, $3);}
	| MULTIPLICATIVE_EXPRESSION tDivision CAST_EXPRESSION                        {$$ = new BinaryExpression($1, *$2, $3);}
	| MULTIPLICATIVE_EXPRESSION tModulo CAST_EXPRESSION                          {$$ = new BinaryExpression($1, *$2, $3);}
	;

ADDITIVE_EXPRESSION
	: MULTIPLICATIVE_EXPRESSION                                                  {$$ = $1;}
	| ADDITIVE_EXPRESSION tPlus MULTIPLICATIVE_EXPRESSION                        {$$ = new BinaryExpression($1, *$2, $3);}
	| ADDITIVE_EXPRESSION tMinus MULTIPLICATIVE_EXPRESSION                       {$$ = new BinaryExpression($1, *$2, $3);}
	;

SHIFT_EXPRESSION
	: ADDITIVE_EXPRESSION                                                        {$$ = $1;}
	| SHIFT_EXPRESSION tLessLess ADDITIVE_EXPRESSION                             {$$ = new BinaryExpression($1, *$2, $3);}
	| SHIFT_EXPRESSION tMoreMore ADDITIVE_EXPRESSION                             {$$ = new BinaryExpression($1, *$2, $3);}
	;

RELATIONAL_EXPRESSION
	: SHIFT_EXPRESSION                                                           {$$ = $1;}
	| RELATIONAL_EXPRESSION tLess SHIFT_EXPRESSION                               {$$ = new BinaryExpression($1, *$2, $3);}
	| RELATIONAL_EXPRESSION tMore SHIFT_EXPRESSION                               {$$ = new BinaryExpression($1, *$2, $3);}
	| RELATIONAL_EXPRESSION tLessEqual SHIFT_EXPRESSION                          {$$ = new BinaryExpression($1, *$2, $3);}
	| RELATIONAL_EXPRESSION tMoreEqual SHIFT_EXPRESSION                          {$$ = new BinaryExpression($1, *$2, $3);}
	;

EQUALITY_EXPRESSION
	: RELATIONAL_EXPRESSION                                                      {$$ = $1;}
	| EQUALITY_EXPRESSION tEqualEqual RELATIONAL_EXPRESSION                      {$$ = new BinaryExpression($1, *$2, $3);}
	| EQUALITY_EXPRESSION tExMarkEqual RELATIONAL_EXPRESSION                     {$$ = new BinaryExpression($1, *$2, $3);}
	;

AND_EXPRESSION
	: EQUALITY_EXPRESSION                                                        {$$ = $1;}
	| AND_EXPRESSION tAnd EQUALITY_EXPRESSION                                    {$$ = new BinaryExpression($1, *$2, $3);}
	;

EXCLUSIVE_OR_EXPRESSION
	: AND_EXPRESSION                                                             {$$ = $1;}
	| EXCLUSIVE_OR_EXPRESSION tXor AND_EXPRESSION                                {$$ = new BinaryExpression($1, *$2, $3);}
	;

INCLUSIVE_OR_EXPRESSION
	: EXCLUSIVE_OR_EXPRESSION                                                    {$$ = $1;}
	| INCLUSIVE_OR_EXPRESSION tPipe EXCLUSIVE_OR_EXPRESSION                      {$$ = new BinaryExpression($1, *$2, $3);}
	;

LOGICAL_AND_EXPRESSION
	: INCLUSIVE_OR_EXPRESSION                                                    {$$ = $1;}
	| LOGICAL_AND_EXPRESSION tAndAnd INCLUSIVE_OR_EXPRESSION                     {$$ = new BinaryExpression($1, *$2, $3);}
	;

LOGICAL_OR_EXPRESSION
	: LOGICAL_AND_EXPRESSION                                                     {$$ = $1;}
	| LOGICAL_OR_EXPRESSION tPipePipe LOGICAL_AND_EXPRESSION                     {$$ = new BinaryExpression($1, *$2, $3);}
	;

CONDITIONAL_EXPRESSION
	: LOGICAL_OR_EXPRESSION                                                      {$$ = $1;}
	| LOGICAL_OR_EXPRESSION tQuesMark EXPRESSION tColon CONDITIONAL_EXPRESSION   {$$ = new If($1,$3,$5);}
	;

ASSIGNMENT_EXPRESSION
	: CONDITIONAL_EXPRESSION                                                     {$$ = $1;}
	| UNARY_EXPRESSION ASSIGNMENT_OPERATOR ASSIGNMENT_EXPRESSION                 {$$ = new BinaryExpression($1, *$2, $3);}
	;

ASSIGNMENT_OPERATOR
  : tEqual                                                                     {$$ = $1;}
  | tPlusEqual                                                                 {$$ = $1;}
  | tModuloEqual                                                               {$$ = $1;}
  | tMinusEqual                                                                {$$ = $1;}
  | tDivisionEqual                                                             {$$ = $1;}
  | tXorEqual                                                                  {$$ = $1;}
  | tAndEqual                                                                  {$$ = $1;}
  | tMoreMoreEqual                                                             {$$ = $1;}
  | tLessLessEqual                                                             {$$ = $1;}
  | tPipeEqual                                                                 {$$ = $1;}
  | tMultiplyEqual                                                             {$$ = $1;}
  ;

EXPRESSION
  : ASSIGNMENT_EXPRESSION                                                      {$$ = $1;}
  | EXPRESSION tComma ASSIGNMENT_EXPRESSION                                    {$$ = $1;}
  ;

ARGUMENT_EXPRESSION_LIST
  : ASSIGNMENT_EXPRESSION                                                      {ArgumentList* a = new ArgumentList();
                                                                                a->add($1);
                                                                                $$ = a;}
  | ARGUMENT_EXPRESSION_LIST tComma ASSIGNMENT_EXPRESSION                      {$$->add($3);}
  ;

COMPOUND_STATEMENT
  : tOScope tCScope                                                           {$$ = new Scope();}
  | tOScope STATEMENT_LIST tCScope                                            {$$ = $2;}
  ;

STATEMENT_LIST
  : STATEMENT                                                                 {$$ = new Scope(); $$->add($1);}
  | STATEMENT_LIST STATEMENT                                                  {$1->add($2); $$ = $1;}
  ;

DECLARATION_STATEMENT
  : DECLARATION tSemiColon                                                    {$$ = $1;}
  ;


DECLARATION
	: SPECIFIER_QUALIFIER_LIST                                                  {;}
	| SPECIFIER_QUALIFIER_LIST INIT_DECLARATOR_LIST                             {$$ = $2; $$->setType(*$1); }
	;

INIT_DECLARATOR_LIST
  : INIT_DECLARATOR                                                            {VariableList* v = new VariableList();
                                                                                v->add($1);
                                                                                $$ = v;}
	| INIT_DECLARATOR_LIST tComma INIT_DECLARATOR                                {$1->add($3); $$ = $1;}
	;

INIT_DECLARATOR
	: DECLARATOR                                                                 {$$ = $1;}
	| DECLARATOR tEqual INITIALIZER                                              {$$ = new BinaryExpression($1, *$2, $3);}
	;

INITIALIZER
	: ASSIGNMENT_EXPRESSION                                                      {$$ = $1;}
	| tOScope INITIALIZER_LIST tCScope                                           {$$ = $2;}
	| tOScope INITIALIZER_LIST tComma tCScope                                    {$$ = $2;}
	;

INITIALIZER_LIST
	: INITIALIZER                                                               {InitializerList* l = new InitializerList();
                                                                               l->add($1);
                                                                               $$ = l;}
	| INITIALIZER_LIST tComma INITIALIZER                                       {$1->add($3); $$ = $1;}
	;

DECLARATOR
  : tMultiply DIRECT_DECLARATOR                                                {$$ = new Pointer($2);}
  | DIRECT_DECLARATOR  tLSBracket tIntegerConstant tRSBracket                  {$$ = new Array($1, $3);}
  | DIRECT_DECLARATOR                                                          {$$ = $1;}
  ;


DIRECT_DECLARATOR
	: tIdentifier                                                        {$$ = new Variable(*$1);}
	| tLBracket DECLARATOR tRBracket                                     {$$ = $2;}
	;

FUNCTION
	: SPECIFIER_QUALIFIER_LIST tIdentifier PARAMETERS COMPOUND_STATEMENT    {$$ = new Function(*$2, $3, $4); $$->setType(*$1);}
  | SPECIFIER_QUALIFIER_LIST tMultiply tIdentifier PARAMETERS COMPOUND_STATEMENT    {$$ = new Function(*$3, $4, $5); $$->setType(*$1);}
  | SPECIFIER_QUALIFIER_LIST tIdentifier PARAMETERS tSemiColon            {$$ = new FunctionDec(*$2, $3); $$->setType(*$1);}
	;

PARAMETERS
  : tLBracket tRBracket                                                 {$$ = new ParameterList();}
  | tLBracket PARAMETERS_LIST tRBracket                                 {$$ = $2;}
  ;

PARAMETERS_LIST
  : SPECIFIER_QUALIFIER_LIST tIdentifier                                {$$ = new ParameterList();
                                                                         Parameter* p = new Parameter(*$2);
                                                                         p->setType(*$1);
                                                                         $$->add(p);}
  | PARAMETERS_LIST tComma SPECIFIER_QUALIFIER_LIST tIdentifier         {Parameter* p = new Parameter(*$4);
                                                                         p->setType(*$3);
                                                                         $$->add(p);}
  | SPECIFIER_QUALIFIER_LIST tMultiply tIdentifier                      {$$ = new ParameterList();
                                                                        Parameter* p = new Parameter(*$3);
                                                                        p->setType(*$1);
                                                                        $$->add(p);}
  | PARAMETERS_LIST tComma SPECIFIER_QUALIFIER_LIST tMultiply tIdentifier {Parameter* p = new Parameter(*$5);
                                                                        p->setType(*$3);
                                                                        $$->add(p);}
  ;

LABELED_STATEMENT
  : tIdentifier tColon STATEMENT                                   {Variable* v = new Variable(*$1); $$ = new Case(v,$3);}
  | tCase EXPRESSION tColon STATEMENT                              {$$ = new Case($2,$4);}
  | tDefault tColon STATEMENT                                      {$$ = new Case(NULL,$3); $$->setType("default");}
  ;

SELECTION_STATEMENT
	: tIf tLBracket EXPRESSION tRBracket STATEMENT %prec "then"             {$$ = new If($3,$5,NULL);}
	| tIf tLBracket EXPRESSION tRBracket STATEMENT tElse STATEMENT          {$$ = new If($3,$5,$7);}
  | tSwitch tLBracket EXPRESSION tRBracket STATEMENT                      {$$ = new Switch($3,$5);}
  ;

ITERATION_STATEMENT
	: tWhile tLBracket EXPRESSION tRBracket STATEMENT                                                  {$$ = new WhileLoop($3, $5);}
	| tDo STATEMENT tWhile tLBracket EXPRESSION tRBracket tSemiColon                                   {$$ = new DoWhileLoop($5, $2);}
  | tFor tLBracket EXPRESSION_STATEMENT EXPRESSION_STATEMENT tRBracket STATEMENT                     {$$ = new ForLoop($3, $4, NULL, $6);}
	| tFor tLBracket EXPRESSION_STATEMENT EXPRESSION_STATEMENT EXPRESSION tRBracket STATEMENT          {$$ = new ForLoop($3, $4, $5, $7);}
  ;

TYPE_SPECIFIER
  : tVoid                                                                   {$$ = $1;}
  | tChar                                                                   {$$ = $1;}
  | tShort                                                                  {$$ = $1;}
  | tInt                                                                    {$$ = $1;}
  | tLong                                                                   {$$ = $1;}
  | tFloat                                                                  {$$ = $1;}
  | tDouble                                                                 {$$ = $1;}
  | tSigned                                                                 {$$ = $1;}
  | tUnsigned                                                               {$$ = $1;}

TYPE_QUALIFIER
	: tConst                                                                  {;}
	| tVolatile                                                               {;}
	;

SPECIFIER_QUALIFIER_LIST
  : TYPE_SPECIFIER SPECIFIER_QUALIFIER_LIST                                 {$$ = new string(*$1 + " " + *$2);}
  | TYPE_SPECIFIER                                                          {$$ = $1;}
  | TYPE_QUALIFIER SPECIFIER_QUALIFIER_LIST                                 {$$ = $2;}
  | TYPE_QUALIFIER                                                          {;}
  ;

JUMP_STATEMENT
	: tGoTo tIdentifier tSemiColon                                  {;}
	| tContinue tSemiColon                                          {$$ = new Continue();}
	| tBreak tSemiColon                                             {$$ = new Break();}
	| tReturn tSemiColon                                            {$$ = new Return(NULL);}
	| tReturn EXPRESSION tSemiColon                                 {$$ = new Return($2);}
	;


%%
Program* g_root;
Expression *parseAST(){
  g_root = new Program();
  yyparse();
  return g_root;
}
