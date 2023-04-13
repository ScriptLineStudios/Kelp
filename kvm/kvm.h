#ifndef KVM_H
#define KVM_H

typedef struct {
    Operand *stack;
    size_t stack_size;
} Kvm;

#define NEXT_INSTRUCTION do {ip++; break;} while(0);

#endif