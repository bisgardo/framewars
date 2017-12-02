#ifndef PLAYER_H
#define PLAYER_H

#include "process.h"
#include "arena.h"

typedef struct Player Player;

struct Player {
    char *name;
    Process *current_process;
};

Player *player_create(char *name);

void player_add_process(Player *player);

void player_destroy(Player *player);

int player_move(Player *player);

#endif /* PLAYER_H */
