#include <codegen/register_allocation.h>

#include <codegen.h>
#include <stdlib.h>
#include <codegen/intermediate_representation.h>

RegisterAllocationInfo* ra_allocate_info
(CodegenContext* context,
    Register result_register,
    size_t general_registers_count,
    Register* general_registers,
    size_t argument_registers_count,
    Register* argument_registers
)
{
    if (!context) { return NULL; }
    if (general_registers_count == 0) { return NULL; }
    if (!general_registers) {  return NULL; }

    RegisterAllocationInfo* info = calloc(1, sizeof(*info));

    info->context = context;
    info->result_register = result_register;

    info->register_count = general_registers_count;
    info->registers = general_registers;

    info->argument_register_count = argument_registers_count;
    info->argument_registers = argument_registers;

    return info;
}

// Insert instruction A before instruction B.
void insert_instruction_before(IRInstruction* a, IRInstruction* b) {
    if (!a || !b) { return; }

    //  0 - b - 1
    //  0 - a - b - 1

    a->previous = b->previous;

    if (b->previous) {
        b->previous->next = a;
    }
    b->previous = a;

    a->next = b;

    // TODO: Handle beginning/end of block stuffs.
}


// Insert instruction A after instruction B.
void insert_instruction_after(IRInstruction* a, IRInstruction* b) {
    if (!a || !b) { return; }

    //  0 - b - 1
    //  0 - b - a - 1

    if (b->next) {
        b->next->previous = a;
    }
    a->next = b->next;
    b->next = a;

    a->previous = b;

    // TODO: Handle beginning/end of block stuffs.
}

// ===== BEG REGISTER ALLOCATION PASSES =====

void phi2copy(RegisterAllocationInfo* info) {
    for (IRFunction* function = info->context->all_functions; function; function = function->next) {
        for (IRBlock* block = function->first; block; block = block->next) {
            for (IRInstruction* instruction = block->instructions; instruction; instruction = instruction->next) {
                if (instruction->type == IR_PHI) {
                    IRPhiArgument* phi = instruction->value.phi_argument;

                    // Single PHI argument means that we can replace it with a simple copy.
                    if (phi && !phi->next) {
                        instruction->type = IR_COPY;
                        instruction->value.reference = phi->value;
                        continue;
                    }

                    // For each of the PHI arguments, we basically insert a copy.
                    // Where we insert it depends on some complicated factors
                    // that have to do with control flow.
                    for (; phi; phi = phi->next) {
                        IRInstruction* argument = phi->value;
                        IRInstruction* copy = ir_copy(info->context, argument);

                        insert_instruction_after(copy, argument);

                        mark_used(argument, copy);
                        mark_used(copy, instruction);

                        // Remove use of PHI argument in PHI; it's now used in the copy instead.
                        Use* previous_use = NULL;
                        for (Use* use = argument->uses; use; previous_use = use, use = use->next) {
                            if (use->user == instruction) {
                                if (previous_use) {
                                    previous_use->next = use->next;
                                } else {
                                    argument->uses = use;
                                }
                            }
                        }
                        phi->value = copy;
                    }
                }
            }
        }
    }
}

void function_call_arguments(RegisterAllocationInfo* info) {
    for (IRFunction* function = info->context->all_functions; function; function = function->next) {
        for (IRBlock* block = function->first; block; block = block->next) {
            for (IRInstruction* instruction = block->instructions; instruction; instruction = instruction->next) {
                if (instruction->type == IR_CALL) {
                    IRCallArgument* arguments = instruction->value.call.arguments;
                    for (size_t i = 0; arguments; ++i, arguments = arguments->next) {
                        IRInstruction* argument = arguments->value;
                        IRInstruction* arg_copy = ir_copy(info->context, argument);
                        if (i >= info->argument_register_count) {
                            TODO("Handle stack allocated function parameters, somehow :P");
                        }
                        arg_copy->result = info->argument_registers[i];
                        insert_instruction_before(arg_copy, instruction);
                        arguments->value = arg_copy;
                    }
                }
            }
        }
    }
}

void function_return_values(RegisterAllocationInfo* info) {
    for (IRFunction* function = info->context->all_functions; function; function = function->next) {
        function->return_value->result = info->result_register;
    }
}

// ===== END REGISTER ALLOCATION PASSES =====

// ===== BEG INSTRUCTION LISTS =====

typedef struct IRInstructionList {
    IRInstruction* instruction;
    struct IRInstructionList* next;
} IRInstructionList;

IRInstructionList* collect_instructions(RegisterAllocationInfo* info) {
    IRInstructionList* list = NULL;
    IRInstructionList* list_it = NULL;
    for (IRFunction* function = info->context->all_functions; function; function = function->next) {
        for (IRBlock* block = function->first; block; block = block->next) {
            for (IRInstruction* instruction = block->instructions; instruction; instruction = instruction->next) {
                // Add instruction to flat list iff instruction needs register
                // allocated.
                switch (instruction->type) {
                case IR_ADD:
                case IR_SUBTRACT:
                case IR_LOAD:
                case IR_LOCAL_LOAD:
                case IR_LOCAL_ADDRESS:
                case IR_GLOBAL_LOAD:
                case IR_GLOBAL_ADDRESS:
                case IR_PHI:
                case IR_COPY:
                case IR_IMMEDIATE:
                case IR_COMPARISON:
                case IR_CALL:
                case IR_PARAMETER_REFERENCE:
                    if (list_it) {
                        list_it->next = calloc(1, sizeof(IRInstructionList));
                        list_it = list_it->next;
                    } else {
                        list_it = calloc(1, sizeof(IRInstructionList));
                        list = list_it;
                    }
                    list_it->instruction = instruction;
                    break;
                default:
                    break;
                }
            }
        }
    }

    return list;
}

void print_instruction_list(IRInstructionList* list) {
    for (; list; list = list->next) {
        ir_femit_instruction(stdout, list->instruction);
    }
}

// ===== END INSTRUCTION LISTS =====

void ra(RegisterAllocationInfo* info) {
    if (!info) { return; }

    phi2copy(info);

    function_call_arguments(info);
    function_return_values(info);

    IRInstructionList* instructions = collect_instructions(info);

    ir_set_ids(info->context);

    print_instruction_list(instructions);
    // ir_femit(stdout, info->context);
}
