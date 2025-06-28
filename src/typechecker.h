#ifndef ALY_COMPILER_TYPECHECKER_H
#define ALY_COMPILER_TYPECHECKER_H

#include <error.h>
#include <parser.h>

Error expression_return_type(ParsingContext* context, Node* expression, int* type);
Error typecheck_expression(ParsingContext* context, Node* expression);
Error typecheck_program(ParsingContext* context, Node* program);

#endif // ALY_COMPILER_TYPECHECKER_H