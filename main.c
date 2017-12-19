#define _CRT_SECURE_NO_WARNINGS

#include "player.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

extern FILE *yyin;
extern int yyparse(Proc *proc);

extern int yylineno;
extern char *yytext;

int err_count;

int yywrap() {
    return 1;
}

void yyerror(char *s, ...) {
    err_count++;
    va_list ap;
    va_start(ap, s);
    fprintf(stderr, "error on line %d: ", yylineno);
    vfprintf(stderr, s, ap);
    fprintf(stderr, "\n");
}

int redcode_parse(Proc *proc, FILE *file) {
    yyin = file;
    yylineno = 1;
    err_count = 0;
    return !yyparse(proc) && !err_count;
}

int main(int argc, char *argv[]) {
    int rounds_count = 5;

    char *dummy = "redcode/dummy.red";
    char *dwarf = "redcode/dwarf.red";

    Player *player1 = player_create("A");
    Player *player2 = player_create("B");

    Player *players[] = { player1, player2 };
    Player *loser = NULL;

    int max_rounds = 2*rounds_count;
    int round;

    FILE *dummyFile = fopen(dummy, "r");
    if (!dummyFile) {
        fprintf(stderr, "Error reading initial proc of player 1: File %s not found\n", dummy);
        return 1;
    }

    FILE *dwarfFile = fopen(dwarf, "r");
    if (!dwarfFile) {
        fprintf(stderr, "Error reading initial proc of player 2: File %s not found\n", dwarf);
        return 1;
    }

    if (!redcode_parse(player1->cur_proc, dummyFile)) {
        fprintf(stderr, "Error parsing initial procedure of player 1");
        return 2;
    }
    if (!redcode_parse(player2->cur_proc, dwarfFile)) {
        fprintf(stderr, "Error parsing initial procedure of player 2");
        return 2;
    }

    {
        printf("Player 1:\n");
        proc_print(player1->cur_proc);
        printf("Player 2:\n");
        proc_print(player2->cur_proc);
    }

    /* TODO Initialize arena (could set size at the same time...) */

    for (round = 0; round < max_rounds; round++) {
        Player *current = players[round % 2];

        int failed = player_move(current);
        if (failed) {
            loser = current;
            break;
        }
    }

    if (loser) {
        /* TODO Inspect 'arena' to see what happened. */
        printf("And the loser is '%s' (round %d)!\n", loser->name, round);
    } else {
        printf("Draw after %d rounds!\n", max_rounds);
    }

    player_destroy(player1);
    player_destroy(player2);

    return EXIT_SUCCESS;
}
