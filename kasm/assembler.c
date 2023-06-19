#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

#define KELP_IMPLEMENTATION
#include "../kelp.h"

#define STR_HEADER_IMPLEMENTATION
#include "../tools/str_header.h"

#define HASH_IMPLEMENTATION
#include "../tools/hash.h"

#include "instructions.h"

void usage(void) {
    printf("Usage: ./kasma [YOUR_CODE].kasm\n");
}

/*
    TODO:
        - more arethmatic instructions
        - command line tool for loading *.kelp files
        - compilation to x86_64 
        - labels and macros for assembler
*/

void assemble(char *filename) {
    FILE *file = fopen(filename, "r");
    StrReader *reader = str_reader_new(file);

    Instructions *instructions = instructions_init();

    size_t free_count = 0;
    void **frees = malloc(sizeof(void *) * free_count);
    while (!feof(file)) {
        Str *line = str_trim_left(str_read_line(reader));
        StrArray *split = str_split_by(line, ' ');

        if (str_in(line, '%')) {
            StrArray *s = str_split_by(line, '%');
            Str *name = s->strs[1];
            printf("name = %s\n", name->string);
        }

        free_count++;
        frees = realloc(frees, sizeof(void *) * free_count);
        frees[free_count - 1] = (void *)split; 

        free_count++;
        frees = realloc(frees, sizeof(void *) * free_count);
        frees[free_count - 1] = (void *)line; 

        Str *opcode = split->strs[0]; //important to remeber these are not being allocated and are just references
        Str *operand = split->strs[1];
        printf("%s\n", opcode->string);
        
        switch (string_to_opcode(opcode->string)) {
            case NOP:
                break;
            case PUSH:
                emit_instruction(instructions, make_instruction(PUSH, make_operand(atof(operand->string))));
                break;
            case ADDI:
                emit_instruction(instructions, make_instruction(ADDI, NO_OPERAND));
                break;
            case ADDF:
                emit_instruction(instructions, make_instruction(ADDF, NO_OPERAND));
                break;
            case PRINTI:
                emit_instruction(instructions, make_instruction(PRINTI, NO_OPERAND));
                break;
            case PRINTF:
                emit_instruction(instructions, make_instruction(PRINTF, NO_OPERAND));
                break;
            case JMP:
                emit_instruction(instructions, make_instruction(JMP, make_operand(atoi(operand->string))));
                break;
            case JG:
                emit_instruction(instructions, make_instruction(JG, make_operand(atoi(operand->string))));
                break;
            case SUBI:
                emit_instruction(instructions, make_instruction(SUBI, NO_OPERAND));
                break;
            case SUBF:
                emit_instruction(instructions, make_instruction(SUBF, NO_OPERAND));
                break;
            case MULI:
                emit_instruction(instructions, make_instruction(MULI, NO_OPERAND));
                break;
            case MULF:
                emit_instruction(instructions, make_instruction(MULF, NO_OPERAND));
                break; 
            case DIVI:
                emit_instruction(instructions, make_instruction(DIVI, NO_OPERAND));
                break;
            case DIVF:
                emit_instruction(instructions, make_instruction(DIVF, NO_OPERAND));
                break; 
            case SHL:
                emit_instruction(instructions, make_instruction(SHL, NO_OPERAND));
                break;
            case SHR:
                emit_instruction(instructions, make_instruction(SHR, NO_OPERAND));
                break;
            default:
                printf("unknown instruction: %s\n", opcode->string);
                exit(1);
        }
    }
    printf("free count = %ld\n", free_count);
    for (size_t i = 0; i < free_count; i++) {
        str_free(frees[i]);
    }
    free(frees);
    str_reader_free(reader);
    write_instructions_to_file(instructions, "out.kelp");
    instructions_free(instructions);
}

int main(int argc, char **argv) {
    if (argc <= 1) {
        usage();
        exit(1);
    }

    assemble(argv[1]);

    return 0;
}