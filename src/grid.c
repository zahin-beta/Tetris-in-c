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
            DrawRectangle(j * CELL_S + 11, i * CELL_S + 11, CELL_S - 1, CELL_S - 1, color[cellV]);
        }
    }
}


int clearLines (Grid * g)
{
    int lineCleared = 0;
    for (int row = HEIGHT - 1; row >= 0; row--)
    {
        int linefull = 1;

        for (int col = 0; col < WIDTH; col++)
        {
            if (g->cell[row][col] == 0)
            {
                linefull = 0;
                break;
            }
            
        }

        if (linefull)
        {
            for ( int r = row; r > 0; r--)
            {
                for (size_t col = 0; col < WIDTH; col++)
                {
                    g->cell[r][col] = g->cell[r - 1][col];
                }
            }

            for (size_t i = 0; i < WIDTH; i++)
            {
                g->cell[0][i] = 0;
            }
            lineCleared++;
            row++;
        }    
    }
    return lineCleared;
}