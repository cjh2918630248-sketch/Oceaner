#include <iostream>
#include <raylib.h>

int main(int, char**){
    std::cout << "Hello, from Oceaner!\n";

    InitWindow(800, 600, "Oceaner");
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Hello, from Oceaner!", 190, 200, 20, LIGHTGRAY);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
