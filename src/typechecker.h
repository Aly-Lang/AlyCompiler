#ifndef ALY_COMPILER_TYPECHECKER_H
#define ALY_COMPILER_TYPECHECKER_H

#include <error.h>
#include <parser.h>

Error typecheck_program(ParsingContext* context, Node* program);

#endif // ALY_COMPILER_TYPECHECKER_H