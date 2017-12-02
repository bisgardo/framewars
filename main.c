#define _CRT_SECURE_NO_WARNINGS

#include "arena.h"
#include "player.h"
#include "process.h"

#include <stdio.h>
#include <stdlib.h>

extern FILE *yyin;
extern int yyparse(Process *process);

void yyerror(Process *process, char *msg) {
    fprintf(stderr, "Parse error...");
}

int yywrap() {
    return 1;
}

int redcode_parse(Process *process, char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        return 0;
    }

    yyin = file;
    yyparse(process);
    return 1;
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

    if (!redcode_parse(player1->current_process, dummy)) {
        printf("Error parsing initial process of player 1: File %s not found\n", dummy);
        return 1;
    }
    if (!redcode_parse(player2->current_process, dwarf)) {
        printf("Error parsing initial process of player 2: File %s not found\n", dwarf);
        return 2;
    }

    {
        printf("Player 1:\n");
        process_print(player1->current_process);
        printf("Player 2:\n");
        process_print(player2->current_process);
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
