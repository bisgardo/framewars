#ifndef PROCESS_H
#define PROCESS_H

#include "instruction.h"
#include "types.h"

typedef struct Process Process;

struct Process {
    Process *prev;
    Process *next;
    Instruction *first_instruction;
    Instruction *last_instruction;
    uint pc;
};

Process *process_create();

void process_destroy(Process *process);

void process_print(Process *process);

void process_add_instruction(Process *process, Instruction *instruction);

Instruction *process_instruction(Process *process, uint n);

#endif /* PROCESS_H */
