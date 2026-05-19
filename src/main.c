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
#include "tiles.h"
#include "game_update.h"

int loadHighScore()
{
    FILE *f = fopen("../assets/highscore.txt", "r");
    if (!f) return 0;
    int hs;
    fscanf(f, "%d", &hs);
    fclose(f);
    return hs;
}

void saveHighScore(int hs)
{
    FILE *f = fopen("../assets/highscore.txt", "w");
    if (!f) return;
    fprintf(f, "%d", hs);
    fclose(f);
}

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
    int level = 1;
    int highScore = loadHighScore();
    bool showStart = true;

    Music music = LoadMusicStream("../assets/music.mp3");
    Sound clear = LoadSound("../assets/clear.mp3");
    Sound rotate = LoadSound("../assets/rotate.mp3");
    Sound over = LoadSound("../assets/over.mp3");
    PlayMusicStream(music);
    bool sound = false;
    bool paused = false;

    while (!WindowShouldClose())
    {
        UpdateMusicStream(music);

        if (showStart)
        {
            if (IsKeyPressed(KEY_SPACE))
            {
                g = createGrid();
                b = createBlock(rand() % SHAPE_COUNT);
                next = createBlock(rand() % SHAPE_COUNT);
                score = 0;
                level = 1;
                fallInt = 0.5;
                game_over = false;
                paused = false;
                sound = false;
                ResumeMusicStream(music);
                showStart = false;
            }

            BeginDrawing();
            ClearBackground(darkBlue);
            DrawTextEx(font, "TETRIS", (Vector2){110, 120}, 80, 2, cyan);
            DrawTextEx(font, "Press SPACE to play", (Vector2){70, 210}, 38, 2, WHITE);
            int sy = 280;
            DrawTextEx(font, "CONTROLS", (Vector2){170, sy}, 32, 2, YELLOW); sy += 35;
            DrawTextEx(font, "LEFT/RIGHT", (Vector2){70, sy}, 24, 2, WHITE);
            DrawTextEx(font, "Move", (Vector2){240, sy}, 24, 2, WHITE); sy += 28;
            DrawTextEx(font, "UP", (Vector2){70, sy}, 24, 2, WHITE);
            DrawTextEx(font, "Rotate", (Vector2){240, sy}, 24, 2, WHITE); sy += 28;
            DrawTextEx(font, "DOWN", (Vector2){70, sy}, 24, 2, WHITE);
            DrawTextEx(font, "Soft Drop", (Vector2){240, sy}, 24, 2, WHITE); sy += 28;
            DrawTextEx(font, "TAB", (Vector2){70, sy}, 24, 2, WHITE);
            DrawTextEx(font, "Hard Drop", (Vector2){240, sy}, 24, 2, WHITE); sy += 28;
            DrawTextEx(font, "SPACE", (Vector2){70, sy}, 24, 2, WHITE);
            DrawTextEx(font, "Pause", (Vector2){240, sy}, 24, 2, WHITE); sy += 28;
            DrawTextEx(font, "R", (Vector2){70, sy}, 24, 2, WHITE);
            DrawTextEx(font, "Restart", (Vector2){240, sy}, 24, 2, WHITE);
            DrawTextEx(font, TextFormat("High Score: %d", highScore), (Vector2){120, 520}, 32, 2, LIME);
            EndDrawing();
        }
        else
        {
            if (IsKeyPressed(KEY_SPACE) && !game_over) paused = !paused;

            if (IsKeyPressed(KEY_R))
            {
                if (game_over)
                {
                    showStart = true;
                }
                else
                {
                    g = createGrid();
                    b = createBlock(rand() % SHAPE_COUNT);
                    next = createBlock(rand() % SHAPE_COUNT);
                    score = 0;
                    level = 1;
                    fallInt = 0.5;
                    game_over = false;
                    paused = false;
                    sound = false;
                    ResumeMusicStream(music);
                }
            }

            if (game_over)
            {
                if (!sound)
                {
                    PauseMusicStream(music);
                    PlaySound(over);
                    if (score > highScore)
                    {
                        highScore = score;
                        saveHighScore(highScore);
                    }
                    sound = true;
                }
                
                BeginDrawing();
                ClearBackground(darkBlue);
                DrawTextEx(font, "GAME OVER", (Vector2){60, 250}, 64, 2, RED);
                DrawTextEx(font, TextFormat("Score: %d", score), (Vector2){100, 320}, 38, 2, WHITE);
                DrawTextEx(font, TextFormat("High Score: %d", highScore), (Vector2){100, 365}, 32, 2, LIME);
                if (score > 0 && score >= highScore)
                {
                    DrawTextEx(font, "NEW RECORD!", (Vector2){120, 405}, 28, 2, YELLOW);
                }
                DrawTextEx(font, "Press R to menu", (Vector2){100, 450}, 38, 2, WHITE);
                EndDrawing(); 
            }
            else if (paused)
            {
                BeginDrawing();
                ClearBackground(darkBlue);
                DrawTextEx(font, "PAUSED", (Vector2){140, 270}, 64, 2, YELLOW);
                DrawTextEx(font, "Press SPACE to resume", (Vector2){60, 340}, 38, 2, WHITE);
                EndDrawing();
            }
            else
            {

                updateGameplay(&g, &b, &next, &score, &level, &fallInt, &fallT, &game_over, clear, rotate);

                BeginDrawing();
                ClearBackground(darkBlue);

                DrawRectangleRounded((Rectangle){320, 55, 170, 60}, .3, 6, lightBlue);
                DrawRectangleRounded((Rectangle){320, 265, 170, 180}, .3, 6, lightBlue);

                DrawTextEx(font, "SCORE", (Vector2){365, 15}, 38, 2, WHITE);
                DrawTextEx(font, "Next", (Vector2){365, 225}, 38, 2, WHITE);

                char scoreText[10];
                sprintf(scoreText, "%d", score);
                Vector2 textSize = MeasureTextEx(font, scoreText, 38, 2);
                Vector2 textPos = {320 + (170 - textSize.x) / 2, 65};
                DrawTextEx(font, scoreText, textPos, 38, 2, WHITE);

                DrawRectangleRounded((Rectangle){320, 160, 170, 60}, .3, 6, lightBlue);
                DrawTextEx(font, "LEVEL", (Vector2){365, 120}, 38, 2, WHITE);
                char levelText[10];
                sprintf(levelText, "%d", level);
                Vector2 levelSize = MeasureTextEx(font, levelText, 38, 2);
                Vector2 levelPos = {320 + (170 - levelSize.x) / 2, 170};
                DrawTextEx(font, levelText, levelPos, 38, 2, WHITE);

                drawGrid(g);
                drawGhost(b, g, getColor(), 11, 11);
                Block previewBlock = next;
                previewBlock.pos = (Vector2){0, 0};
                drawBlock(b, getColor(), 11, 11);
                int px = 360, py = 325;
                if (next.type == SHAPE_I)
                {
                    px = 345;
                    py = 340;
                }
                if (next.type == SHAPE_O)
                {
                    px = 345;
                    py = 325;
                }

                drawBlock(previewBlock, getColor(), px, py);
                EndDrawing();
            }
        }
    }
    CloseWindow();
    UnloadMusicStream(music);
    UnloadSound(clear);
    UnloadSound(rotate);
    CloseAudioDevice();
}