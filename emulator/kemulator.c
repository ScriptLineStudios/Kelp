#include <stdio.h>
#include <stdlib.h>

#define KELP_IMPLEMENTATION
#include "../kelp.h"

void usage() {
    printf("Usage: ./kemulator [YOUR_KELP_EXECUTABLE].kelp");
}

void emulate(const char *filename) {
    Instructions *program = read_instructions_from_file(filename);

    Kvm *kvm = kvm_init();
    kvm_execute_program(kvm, program);
    kvm_free(kvm);
}

int main(int argc, char **argv) {
    if (argc <= 1) {
        usage();
        exit(1);
    }
    emulate(argv[1]);
}

