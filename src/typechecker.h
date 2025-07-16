#ifndef ALY_COMPILER_TYPECHECKER_H
#define ALY_COMPILER_TYPECHECKER_H

#include <error.h>
#include <parser.h>

/// If types are equal, return 1, otherwise 0.
int type_compare(Node* a, Node* b);

Error expression_return_type(ParsingContext* context, ParsingContext** context_to_enter, Node* expression, Node* type);
Error typecheck_expression(ParsingContext* context, ParsingContext** context_to_enter, Node* expression);
Error typecheck_program(ParsingContext* context, Node* program);

#endif // ALY_COMPILER_TYPECHECKER_H