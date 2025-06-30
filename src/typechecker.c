#include <typechecker.h>

#include <error.h>
#include <environment.h>
#include <parser.h>

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

Error expression_return_type(ParsingContext* context, Node* expression, int* type) {
    Error err = ok;
    ParsingContext* original_context = context;
    Node* result = node_allocate();
    result->type = -1;
    *type = result->type;
    switch (expression->type) {
    default:
        result->type = expression->type;
        break;
    case NODE_TYPE_BINARY_OPERATOR:
        // Typecheck this operator as well!
        err = typecheck_expression(context, expression);
        if (err.type) { break; }
        while (context->parent) { context = context->parent; }
        environment_get_by_symbol(*context->binary_operators, expression->value.symbol, result);
        err = parse_get_type(original_context, result->children->next_child, result);
        if (err.type) { break; }
        break;
    case NODE_TYPE_FUNCTION_CALL:
        while (context) {
            if (environment_get(*context->functions, expression->children, result)) {
                break;
            }
            context = context->parent;
        }
        // RESULT contains a function node.
        print_node(result, 0);
        break;
    }
    *type = result->type;
    free(result);
    return err;
}

Error typecheck_expression(ParsingContext* context, Node* expression) {
    Error err = ok;
    ParsingContext* original_context = context;
    Node* value = node_allocate();
    Node* tmpnode = node_allocate();
    Node* iterator = node_allocate();
    Node* result = node_allocate();
    int type = NODE_TYPE_NONE;
    switch (expression->type) {
    default:
        break;
    case NODE_TYPE_BINARY_OPERATOR:
        while (context->parent) { context = context->parent; }
        environment_get_by_symbol(*context->binary_operators, expression->value.symbol, value);
        // Get return type of LHS in type integer.
        expression_return_type(original_context, expression->children, &type);
        // Get expected return type of LHS in tmpnode->type.
        parse_get_type(original_context, value->children->next_child->next_child, tmpnode);
        if (type != tmpnode->type) {
            printf("Type: %d\n", type);
            print_node(value->children->next_child->next_child, 0);
            print_node(expression, 0);
            ERROR_PREP(err, ERROR_TYPE, "Return type of LHS expression of binary operator does not match declared LHS return type");
            return err;
        }
        // Get return type of RHS in type integer.
        expression_return_type(original_context, expression->children->next_child, &type);
        // Get expected return type of RHS in tmpnode->type.
        parse_get_type(original_context, value->children->next_child->next_child, tmpnode);
        if (type != tmpnode->type) {
            print_node(expression, 0);
            ERROR_PREP(err, ERROR_TYPE, "Return type of RHS expression of binary operator does not match declared RHS return type");
            return err;
        }
        break;
    case NODE_TYPE_FUNCTION_CALL:
        // TODO: Ensure function call arguments are of correct type.
        //       Get function info from functions environment.
        while (context) {
            if (environment_get(*context->functions, expression->children, value)) {
                break;
            }
            context = context->parent;
        }
        //print_node(value,0);
        iterator = expression->children->next_child->children;
        tmpnode = value->children->children;
        while (iterator && tmpnode) {
            err = parse_get_type(context, tmpnode->children->next_child, result);
            if (err.type) { break; }
            expression_return_type(context, iterator, &type);
            if (type != result->type) {
                printf("Function:%s\n", expression->children->value.symbol);
                ERROR_PREP(err, ERROR_TYPE, "Argument type does not match declared parameter type");
                break;
            }
            iterator = iterator->next_child;
            tmpnode = tmpnode->next_child;
        }
        if (tmpnode != NULL) {
            printf("Function:%s\n", expression->children->value.symbol);
            ERROR_PREP(err, ERROR_ARGUMENTS, "Not enough arguments passed to function!");
            break;
        }
        if (iterator != NULL) {
            printf("Function:%s\n", expression->children->value.symbol);
            ERROR_CREATE(err, ERROR_ARGUMENTS, "Too many arguments passed to function!");
            break;
        }
        break;
    }
    free(result);
    free(value);
    free(tmpnode);
    free(iterator);
    return err;
}

Error typecheck_program(ParsingContext* context, Node* program) {
    Error err = ok;

    Node* expression = program->children;
    while (expression) {
        err = typecheck_expression(context, expression);
        if (err.type) { return err; }
        expression = expression->next_child;
    }
    return err;
}