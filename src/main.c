#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <error.h>
#include <file_io.h>
#include <parser.h>

void print_usage(char** argv) {
    printf("USAGE: %s <path_to_file_to_compile>\n", argv[0]);
}

// TODO:
// |-- API to create new Binding.
// `-- API to add Binding to environment.
typedef struct Binding {
    Node* id;
    Node* value;
    struct Binding* next;
} Binding;

// TODO: API to create new Environment.
typedef struct Environment {
    struct Environment* parent;
    Binding* bind;
} Environment;

Environment* environment_create(Environment* parent) {
    Environment* env = malloc(sizeof(Environment));
    assert(env && "Could not allocate memory to new environment");
    env->parent = parent;
    env->bind = NULL;
    return env;
}

/**
* @retval 0 Failure.
* @retval 1 Creation of new binding.
* @retval 2 Existing binding value overwrite (ID unused).
*/
int environment_set(Environment* env, Node* id, Node* value) {
    // Over-write existing value if ID is already bound in environment.
    if (!env || !id || !value) { return 0; }

    Binding* binding_it = env->bind;
    while (binding_it) {
        if (node_compare(binding_it->id, id)) {
            binding_it->value = value;
            return 2;
        }
        binding_it = binding_it->next;
    }
    // Create new binding.
    Binding* binding = malloc(sizeof(Binding));
    assert(binding && "Could not allocate new binding for environment");
    binding->id = id;
    binding->value = value;
    binding->next = env->bind;
    env->bind = binding;
    return 1;
}

/// @return Boolean-like value; 1 for success, 0 for failure.
int environment_get(Environment env, Node* id, Node* result) {
    Binding* binding_it = env.bind;
    while (binding_it) {
        if (node_compare(binding_it->id, id)) {
            *result = *binding_it->value;
            return 1;
        }
        binding_it = binding_it->next;
    }
    return 0;
}

int enviornment_get_by_symbol(Environment env, char* symbol, Node* result) {
    Node* symbol_node = node_symbol(symbol);
    int status = environment_get(env, symbol_node, result);
    free(symbol_node);
    return status;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        print_usage(argv);
        exit(0);
    }

    char* path = argv[1];
    char* contents = file_contents(path);

    if (contents) {
        // printf("Contents of %s:\n---\n\"%s\"\n---\n", path, contents);

        // TODO: Create API to heap allocate a program node, as well as add 
        // expression as children.
        ParsingContext* context = parse_context_create();
        Node* program = node_allocate();
        program->type = NODE_TYPE_PROGRAM;
        Node* expression = node_allocate();
        memset(expression, 0, sizeof(Node));
        char* contents_it = contents;
        Error err = parse_expr(context, contents_it, &contents_it, expression);
        node_add_child(program, expression);

        print_error(err);

        print_node(program, 0);
        putchar('\n');

        node_free(program);
        free(contents);
    }

    return 0;
}