#include "kvm.h"
#include <string.h>

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

#define PYTHON_IF do{\
    char iff[200];\
    sprintf(iff, "    if ci == %ld:\n", ci);\
    ci++;\
    fwrite(iff, strlen(iff), 1, file);\
}while(0)\

void kvm_dispatch_python_transpilation(Instructions *instructions) {
    FILE *file = fopen("kelp_python.py", "w");
    
    const char *header = "stack = []\n";
    fwrite(header, strlen(header), 1, file);

    char line[200];
    sprintf(line, "ni=%ld\nci=0\nwhile ci < ni:\n", instructions->num_instructions);
    fwrite(line, strlen(line), 1, file);
    size_t ci = 0;
    for (int i = 0; i < instructions->num_instructions; i++) {
        Instruction inst = instructions->instructions[i];
        switch (inst.opcode) {
            case NOP: {
            }
                break;
            case PUSH: {
                PYTHON_IF;

                char line[200];
                sprintf(line, "        stack.append(%f)\n        ci+=1\n", inst.operand.as_float);
                fwrite(line, strlen(line), 1, file);
            }
                break;
            case ADDI: {
                PYTHON_IF;

                char line[200] = "        a = stack.pop()\n        b = stack.pop()\n        stack.append(int(a + b))\n        ci+=1\n";
                fwrite(line, strlen(line), 1, file);
            }
                break;
            case ADDF: {
                PYTHON_IF;

                char line[200] = "        a = stack.pop()\n        b = stack.pop()\n        stack.append(float(a + b))\n        ci+=1\n";
                fwrite(line, strlen(line), 1, file);
            }
                break;
            case SUBI: {
                PYTHON_IF;

                char line[200] = "        a = stack.pop()\n        b = stack.pop()\n        stack.append(int(b - a))\n        ci+=1\n";
                fwrite(line, strlen(line), 1, file);
            }
                break;
            case SUBF: {
                PYTHON_IF;

                char line[200] = "        a = stack.pop()\n        b = stack.pop()\n        stack.append(float(b - a))\n        ci+=1\n";
                fwrite(line, strlen(line), 1, file);
            }
                break;
            case DIVI: {
                PYTHON_IF;

                char line[200] = "        a = stack.pop()\n        b = stack.pop()\n        stack.append(int(a / b))\n        ci+=1\n";
                fwrite(line, strlen(line), 1, file);
            }
                break;
            case DIVF: {
                PYTHON_IF;

                char line[200] = "        a = stack.pop()\n        b = stack.pop()\n        stack.append(float(a / b))\n        ci+=1\n";
                fwrite(line, strlen(line), 1, file);
            }
                break;
            case MULI: {
                PYTHON_IF;

                char line[200] = "        a = stack.pop()\n        b = stack.pop()\n        stack.append(int(a * b))\n        ci+=1\n";
                fwrite(line, strlen(line), 1, file);
            }
                break;
            case MULF: {
                PYTHON_IF;

                char line[200] = "        a = stack.pop()\n        b = stack.pop()\n        stack.append(float(a * b))\n        ci+=1\n";
                fwrite(line, strlen(line), 1, file);
            }
                break;
            case SHR: {
            }
                break;
            case SHL: {
            }
                break;
            case PRINTI: {
                PYTHON_IF;

                char line[200] = "        print(int(stack[len(stack) - 1]))\n        ci+=1\n";
                fwrite(line, strlen(line), 1, file);
            }
                break;
            case PRINTF: {
                PYTHON_IF;

                char line[200] = "        print(stack[len(stack) - 1])\n        ci+=1\n";
                fwrite(line, strlen(line), 1, file);
            }
                break;
            case JMP: {
            }
                break;
            case JG: {
                PYTHON_IF;

                char line[200];
                sprintf(line, "        if stack[len(stack) - 1] > 0:\n            ci=%d\n", inst.operand.as_int);
                fwrite(line, strlen(line), 1, file);

                sprintf(line, "        else:\n            ci+=1\n", inst.operand.as_int);
                fwrite(line, strlen(line), 1, file);
            }
                break;
            default: {
                printf("ERROR: Unknown opcode %ld\n", (size_t)inst.opcode);
                exit(1);
            } 
        }
    }
    fclose(file);
}

void kvm_transpile(Instructions *instructions, KelpTranspileTarget target) {
    switch (target) {
        case KVM_PYTHON: {
                kvm_dispatch_python_transpilation(instructions);
            }
            break;
        default:
            printf("ERROR: Unknown transpilation target!\n");
            exit(1);
    }
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