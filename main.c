#include <stdio.h>
#include <stdlib.h>

#define KELP_IMPLEMENTATION
#include "kelp.h"

int main(void) {
    Instructions *instructions = instructions_init();
    emit_instruction(instructions, make_instruction(PUSH, make_operand(0)));
    emit_instruction(instructions, make_instruction(PRINTF, NO_OPERAND));
    emit_instruction(instructions, make_instruction(JG, make_operand(0)));

    Kvm *kvm = kvm_init();
    
    kvm_execute_program(kvm, instructions);

    write_instructions_to_file(instructions, "out.dump");
    instructions_free(instructions);
    return 0;
}
