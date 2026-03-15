#ifndef BLOCK_H
#define BLOCK_H
#include "grid.h"
#include <raylib.h>
#include "color.h"

typedef enum
{
    SHAPE_I,
    SHAPE_O,
    SHAPE_T,
    SHAPE_L,
    SHAPE_J,
    SHAPE_S,
    SHAPE_Z,
    SHAPE_COUNT
} shapeType;

typedef struct
{
    shapeType type;
    Vector2 pos;
    int rotation; // 0 1 2 3
    int tiles[4][4][2]; // rot tiles pos2
} Block;

Block createBlock(shapeType type);
void drawBlock(Block b, const Color *color);

#endif