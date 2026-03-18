//"The journey of a thousand miles begins with a single step" - Lau Tse
// Tetris in c with raylib
// author : Zahin Bin Hasan
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "grid.h"
#include "color.h"
#include "block.h"
int main()
{
    int ww = 500, wh = 620;
    InitWindow(ww, wh, "TETRIS");
    InitAudioDevice();
    SetTargetFPS(60);

    double fallT = 0, fallInt = .5;

    srand(time(NULL));

    Font font = LoadFontEx("../assets/monogram.ttf", 64, 0, 0);

    Grid g = createGrid();
    Block b = createBlock(rand() % SHAPE_COUNT);
    Block next = createBlock(rand() % SHAPE_COUNT);
    bool game_over = false;
    int score = 0;

    Music music = LoadMusicStream("../assets/music.mp3");
    Sound clear = LoadSound("../assets/clear.mp3");
    Sound rotate = LoadSound("../assets/rotate.mp3");
    Sound over = LoadSound("../assets/over.mp3");
    PlayMusicStream(music);
    bool sound = false;
    //  printGrid(g);

    while (!WindowShouldClose())
    {
        UpdateMusicStream(music);
        if (game_over)
        {
            if (!sound)
            {
                PauseMusicStream(music);
                PlaySound(over);
                sound = true;
            }
            
            BeginDrawing();
            ClearBackground(darkBlue);
            DrawTextEx(font, "GAME OVER", (Vector2){60, 270}, 64, 2, RED);
            DrawTextEx(font, "Press R to restart", (Vector2){60, 340}, 38, 2, WHITE);
            if (IsKeyPressed(KEY_R))
            {
                g = createGrid();
                b = createBlock(rand() % SHAPE_COUNT);
                next = createBlock(rand() % SHAPE_COUNT);
                score = 0;
                game_over = false;
                sound = false;
                ResumeMusicStream(music);
            }
            EndDrawing(); 
        }
        else
        {

            double frameTime = GetFrameTime();
            fallT += frameTime;

            if (fallT >= fallInt)
            {
                b.pos.y++;
                if (checkCollision(b, g))
                {
                    b.pos.y--;
                    lockBlocks(b, &g);
                    b = next;
                    next = createBlock(rand() % SHAPE_COUNT);
                    int lines = clearLines(&g);
                    if (lines > 0)
                    {
                        PlaySound(clear);
                    }

                    switch (lines)
                    {
                    case 1:
                        score += 100;
                        break;
                    case 2:
                        score += 200;
                        break;
                    case 3:
                        score += 300;
                        break;
                    case 4:
                        score += 400;
                        break;

                    default:
                        score += 0;
                        break;
                    }
                    // b = createBlock(rand() % SHAPE_COUNT);
                    if (checkCollision(b, g))
                    {
                        game_over = true;
                    }
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
                PlaySound(rotate);
                b.rotation = (b.rotation + 1) % 4;

                if (checkCollision(b, g))
                {
                    int kicks = (b.type == SHAPE_I) ? 3 : 1;
                    b.pos.x -= kicks;
                    if (checkCollision(b, g))
                    {
                        b.pos.x += kicks * 2;
                        if (checkCollision(b, g))
                        {
                            b.pos.x -= kicks;
                            b.rotation = (b.rotation + 3) % 4;
                        }
                    }
                }
            }

            BeginDrawing();
            ClearBackground(darkBlue);

            DrawRectangleRounded((Rectangle){320, 55, 170, 60}, .3, 6, lightBlue);
            DrawRectangleRounded((Rectangle){320, 215, 170, 180}, .3, 6, lightBlue);

            DrawTextEx(font, "SCORE", (Vector2){365, 15}, 38, 2, WHITE);
            DrawTextEx(font, "Next", (Vector2){370, 175}, 38, 2, WHITE);

            char scoreText[10];
            sprintf(scoreText, "%d", score);
            Vector2 textSize = MeasureTextEx(font, scoreText, 38, 2);
            Vector2 textPos = {320 + (170 - textSize.x) / 2, 65};
            DrawTextEx(font, scoreText, textPos, 38, 2, WHITE);

            drawGrid(g);
            Block previewBlock = next;
            previewBlock.pos = (Vector2){0, 0};
            drawBlock(b, getColor(), 11, 11);
            int px = 360, py = 270;
            if (next.type == SHAPE_I)
            {
                px = 345;
                py = 260;
            }
            if (next.type == SHAPE_O)
            {
                px = 345;
                py = 240;
            }

            drawBlock(previewBlock, getColor(), px, py);
            EndDrawing();
        }
    }
    CloseWindow();
    UnloadMusicStream(music);
    UnloadSound(clear);
    UnloadSound(rotate);
    CloseAudioDevice();
}