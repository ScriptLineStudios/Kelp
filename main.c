#include <stdio.h>
#include <stdlib.h>

#define KELP_IMPLEMENTATION
#include "kelp.h"

int main(void) {
    Instructions *instructions = instructions_init();
    emit_instruction(instructions, make_instruction(NOP, (Operand){0}));
    emit_instruction(instructions, make_instruction(PUSH, (Operand){0}));
    emit_instruction(instructions, make_instruction(PUSH, (Operand){0}));
    emit_instruction(instructions, make_instruction(PUSH, (Operand){0}));

    printf("Instructions = %ld\n", instructions->num_instructions);
    write_instructions_to_file(instructions, "out.dump");
    instructions_free(instructions);
    instructions = read_instructions_from_file("out.dump");
    printf("Instructions = %ld\n", instructions->num_instructions);
    printf("%d\n", instructions->instructions[0].opcode);
    printf("%d\n", instructions->instructions[1].opcode);
    printf("%d\n", instructions->instructions[2].opcode);
    printf("%d\n", instructions->instructions[3].opcode);

    return 0;
}
