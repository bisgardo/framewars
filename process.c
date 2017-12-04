#include "process.h"

#include <stdio.h>
#include <stdlib.h>

Proc *proc_create() {
    Proc *proc = malloc(sizeof(Proc));

    proc->prev = proc;
    proc->next = proc;
    proc->first_instr = 0;
    proc->last_instr = 0;

    return proc;
}

void proc_destroy(Proc *proc) {
    free(proc);
}

void proc_print(Proc *proc) {
    Instr *instr;
    for (instr = proc->first_instr; instr; instr = instr->next) {
        instr_print(instr);
    }
}

void proc_add_instr(Proc *proc, Instr *instr) {
    Instr *last = proc->last_instr;

    if (last) {
        instr_sequence(last, instr);
        proc->last_instr = instr;
    } else {
        proc->first_instr = instr;
        proc->last_instr = instr;
    }
}

Instr *proc_instr(Proc *proc, uint n) {
    Instr *instr = proc->first_instr;
    return instr_succ(instr, n);
}
