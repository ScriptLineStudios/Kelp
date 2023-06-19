#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include <string.h>
#include <stdint.h>

Opcode string_to_opcode(char *string) {
    if      (!strcmp(string, "nop"))    return NOP;
    else if (!strcmp(string, "push"))   return PUSH;
    else if (!strcmp(string, "addi"))   return ADDI;
    else if (!strcmp(string, "addf"))   return ADDF;
    else if (!strcmp(string, "subi"))   return SUBI;
    else if (!strcmp(string, "subf"))   return SUBF;
    else if (!strcmp(string, "divi"))   return DIVI;
    else if (!strcmp(string, "divf"))   return DIVF;
    else if (!strcmp(string, "muli"))   return MULI;
    else if (!strcmp(string, "mulf"))   return MULF;
    else if (!strcmp(string, "shr"))    return SHR;
    else if (!strcmp(string, "shl"))    return SHL;
    else if (!strcmp(string, "printi")) return PRINTI;
    else if (!strcmp(string, "printf")) return PRINTF;
    else if (!strcmp(string, "jmp"))    return JMP;
    else if (!strcmp(string, "jg"))     return JG;
    else                                return NOP;
}

#endif