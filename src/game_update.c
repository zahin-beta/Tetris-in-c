#include "game_update.h"
#include "tiles.h"
#include <stdlib.h>
#include <time.h>

void updateGameplay(Grid *g, Block *b, Block *next,
    int *score, int *level, double *fallInt, double *fallT,
    bool *game_over, Sound clear, Sound rotate)
{
    double frameTime = GetFrameTime();
    *fallT += frameTime;

    if (*fallT >= *fallInt)
    {
        b->pos.y++;
        if (checkCollision(*b, *g))
        {
            b->pos.y--;
            lockBlocks(*b, g);
            *b = *next;
            *next = createBlock(rand() % SHAPE_COUNT);
            int lines = clearLines(g);
            if (lines > 0) PlaySound(clear);
            switch (lines)
            {
            case 1: *score += 100; break;
            case 2: *score += 200; break;
            case 3: *score += 300; break;
            case 4: *score += 400; break;
            }
            *level = *score / 1000 + 1;
            *fallInt = 0.5 - (*level - 1) * 0.04;
            if (*fallInt < 0.08) *fallInt = 0.08;
            if (checkCollision(*b, *g)) *game_over = true;
        }
        *fallT = 0;
    }

    if (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A))
    {
        b->pos.x--;
        if (checkCollision(*b, *g)) b->pos.x++;
    }
    if (IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D))
    {
        b->pos.x++;
        if (checkCollision(*b, *g)) b->pos.x--;
    }
    if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S))
    {
        b->pos.y++;
        if (checkCollision(*b, *g)) b->pos.y--;
    }
    if (IsKeyPressed(KEY_TAB))
    {
        int dropDist = 0;
        while (!checkCollision(*b, *g))
        {
            b->pos.y++;
            dropDist++;
        }
        b->pos.y--;
        dropDist--;
        *score += dropDist * 2;
        lockBlocks(*b, g);
        *b = *next;
        *next = createBlock(rand() % SHAPE_COUNT);
        int lines = clearLines(g);
        if (lines > 0) PlaySound(clear);
        switch (lines)
        {
        case 1: *score += 100; break;
        case 2: *score += 200; break;
        case 3: *score += 300; break;
        case 4: *score += 400; break;
        }
        *level = *score / 1000 + 1;
        *fallInt = 0.5 - (*level - 1) * 0.04;
        if (*fallInt < 0.08) *fallInt = 0.08;
        if (checkCollision(*b, *g)) *game_over = true;
        *fallT = 0;
    }
    if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W))
    {
        int prevRot = b->rotation;
        b->rotation = (b->rotation + 1) % 4;
        if (!checkCollision(*b, *g))
        {
            PlaySound(rotate);
        }
        else
        {
            const int (*kicks)[2] = (b->type == SHAPE_I) ? KICK_I[prevRot] : KICK_JLSTZ[prevRot];
            bool kicked = false;
            for (int i = 0; i < 5; i++)
            {
                b->pos.x += kicks[i][0];
                b->pos.y += kicks[i][1];
                if (!checkCollision(*b, *g))
                {
                    kicked = true;
                    break;
                }
                b->pos.x -= kicks[i][0];
                b->pos.y -= kicks[i][1];
            }
            if (kicked) PlaySound(rotate);
            else b->rotation = prevRot;
        }
    }
}
