#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include "types.h"

typedef enum Code Code;
typedef enum Mode Mode;
typedef struct Arg Arg;
typedef struct Instruction Instruction;

enum Code {
    DAT,
    MOV,
    ADD,
    SUB,
    JMP,
    JMZ,
    DJZ,
    CMP
};

enum Mode {
    IMD,
    REL,
    IND
};

struct Arg {
    int mode;
    int val;
};

struct Instruction {
    Instruction *prev;
    Instruction *next;
    int code;
    Arg a;
    Arg b;
};

Arg arg_create(int mode, int val);

Instruction *instruction_create(int code, Arg a, Arg b);

void instruction_destroy(Instruction *instruction);

char *instruction_code_name(int code);

char *instruction_mode_name(int mode);

Instruction instruction_parse(uint instr);

Instruction *instruction_pred(Instruction *instruction, int n);

Instruction *instruction_succ(Instruction *instruction, int n);

Instruction *instruction_first(Instruction *instruction);

Instruction *instruction_last(Instruction *instruction);

void instruction_sequence(Instruction *prev, Instruction *next);

uint instruction_instr(Instruction *instruction);

void instruction_print(Instruction *instruction);

//void instruction_execute(uint instr, Player *player);

#endif /* INSTRUCTION_H */
