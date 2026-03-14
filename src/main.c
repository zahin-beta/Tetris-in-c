//"The journey of a thousand miles begins with a single step" - Lau Tse
//Tetris in c with raylib
//author : Zahin Bin Hasan 
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include "grid.h"
#include "color.h"
int main()
{
    int ww = 300, wh = 600;
    InitWindow(ww, wh, "TETRIS");
    SetTargetFPS(120);
    Grid g = createGrid();
    printGrid(g);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(darkBlue);
        drawGrid(g);
        EndDrawing();
    }
    CloseWindow();
}