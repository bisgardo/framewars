#include "process.h"

#include <stdio.h>
#include <stdlib.h>

Process *process_create() {
    Process *process = malloc(sizeof(Process));

    process->prev = process;
    process->next = process;
    process->first_instr = 0;
    process->last_instr = 0;

    return process;
}

void process_destroy(Process *process) {
    free(process);
}

void process_print(Process *process) {
    Instr *instr;
    for (instr = process->first_instr; instr; instr = instr->next) {
        instr_print(instr);
    }
}

void process_add_instr(Process *process, Instr *instr) {
    Instr *last = process->last_instr;

    if (last) {
        instr_sequence(last, instr);
        process->last_instr = instr;
    } else {
        process->first_instr = instr;
        process->last_instr = instr;
    }
}

Instr *process_instr(Process *process, uint n) {
    Instr *instr = process->first_instr;
    return instr_succ(instr, n);
}
