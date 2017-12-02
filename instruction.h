#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include "types.h"

typedef enum {
    DAT, MOV, ADD, SUB, JMP, JMZ, DJZ, CMP
} Code;

typedef enum {
    IMD, REL, IND
} Mode;

typedef struct {
    Mode mode;
    int val;
} Arg;

typedef struct instr Instr;
struct instr {
    Instr *prev;
    Instr *next;
    int code;
    Arg a;
    Arg b;
};

Arg arg_create(Mode mode, int val);

Instr *instr_create(int code, Arg a, Arg b);

void instr_destroy(Instr *instr);

char *instr_code_name(int code);

char *instr_mode_name(int mode);

Instr instr_parse(uint encoded);

Instr *instr_pred(Instr *instr, int index);

Instr *instr_succ(Instr *instr, int index);

Instr *instr_first(Instr *instr);

Instr *instr_last(Instr *instr);

void instr_sequence(Instr *prev, Instr *next);

int instr_encode(Instr *instr);

void instr_print(Instr *instr);

/*void instr_execute(uint instr, Player *player);*/

#endif /* INSTRUCTION_H */
