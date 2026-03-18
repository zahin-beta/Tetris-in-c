#include "block.h"

static const int TILES[SHAPE_COUNT][4][4][2] = {
    // SHAPE_I
    {
        {{0, 0}, {0, 1}, {0, 2}, {0, 3}},
        {{0, 2}, {1, 2}, {2, 2}, {3, 2}},
        {{2, 0}, {2, 1}, {2, 2}, {2, 3}},
        {{0, 1}, {1, 1}, {2, 1}, {3, 1}},
    },
    // SHAPE_O
    {
        {{0, 0}, {0, 1}, {1, 0}, {1, 1}},
        {{0, 0}, {0, 1}, {1, 0}, {1, 1}},
        {{0, 0}, {0, 1}, {1, 0}, {1, 1}},
        {{0, 0}, {0, 1}, {1, 0}, {1, 1}},
    },
    // SHAPE_T
    {
        {{0, 1}, {1, 0}, {1, 1}, {1, 2}},
        {{0, 0}, {1, 0}, {1, 1}, {2, 0}},
        {{1, 0}, {1, 1}, {1, 2}, {2, 1}},
        {{0, 1}, {1, 0}, {1, 1}, {2, 1}},
    },
    // SHAPE_L
    {
        {{0, 2}, {1, 0}, {1, 1}, {1, 2}},
        {{0, 0}, {1, 0}, {2, 0}, {2, 1}},
        {{1, 0}, {1, 1}, {1, 2}, {2, 0}},
        {{0, 0}, {0, 1}, {1, 1}, {2, 1}},
    },
    // SHAPE_J
    {
        {{0, 0}, {1, 0}, {1, 1}, {1, 2}},
        {{0, 0}, {0, 1}, {1, 0}, {2, 0}},
        {{1, 0}, {1, 1}, {1, 2}, {2, 2}},
        {{0, 1}, {1, 1}, {2, 0}, {2, 1}},
    },
    // SHAPE_S
    {
        {{0, 1}, {0, 2}, {1, 0}, {1, 1}},
        {{0, 0}, {1, 0}, {1, 1}, {2, 1}},
        {{0, 1}, {0, 2}, {1, 0}, {1, 1}},
        {{0, 0}, {1, 0}, {1, 1}, {2, 1}},
    },
    // SHAPE_Z
    {
        {{0, 0}, {0, 1}, {1, 1}, {1, 2}},
        {{0, 1}, {1, 0}, {1, 1}, {2, 0}},
        {{0, 0}, {0, 1}, {1, 1}, {1, 2}},
        {{0, 1}, {1, 0}, {1, 1}, {2, 0}},
    },
};

Block createBlock(shapeType type)
{
    Block b;
    b.type = type;
    b.rotation = 0;
    b.pos = (Vector2){4, 0};
    for (int r = 0; r < 4; r++)
    {
        for (int t = 0; t < 4; t++)
        {
            b.tiles[r][t][0] = TILES[type][r][t][0];
            b.tiles[r][t][1] = TILES[type][r][t][1];
        }
    }
    return b;
}
void drawBlock(Block b, const Color *color)
{
    for (int t = 0; t < 4; t++)
    {
        int offset_row = b.tiles[b.rotation][t][0];
        int row = (int)b.pos.y + offset_row;
        int offset_clm = b.tiles[b.rotation][t][1];
        int col = (int)b.pos.x + offset_clm;

        DrawRectangle(
            col * CELL_S + 1,
            row * CELL_S + 1,
            CELL_S - 1,
            CELL_S - 1,
            color[b.type + 1]);
    }
}
bool checkCollision(Block b, Grid g)
{
    for (int t = 0; t < 4; t++)
    {
        int offset_row = b.tiles[b.rotation][t][0];
        int row = (int)b.pos.y + offset_row;
        int offset_clm = b.tiles[b.rotation][t][1];
        int col = (int)b.pos.x + offset_clm;

        if (row >= HEIGHT)
        {
            return 1;
        }
        if (col < 0 || col >= WIDTH)
        {
            return 1;
        }
        if (g.cell[row][col] != 0)
        {
            return 1;
        }
    }
    return 0;
}

void lockGrid(Block b, Grid *g)
{
    for (int t = 0; t < 4; t++)
    {
        int offset_row = b.tiles[b.rotation][t][0];
        int row = (int)b.pos.y + offset_row;
        int offset_clm = b.tiles[b.rotation][t][1];
        int col = (int)b.pos.x + offset_clm;
        g->cell[row][col] = b.type + 1;
    }
}