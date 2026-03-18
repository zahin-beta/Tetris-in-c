#include "block.h"
#include "tiles.h"
Block createBlock(shapeType type)
{
    Block b;
    b.type = type;
    b.rotation = 0;
    if (type == SHAPE_I)
        b.pos = (Vector2){3, -1}; // Move(-1, 3)
    else if (type == SHAPE_O)
        b.pos = (Vector2){4, 0}; // Move(0, 4)
    else
        b.pos = (Vector2){3, 0}; // Move(0, 3)
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
            col * CELL_S + 11,
            row * CELL_S + 11,
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

void lockBlocks(Block b, Grid *g)
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