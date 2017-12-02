#include "player.h"

#include "stdlib.h"

Player *player_create(char *name) {
    Player *player = malloc(sizeof(Player));
    Process *process = process_create();

    player->name = name;
    player->current_process = process;

    return player;
}

void player_destroy(Player *player) {
    Process *process = player->current_process;
    process->prev->next = 0;

    while (process) {
        Process *next = process->next;
        process_destroy(process);
        process = next;
    }

    free(player);
}

void player_add_process(Player *player) {
    Process *process = process_create();

    Process *current = player->current_process;
    Process *prev = current->prev;

    prev->next = process;
    process->prev = prev;

    current->prev = process;
    process->next = current;

    player->current_process = process;
}

int player_move(Player *player) {
    Process *process = player->current_process;
    uint pc = process->pc;
    int instr = arena_get(pc);


    // TODO ...

    return 0;
}
