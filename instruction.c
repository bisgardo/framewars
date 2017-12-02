#include "instruction.h"
#include "player.h"

#define PICK_BITS(value, from, to) ((value >> from) & ~(~0 << (to-from+1)))

#include <stdlib.h>
#include <stdio.h>

Arg arg_create(int mode, int val) {
    Arg arg = { mode, val };
    return arg;
}

Instruction *instruction_create(int code, Arg a, Arg b) {
    Instruction *instruction = malloc(sizeof(Instruction));

    instruction->prev = 0;
    instruction->next = 0;
    instruction->code = code;
    instruction->a = a;
    instruction->b = b;

    return instruction;
}

void instruction_destroy(Instruction *instruction) {
    free(instruction);
}

/* Instruction parser functions. */

int parse_val_2(uint instr) {
    return PICK_BITS(instr, 0, 11);
}

int parse_val_1(uint instr) {
    return PICK_BITS(instr, 12, 23);
}

int parse_mode_2(uint instr) {
    return PICK_BITS(instr, 24, 25);
}

int parse_mode_1(uint instr) {
    return PICK_BITS(instr, 26, 27);
}

int parse_code(uint instr) {
    return PICK_BITS(instr, 28, 31);
}

Arg parse_arg_1(uint instr) {
    Arg arg_1;
    arg_1.mode = parse_mode_1(instr);
    arg_1.val = parse_val_1(instr);
    return arg_1;
}

Arg parse_arg_2(uint instr) {
    Arg arg_2;
    arg_2.mode = parse_mode_2(instr);
    arg_2.val = parse_val_2(instr);
    return arg_2;
}

Instruction instruction_parse(uint instr) {
    Instruction instruction;
    instruction.prev = 0;
    instruction.next = 0;

    instruction.code = parse_code(instr);
    instruction.a = parse_arg_1(instr);
    instruction.b = parse_arg_2(instr);
    return instruction;
}

Instruction *instruction_pred(Instruction *instruction, int n) {
    if (n == 0) {
        return instruction;
    } else if (n < 0) {
        return instruction_succ(instruction, -n);
    }

    while (n-- > 0 && instruction) {
        instruction = instruction->prev;
    }
    return instruction;
}

Instruction *instruction_succ(Instruction *instruction, int n) {
    if (n == 0) {
        return instruction;
    } else if (n < 0) {
        return instruction_pred(instruction, -n);
    }

    while (n-- > 0 && instruction) {
        instruction = instruction->next;
    }
    return instruction;
}

Instruction *instruction_first(Instruction *instruction) {
    while (instruction->prev) {
        instruction = instruction->prev;
    }
    return instruction;
}

Instruction *instruction_last(Instruction *instruction) {
    while (instruction->next) {
        instruction = instruction->next;
    }
    return instruction;
}

void instruction_sequence(Instruction *prev, Instruction *next) {
    prev->next = next;
    next->prev = prev;
}

uint instruction_instr(Instruction *instruction) {
    Arg *a = &instruction->a;
    Arg *b = &instruction->b;

    uint code = instruction->code;
    uint mode1 = a->mode;
    uint mode2 = b->mode;
    uint val1 = a->val;
    uint val2 = b->val;

    return (code << 28)
         | (mode1 << 26)
         | (mode2 << 24)
         | (val1 << 12)
         | (val2 << 0);
}

/* Instruction execution functions. */

void dat(Arg *a, Arg *b, Player *player) {

}

void mov(Arg *a, Arg *b, Player *player) {

}

void add(Arg *a, Arg *b, Player *player) {

}

void sub(Arg *a, Arg *b, Player *player) {

}

void jmp(Arg *a, Arg *b, Player *player) {

}

void jmz(Arg *a, Arg *b, Player *player) {

}

void djz(Arg *a, Arg *b, Player *player) {

}

void cmp(Arg *a, Arg *b, Player *player) {

}

void (*handlers[])(Arg *, Arg *, Player *) = {
    dat, mov, add, sub, jmp, jmz, djz, cmp
};

char *instruction_code_name(int code) {
    char *code_names[] = {
        "dat", "mov", "add", "sub", "jmp", "jmz", "djz", "cmp"
    };

    if (0 <= code && code < 8) {
        return code_names[code];
    } else {
        return 0;
    }
}

char *instruction_mode_name(int mode) {
    char *mode_names[] = {
        "#", "", "@"
    };

    if (0 <= mode && mode < 3) {
        return mode_names[mode];
    } else {
        return 0;
    }
}

char *validate(char *code_name, char *mode_1_name, char *mode_2_name) {
    if (!code_name) {
        return "code name";
    } else if (!mode_1_name) {
        return "mode 1";
    } else if (!mode_2_name) {
        return "mode 2";
    } else {
        return 0;
    }
}

void instruction_print(Instruction *instruction) {
    int code = instruction->code;
    Arg *a = &instruction->a;
    Arg *b = &instruction->b;

    int mode_1 = a->mode;
    int mode_2 = b->mode;

    int val_1 = a->val;
    int val_2 = b->val;

    char *code_name = instruction_code_name(code);
    char *mode_1_name = instruction_mode_name(mode_1);
    char *mode_2_name = instruction_mode_name(mode_2);

    char *error_field = validate(code_name, mode_1_name, mode_2_name);

    if (error_field) {
        printf("Invalid %s in instruction: %d(%d/%d, %d/%d)\n", error_field, code, mode_1, val_1, mode_2, val_2);
    } else {
        printf("%s(%s%d, %s%d)\n", code_name, mode_1_name, val_1, mode_2_name, val_2);
    }
}

/*void instruction_execute(uint instr, Player *player) {
    Instruction instruction = instruction_parse(instr);
    int code = instruction.code;
    Arg *a = &instruction.a;
    Arg *b = &instruction.b;
    handlers[code](a, b, player);

    printf("Executed instruction: ");
    instruction_print(&instruction);
}*/
