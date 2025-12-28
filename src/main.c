#include "raylib.h"
#include <math.h>
const int screen_width = 800;
const int screen_height = 600;
const int FPS = 60;

void point(Vector2 p) {
    const float size = 0.0f;
    DrawRectangle(p.x - size / 2.0f, p.y - size / 2.0f, size, size, BLUE);
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

int edges[][2] = {
    {0, 1}, {1, 3}, {3, 2}, {2, 0}, // Back
    {4, 5}, {5, 7}, {7, 6}, {6, 4}, // Front
    {5, 1}, {3, 7},                 // Left
    {0, 4}, {2, 6}                  // Right
};

Vector3 translate_z(Vector3 p, float dz) {
    return (Vector3){p.x, p.y, p.z + dz};
}

Vector3 rotate_xz(Vector3 p, float a) {
    float c = cosf(a);
    float s = sinf(a);
    return (Vector3){p.x * c - p.z * s, p.y, p.x * s + p.z * c};
}

void render(float dz, float angle) {
    ClearBackground(BLACK);
    Vector2 projected[sizeof(points) / sizeof(points[0])];
    for (unsigned long i = 0; i < sizeof(points) / sizeof(points[0]); ++i) {
        projected[i] =
            screen(project(translate_z(rotate_xz(points[i], angle), dz)));
        point(projected[i]);
    }
    for (int i = 0; i < sizeof(edges) / sizeof(edges[0]); i++) {
        DrawLineV(projected[edges[i][0]], projected[edges[i][1]], BLUE);
    }
}

int main() {
    InitWindow(screen_width, screen_height, "should work?");
    SetTargetFPS(FPS);

    float angle = 0.0f;
    float baseZ = 2.5f;
    float amplitude = 1.0f;

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        float dz = baseZ + sinf(GetTime()) * amplitude;
        angle +=  dt;
        BeginDrawing();
        render(dz, angle);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
