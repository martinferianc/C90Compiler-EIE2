#ifndef ast_hpp
#define ast_hpp

#include "ast/ast_expression.hpp"
#include "ast/ast_parameter.hpp"
#include "ast/ast_primitives.hpp"
#include "ast/ast_program.hpp"
#include "ast/ast_scope.hpp"
#include "ast/ast_function.hpp"
#include "ast/ast_forloop.hpp"
#include "ast/ast_whileloop.hpp"
#include "ast/ast_if.hpp"
#include "ast/ast_return.hpp"

extern Expression *parseAST();

#endif
