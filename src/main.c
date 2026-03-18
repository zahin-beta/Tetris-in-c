//"The journey of a thousand miles begins with a single step" - Lau Tse
// Tetris in c with raylib
// author : Zahin Bin Hasan
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
    SetTargetFPS(60);
    double fallT = 0, fallInt = .5;
    Grid g = createGrid();
    Block b = createBlock(SHAPE_T);
    printGrid(g);
    while (!WindowShouldClose())
    {
        double frameTime = GetFrameTime();
        fallT += frameTime;
        if (fallT >= fallInt)
        {
            b.pos.y++;
            if (checkCollision(b, g))
            {
                b.pos.y--;
                lockGrid(b, &g);
                b = createBlock(SHAPE_T);
            }

            fallT = 0;
        }

        if (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A))
        {
            b.pos.x--;
            if (checkCollision(b, g))
            {
                b.pos.x++;
            }
        }
        if (IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D))
        {
            b.pos.x++;
            if (checkCollision(b, g))
            {
                b.pos.x--;
            }
        }
        if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S))
        {
            b.pos.y++;
            if (checkCollision(b, g))
            {
                b.pos.y--;
            }
        }
        if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W))
        {
            b.rotation = (b.rotation + 1) % 4;
            if (checkCollision(b, g))
            {
                b.rotation = (b.rotation + 3) % 4;
            }
        }

        BeginDrawing();
        ClearBackground(darkBlue);
        drawGrid(g);
        drawBlock(b, getColor());
        EndDrawing();
    }
    CloseWindow();
}