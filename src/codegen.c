#include <codegen.h>

#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include <error.h>
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

//================================================================ BEG LABELS

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

//================================================================ END LABELS


//================================================================ BEG CG_FMT_x86_MSWIN

Error codegen_program_x86_64_mswin(ParsingContext* context, Node* program) {
    Error err = ok;
    // 5452 - labels generated 
    char* label_1 = label_generate();
    char* label_2 = label_generate();
    char* label_3 = label_generate();
    char* label_4 = label_generate();
    char* label_5 = label_generate();
    char* label_6 = label_generate();

    printf("Labels:\n" "%s %s %s %s %s %s", label_1, label_2, label_3, label_4, label_5, label_6);

    ERROR_PREP(err, ERROR_TODO, "codegen_program_x86_64_mswin()");
    return err; 
}

//================================================================ END CG_FMT_x86_MSWIN

Error codegen_program(enum CodegenOutputFormat format, ParsingContext* context, Node* program) {
    Error err = ok;
    if (format == CG_FMT_DEFAULT || format == CG_GMT_x86_64_MSWIN) {
        return codegen_program_x86_64_mswin(context, program);
    }
    ERROR_PREP(err, ERROR_TODO, "codegen_program()");
    return err;
}