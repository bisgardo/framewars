#include "player.h"

#include <stdlib.h>

Player *player_create(char *name) {
    Player *player = malloc(sizeof(Player));
    Proc *proc = proc_create();

    player->name = name;
    player->cur_proc = proc;

    return player;
}

void player_destroy(Player *player) {
    Proc *proc = player->cur_proc;
    proc->prev->next = 0;

    while (proc) {
        Proc *next = proc->next;
        proc_destroy(proc);
        proc = next;
    }

    free(player);
}

void player_add_proc(Player *player) {
    Proc *proc = proc_create();

    Proc *current = player->cur_proc;
    Proc *prev = current->prev;

    prev->next = proc;
    proc->prev = prev;

    current->prev = proc;
    proc->next = current;

    player->cur_proc = proc;
}

int player_move(Player *player) {
    Proc *proc = player->cur_proc;
    uint pc = proc->pc;
    int instr = arena_get(pc);


    // TODO ...

    return 0;
}
