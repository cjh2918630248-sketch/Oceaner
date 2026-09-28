#ifndef BATTLE_SCENE_H
#define BATTLE_SCENE_H

#include "scenes/Scene.h"
#include "entities/player.h"
#include "entities/enemy.h"
#include "entities/weapon.h"
#include "systems/BattleSystem.h"

class BattleScene : public Scene {
public:
    BattleScene();
    ~BattleScene();

    void Update() override;
    void Draw() override;

private:
    Player m_player;
    Enemy m_enemy;
    Weapon m_weapon;
    BattleSystem m_battle;
};

#endif