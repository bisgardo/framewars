#include "instruction.h"
#include "player.h"

#include <stdio.h>
#include <stdlib.h>

#define PICK_BITS(value, from, to) (((value) >> (from)) & ~(~0 << ((to)-(from)+1)))

Arg arg_create(Mode mode, int val) {
    Arg arg = { mode, val };
    return arg;
}

Instr *instr_create(int code, Arg a, Arg b) {
    Instr *instr = malloc(sizeof(Instr));

    instr->prev = 0;
    instr->next = 0;
    instr->code = code;
    instr->a = a;
    instr->b = b;

    return instr;
}

void instr_destroy(Instr *instr) {
    free(instr);
}

/* Instruction parser functions. */

int parse_val_2(uint instr) {
    return PICK_BITS(instr, 0, 11);
}

int parse_val_1(uint instr) {
    return PICK_BITS(instr, 12, 23);
}

Mode parse_mode_2(uint instr) {
    return (Mode) PICK_BITS(instr, 24, 25);
}

Mode parse_mode_1(uint instr) {
    return (Mode) PICK_BITS(instr, 26, 27);
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

Instr instr_parse(uint encoded) {
    Instr instr;
    instr.prev = 0;
    instr.next = 0;

    instr.code = parse_code(encoded);
    instr.a = parse_arg_1(encoded);
    instr.b = parse_arg_2(encoded);
    return instr;
}

Instr *instr_pred(Instr *instr, int index) {
    if (index < 0) {
        return instr_succ(instr, -index);
    }
    while (index-- > 0 && instr) {
        instr = instr->prev;
    }
    return instr;
}

Instr *instr_succ(Instr *instr, int index) {
    if (index < 0) {
        return instr_pred(instr, -index);
    }
    while (index-- > 0 && instr) {
        instr = instr->next;
    }
    return instr;
}

Instr *instr_first(Instr *instr) {
    while (instr->prev) {
        instr = instr->prev;
    }
    return instr;
}

Instr *instr_last(Instr *instr) {
    while (instr->next) {
        instr = instr->next;
    }
    return instr;
}

void instr_sequence(Instr *prev, Instr *next) {
    prev->next = next;
    next->prev = prev;
}

int instr_encode(Instr *instr) {
    Arg *a = &instr->a;
    Arg *b = &instr->b;

    int code = instr->code;
    int mode1 = a->mode;
    int mode2 = b->mode;
    int val1 = a->val;
    int val2 = b->val;

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

char *instr_code_name(int code) {
    char *code_names[] = {
        "dat", "mov", "add", "sub", "jmp", "jmz", "djz", "cmp"
    };

    if (0 <= code && code < 8) {
        return code_names[code];
    } else {
        return 0;
    }
}

char *instr_mode_name(int mode) {
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
    }
    if (!mode_1_name) {
        return "mode 1";
    }
    if (!mode_2_name) {
        return "mode 2";
    }
    return 0;
}

void instr_print(Instr *instr) {
    int code = instr->code;
    Arg *a = &instr->a;
    Arg *b = &instr->b;

    int mode_1 = a->mode;
    int mode_2 = b->mode;

    int val_1 = a->val;
    int val_2 = b->val;

    char *code_name = instr_code_name(code);
    char *mode_1_name = instr_mode_name(mode_1);
    char *mode_2_name = instr_mode_name(mode_2);

    char *error_field = validate(code_name, mode_1_name, mode_2_name);

    if (error_field) {
        printf("Invalid %s in instruction: %d(%d/%d, %d/%d)\n", error_field, code, mode_1, val_1, mode_2, val_2);
    } else {
        printf("%s(%s%d, %s%d)\n", code_name, mode_1_name, val_1, mode_2_name, val_2);
    }
}

/*void instr_execute(uint instr, Player *player) {
    instr instr = instr_parse(instr);
    int code = instr.code;
    arg *a = &instr.a;
    arg *b = &instr.b;
    handlers[code](a, b, player);

    printf("Executed instr: ");
    instr_print(&instr);
}*/
