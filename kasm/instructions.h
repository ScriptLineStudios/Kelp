#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include <string.h>
#include <stdint.h>

Opcode string_to_opcode(const char *string) {
    if (!strcmp(string, "nop"))         return NOP;
    else if (!strcmp(string, "push"))   return PUSH;
    else if (!strcmp(string, "addi"))   return ADDI;
    else if (!strcmp(string, "addf"))   return ADDF;
    else if (!strcmp(string, "printi")) return PRINTI;
    else if (!strcmp(string, "printf")) return PRINTF;
    else if (!strcmp(string, "jmp"))    return JMP;
    else if (!strcmp(string, "jg"))     return JG;
    else                                return NOP;
}

#endif