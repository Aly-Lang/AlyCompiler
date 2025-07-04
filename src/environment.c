#include <environment.h>

#include <assert.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

#include <parser.h>

void environment_print(Environment env, long long indent) {
    Binding* binding_it = env.bind;
    long long indent_it = indent;
    while (binding_it) {
        indent_it = indent;
        while (indent_it-- > 0) { putchar(' '); }
        printf("%s -> ", node_text(binding_it->id));
        printf("%s\n", node_text(binding_it->value));
        binding_it = binding_it->next;
    }
}

Environment* environment_create(Environment* parent) {
    Environment* env = malloc(sizeof(Environment));
    assert(env && "Could not allocate memory to new environment");
    env->parent = parent;
    env->bind = NULL;
    return env;
}

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

int environment_get_by_symbol(Environment env, char* symbol, Node* result) {
    Node* symbol_node = node_symbol(symbol);
    int status = environment_get(env, symbol_node, result);
    free(symbol_node);
    return status;
}