//"The journey of a thousand miles begins with a single step" - Lau Tse
//Tetris in c with raylib
//author : Zahin Bin Hasan 
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include "grid.h"
#include "color.h"
#include "block.h"
int main()
{
    int ww = 300, wh = 600;
    InitWindow(ww, wh, "TETRIS");
    SetTargetFPS(120);
    Grid g = createGrid();
    Block b = createBlock(SHAPE_T);
    printGrid(g);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(darkBlue);
        drawGrid(g);
        drawBlock(b,getColor());
        if (IsKeyPressed(KEY_LEFT))
            b.pos.x--;
        if (IsKeyPressed(KEY_RIGHT))
            b.pos.x++;
        if (IsKeyPressed(KEY_DOWN))
            b.pos.y++;
        if (IsKeyPressed(KEY_UP))
            b.rotation = (b.rotation + 1) % 4;
        EndDrawing();
    }
    CloseWindow();
}