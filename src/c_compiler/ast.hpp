#ifndef ast_hpp
#define ast_hpp

#include "ast/context.hpp"
#include "ast/ast_parameter.hpp"
#include "ast/ast_argument.hpp"
#include "ast/ast_primitives.hpp"
#include "ast/ast_variable.hpp"
#include "ast/ast_program.hpp"
#include "ast/ast_scope.hpp"
#include "ast/ast_function.hpp"
#include "ast/ast_forloop.hpp"
#include "ast/ast_whileloop.hpp"
#include "ast/ast_dowhileloop.hpp"
#include "ast/ast_binary.hpp"
#include "ast/ast_if.hpp"
#include "ast/ast_jump.hpp"
#include "ast/ast_pointer.hpp"
#include "ast/ast_array.hpp"
#include "ast/ast_switch.hpp"
#include "ast/ast_initializer.hpp"

extern Expression *parseAST();

#endif
