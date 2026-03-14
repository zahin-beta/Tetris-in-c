#ifndef GRID_H
#define GRID_H
#define HEIGHT 20
#define WIDTH 10
#define CELL_S 30

typedef struct Grid
{
    int cell[HEIGHT][WIDTH];
} Grid;

Grid createGrid();
void printGrid(Grid g);
void drawGrid(Grid g);

#endif
