#include "raylib.h"

int main() {
    const int screen_width = 800;
    const int screen_height = 600;

    InitWindow(screen_width, screen_height, "should work?");
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        const char *msg = "Hello raylib";
        const int fontSize = 20;
        DrawText(msg, ((800 - MeasureText(msg, fontSize)) / 2), 215, fontSize,
                 DARKGRAY);

        DrawCircle(400, 300, 50, BLUE);

        EndDrawing();
    }
    CloseWindow();

    return 0;
}
