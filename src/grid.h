#ifndef GRID_H
#define GRID_H
#include "common.h"
//#include "block.h"
typedef struct Grid
{
    int cell[HEIGHT][WIDTH];
} Grid;

Grid createGrid();
void printGrid(Grid g);
void drawGrid(Grid g);
int clearLines(Grid *g);
#endif
