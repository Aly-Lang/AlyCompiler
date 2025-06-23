#include <codegen.h>

#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <error.h>
#include <environment.h>
#include <parser.h>

//================================================================ BEG REGISTER STUFF

Register* register_create(char* name) {
    Register* r = calloc(1, sizeof(Register));
    assert(r && "Could not allocate memory for new register");
    r->name = name;
    return r;
}

void register_add(Register* base, char* name) {
    while (base->next) {
        base = base->next;
    }
    base->next = register_create(name);
}

void register_free(Register* base) {
    Register* to_free = NULL;
    while (base) {
        to_free = base;
        if (base->name) {
            free(base->name);
        }
        base = base->next;
        free(to_free);
    }
}

RegisterDescriptor register_allocate(Register* base) {
    RegisterDescriptor register_descriptor = 0;
    while (base) {
        if (base->in_use == 0) {
            base->in_use = 1;
            return register_descriptor;
        }
        base = base->next;
        register_descriptor++;
    }
    printf("ERROR::register_allocate(): Could not allocate register!\n");
    exit(1);
    return -1;
}

void register_deallocate(Register* base, RegisterDescriptor register_descriptor) {
    while (base) {
        if (register_descriptor == 0) {
            base->in_use = 0;
            return;
        }
        base = base->next;
        register_descriptor--;
    }
    printf("ERROR::register_deallocate(): Could not deallocate register %d\n", register_descriptor);
    exit(1);
}

char* register_name(Register* base, RegisterDescriptor register_descriptor) {
    while (base) {
        register_descriptor--;
        if (register_descriptor <= 0) {
            return base->name;
        }
        base = base->next;
    }
    printf("ERROR::register_name(): Could not find register with descriptor of %d\n", register_descriptor);
    return NULL;
}

//================================================================ END REGISTER STUFF

#define label_buffer_size 1024
char label_buffer[label_buffer_size];
size_t label_index = 0;
size_t label_count = 0;
char* label_generate() {
    char* label = label_buffer + label_index;
    label_index += snprintf(label, label_buffer_size - label_index, ".L%d:\n", label_count);
    label_index++;
    if (label_index >= label_buffer_size) {
        label_index = 0;
        return label_generate();
    }
    label_count++;
    return label;
}

//================================================================ BEG CG_FMT_x86_MSWIN

#define symbol_buffer_size 1024
char symbol_buffer[symbol_buffer_size];
size_t symbol_index = 0;
size_t symbol_count = 0;
char* symbol_to_address() {
    // Calculate symbol address.
    char* symbol_string = symbol_buffer + symbol_index;
    // Global variable access.
    symbol_index += snprintf(symbol_string, symbol_buffer_size - symbol_index, "%s(%%rip)", symbol->value.symbol);
    // TODO: Local variable access.

    symbol_index++;
    if (symbol_index >= symbol_buffer_size) {
        symbol_index = 0;
        return label_generate();
    }
    return symbol_string;
}

Error codegen_expression_x86_64_mswin(FILE* code, ParsingContext* context, Node* expression) {
    switch (expression->type) {
    default:
        break;
    case NODE_TYPE_VARIABLE_REASSIGNMENT:
        break;
    }
}

Error codegen_program_x86_64_mswin(FILE* code, ParsingContext* context, Node* program) {
    Error err = ok;

    ERROR_PREP(err, ERROR_TODO, "codegen_program_x86_64_mswin()");
    return err;
}

//================================================================ END CG_FMT_x86_MSWIN

CodegenContext* codegen_context_create(CodegenContext* parent) {
    CodegenContext* cg_ctx = calloc(1, sizeof(CodegenContext));
    cg_ctx->parent = parent;
    cg_ctx->locals - environment_create(NULL);
    return cg_ctx;
}

Error codegen_program(enum CodegenOutputFormat format, ParsingContext* context, Node* program) {
    Error err = ok;

    CodegenContext *cg_context = codegen_context_create();

    // Open file for writing.
    FILE* code = fopen("code.S", "w");

    if (format == CG_FMT_DEFAULT || format == CG_GMT_x86_64_MSWIN) {
        err = codegen_program_x86_64_mswin(code, context, program);
    }
    fclose(code);
    if (err.type) { return err; }

    ERROR_PREP(err, ERROR_TODO, "codegen_program()");
    return err;
}