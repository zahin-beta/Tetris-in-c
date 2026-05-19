#pragma once
#include "grid.h"
#include "block.h"
#include <raylib.h>

void updateGameplay(Grid *g, Block *b, Block *next, 
    int *score, int *level, double *fallInt, double *fallT, 
    bool *game_over, Sound clear, Sound rotate);
