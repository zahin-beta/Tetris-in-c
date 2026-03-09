// snake game remake in c
//@author: Zahin Bin Hasan
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define CELL_SIZE 30
#define CELL_COUNT 25

Color green = {173, 204, 96, 255};
Color darkGreen = {43, 51, 24, 255};
// food struct
typedef struct Food
{
    Vector2 pos;
    Texture2D texture;
} Food;

void foodDraw(Food *food)
{
    DrawTexture(food->texture, food->pos.x * CELL_SIZE, food->pos.y * CELL_SIZE, WHITE);
}

Vector2 randomPos()
{
    int x = GetRandomValue(0, CELL_COUNT - 1);
    int y = GetRandomValue(0, CELL_COUNT - 1);
    return (Vector2){x, y};
}

Food createFood()
{
    Food f =
        {
            .pos = randomPos(),
            .texture = LoadTexture("../assets/food.png")};
    return f;
}
// ending food struct

// snake struct

typedef struct Snake
{
    Vector2 body[100];
    int length;
    Vector2 direction;
} Snake;
void initialSnake(Snake *s)
{
    s->length = 3;
    s->body[0] = (Vector2){CELL_COUNT / 2, CELL_COUNT / 2};
    s->body[1] = (Vector2){CELL_COUNT / 2 - 1, CELL_COUNT / 2};
    s->body[2] = (Vector2){CELL_COUNT / 2 - 2, CELL_COUNT / 2};
}

void drawSnake(Snake *s)
{
    for (size_t i = 0; i < s->length; i++)
    {
        DrawRectangle(s->body[i].x * CELL_SIZE, s->body[i].y * CELL_SIZE, CELL_SIZE, CELL_SIZE, darkGreen);
    }
}
void input(Snake *s)
{
    if (IsKeyPressed(KEY_W))
    {
        s->direction = (Vector2){0, -1};
    }
    if (IsKeyPressed(KEY_S))
    {
        s->direction = (Vector2){0, 1};
    }
    if (IsKeyPressed(KEY_A))
    {
        s->direction = (Vector2){-1, 0} ;
    }
    if (IsKeyPressed(KEY_D))
    {
        s->direction = (Vector2){1, 0};
    }
}

void snakeMovement(Snake *s)
{
    for (size_t i = s->length - 1; i > 0; i--)
    {
        s->body[i] = s->body[i - 1];
    }
    s->body[0].x += s->direction.x;
    s->body[0].y += s->direction.y;
}

// ending snake struct

int main()
{
    InitWindow(CELL_SIZE * CELL_COUNT, CELL_SIZE * CELL_COUNT, "SNAKE GAME");
    SetTargetFPS(60);
    int framecount = 0;
    Food food = createFood();
    Snake snake;
    initialSnake(&snake);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        framecount++;
        input(&snake);
        if (framecount == 10)
        {
            snakeMovement(&snake);
            framecount = 0;
        }
        ClearBackground(green);
        foodDraw(&food);
        drawSnake(&snake);
        EndDrawing();
    }
    UnloadTexture(food.texture);
    CloseWindow();
}