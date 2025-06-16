#include <codegen.h>

#include <error.h>
#include <parser.h>
#include <stdio.h>

Error codegen_program_x86_64_att_asm(Node* program) {
    Error err = ok;
    if (!program || program->type != NODE_TYPE_PROGRAM) {
        ERROR_PREP(err, ERROR_ARGUMENTS, "codegen_program() requires a a program!");
        return err;
    }

    FILE* code = fopen("code.txt", "wb");
    if (!code) {
        ERROR_PREP(err, ERROR_GENERIC, "codegen_program() could not open code file");
        return err;
    }

    // TODO: Generate code :^)

    Node* expression = program->children;
    while (expression) {
        switch (expression->type) {
        default:
            break;
        case NODE_TYPE_VARIABLE_DECLARATION:
            // TODO: Handle nested scopes (stack based variables)    
            break;
        }
        
        expression = expression->next_child;
    }

    fclose(code);
    return ok;
}

Error codegen_program(CodegenOutputFormat format, Node* program) {
    switch (format) {
    case OUTPUT_FMT_DEFAULT:
    case OUTPUT_FMT_x86_64_AT_T_ASM:
        return codegen_program_x86_64_att_asm(program);
        break;
    }
    return ok;
}