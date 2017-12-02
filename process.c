#include "process.h"

#include <stdio.h>
#include <stdlib.h>

Process *process_create() {
    Process *process = malloc(sizeof(Process));

    process->prev = process;
    process->next = process;
    process->first_instruction = 0;
    process->last_instruction = 0;

    return process;
}

void process_destroy(Process *process) {
    free(process);
}

void process_print(Process *process) {
    Instruction *instruction;
    for (instruction = process->first_instruction; instruction; instruction = instruction->next) {
        instruction_print(instruction);
    }
}

void process_add_instruction(Process *process, Instruction *instruction) {
    Instruction *last = process->last_instruction;

    if (last) {
        instruction_sequence(last, instruction);
        process->last_instruction = instruction;
    } else {
        process->first_instruction = instruction;
        process->last_instruction = instruction;
    }
}

Instruction *process_instruction(Process *process, uint n) {
    Instruction *instruction = process->first_instruction;
    return instruction_succ(instruction, n);
}
