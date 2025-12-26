#include "raylib.h"
const int screen_width = 800;
const int screen_height = 600;
const int FPS = 60;

void point(Vector2 p) {
    const float size = 20.0f;
    const float s = 20.0f;
    DrawRectangle(p.x - s / 2.0f, p.y - s / 2.0f, s, s, BLUE);
}

Vector2 screen(Vector2 p) {
    return (Vector2){
        (p.x + 1.0f) / 2 * screen_width,
        (1.0f - (p.y + 1.0f) / 2) * screen_height,
    };
}

Vector2 project(Vector3 p) {
    return (Vector2){
        p.x / p.z,
        p.y / p.z,
    };
}

Vector3 points[] = {
    // clang-format off
    {.x =  0.5f, .y =  0.5f, .z = 0.5f},
    {.x = -0.5f, .y =  0.5f, .z = 0.5f},
    {.x =  0.5f, .y = -0.5f, .z = 0.5f},
    {.x = -0.5f, .y = -0.5f, .z = 0.5f},


    {.x =  0.5f, .y =  0.5f, .z = -0.5f},
    {.x = -0.5f, .y =  0.5f, .z = -0.5f},
    {.x =  0.5f, .y = -0.5f, .z = -0.5f},
    {.x = -0.5f, .y = -0.5f, .z = -0.5f},
    // clang-format on
};

Vector3 translate_z(Vector3 p, float dz) {
    return (Vector3){p.x, p.y, p.z + dz};
}

void render(float dz) {
    ClearBackground(BLACK);
    for (unsigned long i = 0; i < sizeof(points) / sizeof(points[0]); ++i) {
        point(screen(project(translate_z(points[i], dz))));
    }
}

int main() {
    InitWindow(screen_width, screen_height, "should work?");
    SetTargetFPS(FPS);

    float dz = 0.5f;

    while (!WindowShouldClose()) {
        float dt = 1.0f / FPS;
        dz += 1.0f * dt;
        BeginDrawing();
        render(dz);
        EndDrawing();
    }
    CloseWindow();

    return 0;
}
