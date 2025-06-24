
#include <typechecker.h>

#include <environment.h>
#include <error.h>
#include <parser.h>

#include <stddef.h>
#include <stdio.h>

Error typecheck_expression(ParsingContext* context, Node* expression) {
    Node* value = node_allocate();
    Node* tmpnode = node_allocate();
    Node* iterator = node_allocate();
    switch (expression->type) {
    default:
        break;
    case NODE_TYPE_FUNCTION_CALL:
        // TODO: Ensure function call arguments are correct type.
        //       Get function information from functions environment.
        while (context) {
            if (environment_get(*context->functions, expression->children, value)) {
                break;
            }
            context = context->parent;
        }
        // print_node(value, 0);
        iterator = expression->children->next_child->children;
        tmpnode = value->children->children;
        while (iterator && tmpnode) {
            // print_node(tmpnode->children->next_child, 0);
            iterator = iterator->next_child;
            tmpnode = tmpnode->next_child;
        }
        if (tmpnode != NULL) {
            printf("Function:%s\n", expression->children->value.symbol);
            ERROR_CREATE(err, ERROR_ARGUMENTS, "Not enough arguments passed to function!");
            return err;
        }
        if (iterator != NULL) {
            printf("Function:%s\n", expression->children->value.symbol);
            ERROR_CREATE(err, ERROR_ARGUMENTS, "Too many arguments passed to function!");
            return err;
        }
        break;
    }
    return ok;
}

Error typecheck_program(ParsingContext* context, Node* program) {
    Error err = ok;

    Node* expression = program->children;
    while (expression) {
        err = typecheck_expression(context, expression);
        if (err.type) { return err; }
        expression = expression->next_child;
    }

    ERROR_PREP(err, ERROR_TODO, "typecheck_program()");
    return err;
}