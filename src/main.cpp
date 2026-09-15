#include <iostream>
#include <raylib.h>
#include "entities/player.h"

int main(int, char**){
    std::cout << "Hello, from Oceaner!\n";
    Player player;
    std::string playerName = player.getName();
    std::cout << "Player name: " << playerName << std::endl;
    InitWindow(800, 600, "Oceaner");
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText(playerName.c_str(), 190, 200, 20, LIGHTGRAY);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
