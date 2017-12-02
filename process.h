#ifndef PROCESS_H
#define PROCESS_H

#include "instruction.h"
#include "types.h"

typedef struct Process Process;

struct Process {
    Process *prev;
    Process *next;
    Instr *first_instr;
    Instr *last_instr;
    uint pc;
};

Process *process_create();

void process_destroy(Process *process);

void process_print(Process *process);

void process_add_instr(Process *process, Instr *instr);

Instr *process_instr(Process *process, uint n);

#endif /* PROCESS_H */
