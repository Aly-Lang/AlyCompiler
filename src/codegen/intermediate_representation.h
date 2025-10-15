#ifndef ALY_COMPILER_INTERMEDIATE_REPRESENTATION_H
#define ALY_COMPILER_INTERMEDIATE_REPRESENTATION_H

#include <codegen.h>
#include <codegen/codegen_forward.h>
#include <inttypes.h>

#define INSTRUCTION(name, given_type)                        \
	IRInstruction* (name) = calloc(1, sizeof(IRInstruction)); \
	ASSERT((name), "Could not allocate new IRInstruction.");   \
	(name)->type = (given_type);

typedef enum IRType {
    IR_IMMEDIATE,
    IR_CALL,
	IR_RETURN,
    IR_LOAD,
	IR_COUNT
} IRType;

typedef union IRCallValue {
    IRInstruction* callee;
    char* name;
} IRCallValue;

typedef struct IRCallArgument {
    IRInstruction* value;
    struct IRCallArgument* next;
} IRCallArgument;

typedef struct IRCall {
    IRCallValue value;
    IRCallArgument* arguments;
} IRCall;

typedef union IRValue {
    IRInstruction* reference;
    int64_t immediate;
    IRCall call;
} IRValue;

typedef struct IRInstruction {
    int type;
    IRValue value;

    // A unique identifier (mainly for debug purposes).
    size_t id;

    // Register allocation.
    size_t index;

    // Doubly-linked list.
    struct IRInstruction* previous;
    struct IRInstruction* next;
} IRInstruction;

typedef struct IRBlockPredecessor {
    IRBlock* block;
    struct IRBlockPredecessor* next;
} IRBlockPredecessor;

/// A block is a list of instructions that have control flow enter at
/// the beginnign and leave at the end.
typedef struct IRBlock {
    IRInstruction* instructions;
	IRInstruction* last_instruction;
	
    IRInstruction* branch;
    char closed;

    IRBlockPredecessor* predecessor;

    // Doubly-linked list.
    struct IRBlock* previous;
    struct IRBlock* next;
} IRBlock;

typedef struct IRFunction {
    IRBlock* first;
    IRBlock* last;

    IRInstruction* return_value;

    // Linked list.
    struct IRFunction* next;
} IRFunction;

void ir_set_ids(CodegenContext* context);

void ir_femit_instruction(FILE* file, IRInstruction* instruction);
void ir_femit_block(FILE* file, IRBlock* block);
void ir_femit_function(FILE* file, IRFunction* function);
void ir_femit(FILE* file, CodegenContext* context);

void ir_add_function_call_argument(CodegenContext* context, IRInstruction* call, IRInstruction* argument);

IRBlock* ir_block_create();

IRFunction* ir_function_create();
IRFunction* ir_function(CodegenContext* context);

void ir_insert
(CodegenContext* context,
 IRInstruction* new_instruction);

IRInstruction* ir_external_call
(CodegenContext* context,
 const char* function_name);

IRInstruction* ir_internal_call
(CodegenContext* context,
 IRInstruction* function);

IRInstruction* ir_load_global_address
(CodegenContext* context,
 const char* name);

IRInstruction* ir_immediate
(CodegenContext* context,
 int64_t immediate);

IRInstruction* ir_load
(CodegenContext* context,
 IRInstruction* address);

IRInstruction* ir_load_local_address
(CodegenContext* context,
 int64_t offset);

void ir_load_global_address_into
(CodegenContext* context,
 const char* name,
 IRInstruction* target);

void ir_load_local_address_into
(CodegenContext* context,
 long long int offset,
 IRInstruction* target);

IRInstruction* ir_load_global
(CodegenContext* context,
 const char* name);

IRInstruction* ir_load_local
(CodegenContext* context,
 long long int offset);

void ir_load_global_into
(CodegenContext* context,
 const char* name,
 IRInstruction* target);

void ir_load_local_into
(CodegenContext* context,
 long long int offset,
 IRInstruction* target);

IRInstruction* ir_store_global
(CodegenContext* context,
 IRInstruction* source,
 const char* name);

IRInstruction* ir_store_local
(CodegenContext* context,
 IRInstruction* source,
 IRInstruction* local);

IRInstruction* ir_store
(CodegenContext* context,
 IRInstruction* data,
 IRInstruction* address);

IRInstruction* ir_branch_conditional
(CodegenContext* context,
 IRInstruction* conditional,
 IRBlock* then_block,
 IRBlock* otherwise_block);

IRInstruction* ir_branch
(CodegenContext* context,
 IRBlock* destination);

IRInstruction* ir_load_immediate
(CodegenContext* context,
 long long int immediate);

IRInstruction* ir_comparison
(CodegenContext* context,
 enum ComparisonType type,
 IRInstruction* lhs,
 IRInstruction* rhs);

IRInstruction* ir_add
(CodegenContext* context,
 IRInstruction* lhs,
 IRInstruction* rhs);

IRInstruction* ir_subtract
(CodegenContext* context,
 IRInstruction* lhs,
 IRInstruction* rhs);

IRInstruction* ir_multiply
(CodegenContext* context,
 IRInstruction* lhs,
 IRInstruction* rhs);

IRInstruction* ir_divide
(CodegenContext* context,
 IRInstruction* lhs,
 IRInstruction* rhs);

IRInstruction* ir_modulo
(CodegenContext* context,
 IRInstruction* lhs,
 IRInstruction* rhs);

IRInstruction* ir_shift_left
(CodegenContext* context,
 IRInstruction* lhs,
 IRInstruction* rhs);

IRInstruction* ir_shift_right_arithmetic
(CodegenContext* context,
 IRInstruction* lhs,
 IRInstruction* rhs);

IRInstruction* ir_stack_allocate
(CodegenContext* context,
 int64_t size);

void ir_set_return_value(CodegenContext* context, IRFunction* function, IRInstruction* value);

#endif /* ALY_COMPILER_INTERMEDIATE_REPRESENTATION_H */
