#include "grid.h"
#include "color.h"
#include <stdio.h>
#include <raylib.h>
Grid g;
Grid createGrid()
{
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            g.cell[i][j] = 0;
        }
    }
    return g;
}
void printGrid(Grid g)
{
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            printf("%d ", g.cell[i][j]);
        }
        printf("\n");
    }
}

void drawGrid(Grid g)
{
    const Color *color = getColor();
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            int cellV = g.cell[i][j];
            DrawRectangle(j * CELL_S + 1, i * CELL_S + 1, CELL_S - 1, CELL_S - 1, color[cellV]);
        }
    }
}
