#ifndef KELP_H
#define KELP_H


typedef enum {
    NOP, PUSH, ADDI, ADDF, SUBI, SUBF, MULI, MULF, DIVI, DIVF, SHL, SHR, PRINTI, PRINTF, JMP, JG, 
} Opcode;

typedef struct {
    int as_int;
    float as_float;
} Operand;

typedef struct {
    Opcode opcode;
    Operand operand;
} Instruction;

typedef struct {
    Instruction *instructions;
    size_t num_instructions;
} Instructions;

Instructions *instructions_init();
void instructions_free(Instructions *instructions);

void emit_instruction(Instructions *instructions, Instruction instruction);
void write_instructions_to_file(Instructions *instructions, const char *filename); 
Instructions *read_instructions_from_file(const char *filename); 

#include "kvm/kvm.h"
void kvm_execute_program(Kvm *kvm, Instructions *instructions);

Operand make_operand(float value);

#define RESIZE_INSTRUCTIONS instructions->instructions = realloc(instructions->instructions, sizeof(Instruction) * instructions->num_instructions)
#define UNUSED(x) (void)x
#define NO_OPERAND (Operand) {0}

#endif
#ifdef KELP_IMPLEMENTATION

#include "kvm/kvm.c"

Operand make_operand(float value) {
    Operand operand;
    operand.as_int = (int)value;
    operand.as_float = (float)value;
    return operand;
}

Instruction make_instruction(Opcode opcode, Operand operand) {
    return (Instruction){.opcode = opcode, .operand = operand};
}

void write_instructions_to_file(Instructions *instructions, const char *filename) {
    FILE * file= fopen(filename, "wb");

    fwrite(&instructions->num_instructions, sizeof(size_t), 1, file);
    for (size_t i = 0; i < instructions->num_instructions; i++) {
        fwrite(&(instructions->instructions[i]), sizeof(Instruction), 1, file);
    }
    fclose(file);
}

Instructions *instructions_from_data(Instruction *instruction_list, size_t num_instructions) {
    Instructions *instructions = (Instructions *)malloc(sizeof(Instructions)); 
    instructions->num_instructions = num_instructions;
    instructions->instructions = instruction_list;
    return instructions;
}

Instructions *read_instructions_from_file(const char *filename) {
    FILE * file= fopen(filename, "rb");

    size_t num_instructions;
    int res = fread(&num_instructions, sizeof(size_t), 1, file);
    UNUSED(res);

    Instruction *instructions = malloc(sizeof(Instruction) * num_instructions);

    for (size_t i = 0; i < num_instructions; i++) {
        Instruction instruction;
        res = fread(&instruction, sizeof(Instruction), 1, file);
        instructions[i] = instruction;
    }

    fclose(file);
    return instructions_from_data(instructions, num_instructions);
}


void emit_instruction(Instructions *instructions, Instruction instruction) {
    instructions->num_instructions += 1;
    RESIZE_INSTRUCTIONS;
    instructions->instructions[instructions->num_instructions - 1] = instruction;
}

Instructions *instructions_init() {
    Instructions *instructions = (Instructions *)malloc(sizeof(Instructions)); 
    instructions->num_instructions = 0;
    instructions->instructions = malloc(sizeof(Instruction) * instructions->num_instructions);
    return instructions;
}

void instructions_free(Instructions *instructions) {
    free(instructions->instructions);
    free(instructions);
}

#endif