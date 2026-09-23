#include <iostream>
#include <cstdlib>
#include <raylib.h>
#include "entities/player.h"
#include "entities/enemy.h"
#include "entities/weapon.h"

int main(int, char**){
    system("chcp 65001 > nul");
    std::cout << "Hello, from Oceaner!\n";
    Player player;
    Weapon weapon01(static_cast < short >(WeaponType::WEAPON01));
    Enemy enemy(static_cast < short >(EnemyType::ENEMY01));
    std::string playerName = player.getName();
    std::cout << "Player name: " << playerName << std::endl;
    std::cout << "Player hp: " << player.getHp() << std::endl;
    std::cout << "Player physical attack: " << player.getPhysicalAttack() << std::endl;
    std::cout << "Player defense: " << player.getDefense() << std::endl;
    std::cout << "Enemy name: " << enemy.getName() << std::endl;
    std::cout << "Enemy hp: " << enemy.getHp() << std::endl;
    std::cout << "Enemy physical attack: " << enemy.getPhysicalAttack() << std::endl;
    std::cout << "Enemy defense: " << enemy.getDefense() << std::endl;
    std::cout << "Enemy sea power: " << enemy.getSeaPower() << std::endl;
    std::cout << "Weapon name: " << weapon01.getName() << std::endl;
    std::cout << "Weapon physical attack: " << weapon01.getPhysicalAttack() << std::endl;
    std::cout << "Weapon sea power: " << weapon01.getSeaPower() << std::endl;
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
