#include "arena.h"

#include <stdlib.h>

#define SIZE 4096

/* Zero-initialized cell array */
static uint arena[SIZE];

/*
Arena *arena_create(int size) {
    Arena *arena = malloc(sizeof(Arena));
    arena->cells = calloc(size, sizeof(uint));
    return arena;
}

void arena_destroy(Arena *arena) {
    free(arena->cells);
    free(arena);
}
*/

int arena_get(uint index) {
    if (index < SIZE) {
        return arena[index];
    } else {
        return -1;
    }
}

void arena_set(uint index, uint instr) {
    if (index < SIZE) {
        arena[index] = instr;
    }
}
