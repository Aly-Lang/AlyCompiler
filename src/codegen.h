#ifndef ALY_COMPILER_CODEGEN_H
#define ALY_COMPILER_CODEGEN_H

#include <error.h>
#include <environment.h>
#include <parser.h>

typedef int RegisterDescriptor;

typedef struct Register {
    struct Register* next;
    /// What will be emitted when referencing this register, i.e. "%rax"
    char* name;
    /// If non-zero, this register is already in use.
    char in_use;
} Register;

/// NAME is now owned by register.
Register* register_create(char* name);

void register_add(Register* base, char* name);

void register_free(Register* base);

RegisterDescriptor register_allocate(Register* base);
void register_deallocate(Register* base, RegisterDescriptor register_descriptor);

char* register_name(Register* base, RegisterDescriptor register_descriptor);

char* label_generate();

typedef struct CodegenContext { 
    struct CodegenContext* parent;
    /// LOCALS
    /// `-- SYMBOL (NAME) -> INTEGER (STACK OFFSET)
    Environment* locals;
} CodegenContext;

enum CodegenOutputFormat {
    CG_FMT_DEFAULT = 0,
    CG_GMT_x86_64_MSWIN,
};

Error codegen_program(enum CodegenOutputFormat, ParsingContext* context, Node* program);

#endif // ALY_COMPILER_CODEGEN_H