#include "color.h"

const Color darkGrey = {26, 31, 40, 255};
const Color green = {47, 230, 23, 255};
const Color red = {232, 18, 18, 255};
const Color orange = {226, 116, 17, 255};
const Color yellow = {237, 234, 4, 255};
const Color purple = {166, 0, 247, 255};
const Color cyan = {21, 204, 209, 255};
const Color blue = {13, 64, 216, 255};
const Color lightBlue = {0, 191, 255, 255};
const Color darkBlue = {0, 0, 139, 255};

static const Color cellColors[] = {
    darkGrey, green, red, orange, yellow,
    purple, cyan, blue, lightBlue, darkBlue};

const Color *getColor()
{
    return cellColors;
}
