#ifndef PLAYER_H
#define PLAYER_H

#include "arena.h"
#include "process.h"

typedef struct Player Player;

struct Player {
    char *name;
    Proc *cur_proc;
};

Player *player_create(char *name);

void player_add_proc(Player *player);

void player_destroy(Player *player);

int player_move(Player *player);

#endif /* PLAYER_H */
