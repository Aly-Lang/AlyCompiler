#include <codegen/intermediate_representation.h>

#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>

void ir_insert(CodegenContext* context, IRInstruction* new_instruction) {
    // [ ] -> [ ] <-> [NULL]
    //        [ ] <-> [new] <-> [NULL]
    context->block->last_instruction->next = new_instruction;
    new_instruction->previous = context->block->last_instruction;
    context->block->last_instruction = new_instruction;
}

void ir_femit_instruction(FILE* file, IRInstruction* instruction)
{
#define ID_FORMAT "%%%zu | ", instruction->id
    const size_t id_width = 10;
    size_t id_length = snprintf(NULL, 0, ID_FORMAT);
    int64_t difference = id_width - id_length;
    while (difference) {
        fputc(' ', file);
    }
    fprintf(file, ID_FORMAT);
#undef ID_FORMAT

    switch (instruction->type) {
    case IR_IMMEDIATE:
        fprintf(file, "%"PRId64, instruction->value.immediate);
        break;
    default:
        TODO("Handle IRType %d\n", instruction->type);
        break;
    }
    putchar('\n');
}

void ir_femit_block(FILE* file, IRBlock* block)
{
    TODO();
}

void ir_femit_function(FILE* file, IRFunction* function)
{
    TODO();
}

void ir_femit(FILE* file, CodegenContext* context)
{
    TODO();
}

void ir_set_ids(CodegenContext* context) {
    size_t instruction_id = 0;
    for (IRFunction* function = context->function; function; function = function->next) {
        for (IRBlock* block = function->first; block; block = block->next) {
            for (IRInstruction* instruction = block->instructions; instruction; instruction = instruction->next) {
                instruction->id = ++instruction_id;
            }
        }
    }
}

void ir_add_function_call_argument(CodegenContext* context, IRInstruction* call, IRInstruction* argument)
{
    IRCallArgument* new_argument = calloc(1, sizeof(IRCallArgument));
    ASSERT(new_argument, "Could not allocate memory for new_argument.");

    IRCallArgument* arguments = call->value.call.arguments;
    for (; arguments->next; arguments = arguments->next);
    arguments->next = new_argument;
}

IRBlock* ir_block_create()
{
    IRBlock* block = calloc(1, sizeof(IRBlock));
    ASSERT(block, "Could not allocate memory for new first IRBlock of new IRFunction.");
    INSTRUCTION(first, IR_RETURN);
    block->branch = first;
    return block;
}

IRFunction* ir_function_create()
{
    IRFunction* function = calloc(1, sizeof(IRFunction));
    ASSERT(function, "Could not allocate memory for new IRFunction.");
    return function;
}

IRFunction* ir_function(CodegenContext* context) {
    IRFunction* function = ir_function_create();
    // A function *must* contain at least one block, so we start new
    // functions out with an empty block.
    IRBlock* block = ir_block_create();

    function->next = context->function;

    function->first = block;
    function->last = block;

    context->function = function;
    context->block = block;

    return function;
}

void ir_add_function_arg(CodegenContext* context, IRInstruction* arg)
{
    TODO();
}

IRInstruction* ir_external_call
(CodegenContext* context,
 const char* function_name)
{
    TODO();
}

IRInstruction* ir_immediate
(CodegenContext* context,
 int64_t immediate)
{
    INSTRUCTION(imm, IR_IMMEDIATE);
    imm->value.immediate = immediate;
    ir_insert(context, imm);
    return imm;
}

IRInstruction* ir_load
(CodegenContext* context,
 IRInstruction* address)
{
    INSTRUCTION(load, IR_LOAD);
    load->value.reference = address;
    ir_insert(context, load);
    return load;
}

IRInstruction* ir_internal_call
(CodegenContext* context,
 IRInstruction* function)
{
    TODO();
}

IRInstruction* ir_load_global_address
(CodegenContext* context,
 const char* name)
{
    TODO();
}

IRInstruction* ir_comparison
(CodegenContext* context,
 enum ComparisonType type,
 IRInstruction* lhs,
 IRInstruction* rhs)
{
    TODO();
}

IRInstruction* ir_load_local_address
(CodegenContext* context,
 int64_t offset) {
    TODO();
}

void ir_load_global_address_into
(CodegenContext* context,
 const char* name,
 IRInstruction* target)
{
    TODO();
}

void ir_load_local_address_into
(CodegenContext* context,
 long long int offset,
 IRInstruction* target)
{
    TODO();
}

IRInstruction* ir_load_global
(CodegenContext* context,
 const char* name)
{
    TODO();
}

IRInstruction* ir_load_local
(CodegenContext* context,
 long long int offset)
{
    TODO();
}

void ir_load_global_into
(CodegenContext* context,
 const char* name,
 IRInstruction* target)
{
    TODO();
}

void ir_load_local_into
(CodegenContext* context,
 long long int offset,
 IRInstruction* target)
{
    TODO();
}

IRInstruction* ir_store_global
(CodegenContext* context,
 IRInstruction* source,
 const char* name)
{
    TODO();
}

IRInstruction* ir_store_local
(CodegenContext* context,
 IRInstruction* source,
 IRInstruction* local)
{
    TODO();
}

IRInstruction* ir_store
(CodegenContext* context,
 IRInstruction* data,
 IRInstruction* address)
{
    TODO();
}

void ir_add_immediate
(CodegenContext* context,
 IRInstruction* reg,
 long long int immediate)
{
    TODO();
}

IRInstruction* ir_branch_conditional
(CodegenContext* context,
 IRInstruction* conditional,
 IRBlock* then_block,
 IRBlock* otherwise_block)
{
    TODO();
}

IRInstruction* ir_branch
(CodegenContext* context,
 IRBlock* destination)
{
    TODO();
}

IRInstruction* ir_load_immediate
(CodegenContext* context,
 long long int immediate)
{
    TODO();
}

IRInstruction* ir_add
(CodegenContext* context,
 IRInstruction* lhs,
 IRInstruction* rhs)
{
    TODO();
}

IRInstruction* ir_subtract
(CodegenContext* context,
 IRInstruction* lhs,
 IRInstruction* rhs)
{
    TODO();
}

IRInstruction* ir_multiply
(CodegenContext* context,
 IRInstruction* lhs,
 IRInstruction* rhs)
{
    TODO();
}

IRInstruction* ir_divide
(CodegenContext* context,
 IRInstruction* lhs,
 IRInstruction* rhs)
{
    TODO();
}

IRInstruction* ir_modulo
(CodegenContext* context,
 IRInstruction* lhs,
 IRInstruction* rhs)
{
    TODO();
}

IRInstruction* ir_shift_left
(CodegenContext* context,
 IRInstruction* lhs,
 IRInstruction* rhs)
{
    TODO();
}

IRInstruction* ir_shift_right_arithmetic
(CodegenContext* context,
 IRInstruction* lhs,
 IRInstruction* rhs)
{
    TODO();
}

IRInstruction* ir_stack_allocate
(CodegenContext* context,
 int64_t size)
{
    TODO();
}

void ir_set_return_value(CodegenContext* context, IRFunction* function, IRInstruction* value)
{
    TODO();
}
