#include "kvm.h"

Kvm *kvm_init() {
    Kvm *kvm = (Kvm*)malloc(sizeof(Kvm));
    kvm->stack_size = 0;
    kvm->stack = malloc(sizeof(Operand) * kvm->stack_size);
    return kvm;
}

void kvm_free(Kvm *kvm) {
    free(kvm->stack);
    free(kvm);
}

void push(Kvm *kvm, Operand operand) {
    kvm->stack_size++;
    kvm->stack = realloc(kvm->stack, sizeof(Operand) * kvm->stack_size);
    kvm->stack[kvm->stack_size - 1] = operand;
}

Operand pop(Kvm *kvm) {
    Operand operand = kvm->stack[kvm->stack_size - 1];
    kvm->stack_size--;
    kvm->stack = realloc(kvm->stack, sizeof(Operand) * kvm->stack_size);
    return operand;
}

Operand peek(Kvm *kvm) {
    return kvm->stack[kvm->stack_size - 1];
}

void kvm_execute_program(Kvm *kvm, Instructions *instructions) {
    size_t ip = 0;
    while (ip < instructions->num_instructions) {
        Instruction inst = instructions->instructions[ip];
        switch (inst.opcode) {
            case NOP: {
                ip++;
            }
                break;
            case PUSH: {
                push(kvm, inst.operand);
                ip++;
            }
                break;
            case ADDI: {
                Operand a = pop(kvm);
                Operand b = pop(kvm);
                push(kvm, make_operand(a.as_int + b.as_int));
                ip++;
            }
                break;
            case ADDF: {
                Operand a2 = pop(kvm);
                Operand b2 = pop(kvm);
                push(kvm, make_operand(a2.as_float + b2.as_float));
                ip++;
            }
                break;
            case SUBI: {
                Operand a = pop(kvm);
                Operand b = pop(kvm);
                push(kvm, make_operand(b.as_int - a.as_int));
                ip++;
            }
                break;
            case SUBF: {
                Operand a2 = pop(kvm);
                Operand b2 = pop(kvm);
                push(kvm, make_operand(b2.as_float - a2.as_float));
                ip++;
            }
                break;
            case DIVI: {
                Operand a = pop(kvm);
                Operand b = pop(kvm);
                push(kvm, make_operand(b.as_int / a.as_int));
                ip++;
            }
                break;
            case DIVF: {
                Operand a2 = pop(kvm);
                Operand b2 = pop(kvm);
                push(kvm, make_operand(b2.as_float / a2.as_float));
                ip++;
            }
                break;
            case MULI: {
                Operand a = pop(kvm);
                Operand b = pop(kvm);
                push(kvm, make_operand(b.as_int * a.as_int));
                ip++;
            }
                break;
            case MULF: {
                Operand a2 = pop(kvm);
                Operand b2 = pop(kvm);
                push(kvm, make_operand(b2.as_float * a2.as_float));
                ip++;
            }
                break;
            case SHR: {
                Operand a = pop(kvm);
                push(kvm, make_operand(a.as_int >> 1));
                ip++;
            }
                break;
            case SHL: {
                Operand a2 = pop(kvm);
                push(kvm, make_operand(a2.as_int << 1));
                ip++;
            }
                break;
            case PRINTI: {
                printf("%d\n", peek(kvm).as_int);
                ip++;
            }
                break;
            case PRINTF: {
                printf("%f\n", peek(kvm).as_float);
                ip++;
            }
                break;
            case JMP: {
                ip = inst.operand.as_int;
            }
                break;
            case JG: {
                if (peek(kvm).as_int > 0) {
                    ip = inst.operand.as_int;
                }
                else {
                    ip++;
                }
            }
                break;
            default: {
                printf("ERROR: Unknown opcode %ld\n", (size_t)inst.opcode);
                exit(1);
            } 
        }
    }
}