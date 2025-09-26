#include "raylib.h"
#include <iostream>

using namespace std;    

const int MAX_SNAKE_LENGTH = 10000;

class Food {
public:
    int x;
    int y;
    Color color;
    Food(int x, int y, Color color) : x(x), y(y), color(color) {}
    void draw() {
        DrawRectangle(x, y, 30, 30, color);
    }
};

class Snake {
public:
    Vector2 body[MAX_SNAKE_LENGTH];
    int length;
    int cellSize;
    Color color;
    Vector2 direction;
    Snake(int startX, int startY, int cellSize, Color color)
        : length(1), cellSize(cellSize), color(color) {
        body[0] = {(float)startX, (float)startY};
        direction = {1, 0};
    }
    void update() {
        // Move body
        for (int i = length - 1; i > 0; i--) {
            body[i] = body[i - 1];
        }
        // Move head
        body[0].x += direction.x * cellSize;
        body[0].y += direction.y * cellSize;
    }
    void grow() {
        if (length < MAX_SNAKE_LENGTH) {
            // Move body
            for (int i = length; i > 0; i--) {
                body[i] = body[i - 1];
            }
            // Move head
            body[0].x += direction.x * cellSize;
            body[0].y += direction.y * cellSize;
            length++;
        }
    }
    void draw() {
        for (int i = 0; i < length; i++) {
            DrawRectangle((int)body[i].x, (int)body[i].y, cellSize, cellSize, color);
        }
    }
    bool checkCollision(int x, int y) {
        for (int i = 0; i < length; i++) {
            if ((int)body[i].x == x && (int)body[i].y == y) return true;
        }
        return false;
    }
    bool checkSelfCollision() {
        for (int i = 1; i < length; i++) {
            if (body[0].x == body[i].x && body[0].y == body[i].y) return true;
        }
        return false;
    }
};


//const Color WHITE = {255,255,255,255};//
const Color darkGreen = {43, 51, 24,255};
const Color red = {224, 44, 44, 255};
// Use raylib's DARKGRAY or define it if not included
#ifndef DARKGRAY
#define DARKGRAY CLITERAL(Color){80, 78, 81, 255}
#endif

int main() {

    int cellSize = 30;
    int gridSize = 25; 
    InitWindow(cellSize * gridSize, cellSize * gridSize, "Retro Snake Game");
    SetTargetFPS(10);

    Snake snake(5 * cellSize, 5 * cellSize, cellSize, darkGreen);
    Food food((GetRandomValue(0, gridSize - 1)) * cellSize, (GetRandomValue(0, gridSize - 1)) * cellSize, red);

    bool gameOver = false;
    int score = 0;
    int highScore = 0;

    while (!WindowShouldClose()) {
        // Input
        if (IsKeyPressed(KEY_UP) && snake.direction.y != 1) { snake.direction = {0, -1}; }
        if (IsKeyPressed(KEY_DOWN) && snake.direction.y != -1) { snake.direction = {0, 1}; }
        if (IsKeyPressed(KEY_LEFT) && snake.direction.x != 1) { snake.direction = {-1, 0}; }
        if (IsKeyPressed(KEY_RIGHT) && snake.direction.x != -1) { snake.direction = {1, 0}; }

        if (!gameOver) {
            int nextHeadX = (int)(snake.body[0].x + snake.direction.x * cellSize);
            int nextHeadY = (int)(snake.body[0].y + snake.direction.y * cellSize);
            if (nextHeadX == food.x && nextHeadY == food.y) {
                snake.grow();
                score++;
                if (score > highScore) highScore = score;
                do {
                    food.x = GetRandomValue(0, gridSize - 1) * cellSize;
                    food.y = GetRandomValue(0, gridSize - 1) * cellSize;
                } while (snake.checkCollision(food.x, food.y));
            } else {
                snake.update();
            }

            if (snake.body[0].x < 0 || snake.body[0].x >= cellSize * gridSize ||
                snake.body[0].y < 0 || snake.body[0].y >= cellSize * gridSize) {
                gameOver = true;
            }

            if (snake.checkSelfCollision()) {
                gameOver = true;
            }
        }

        BeginDrawing();
        ClearBackground(WHITE);

        food.draw();
        snake.draw();

        // Display score and high score
        DrawText(TextFormat("Score: %d", score), 10, 10, 24, BLACK);
        DrawText(TextFormat("High Score: %d", highScore), 10, 40, 24, DARKGRAY);

        if (gameOver) {
            DrawText("GAME OVER!", 200, 350, 60, red);
            DrawText("Press SPACE to Restart", 200, 420, 30, BLACK);
            if (IsKeyPressed(KEY_SPACE)) {
                snake = Snake(5 * cellSize, 5 * cellSize, cellSize, darkGreen);
                food = Food((GetRandomValue(0, gridSize - 1)) * cellSize, (GetRandomValue(0, gridSize - 1)) * cellSize, red);
                score = 0;
                gameOver = false;
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}