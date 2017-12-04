#ifndef PROCESS_H
#define PROCESS_H

#include "instruction.h"
#include "types.h"

typedef struct proc Proc;
struct proc {
    Proc *prev;
    Proc *next;
    Instr *first_instr;
    Instr *last_instr;
    uint pc;
};

Proc *proc_create();

void proc_destroy(Proc *proc);

void proc_print(Proc *proc);

void proc_add_instr(Proc *proc, Instr *instr);

Instr *proc_instr(Proc *proc, uint n);

#endif /* PROCESS_H */
