#ifndef BATTLE_SYSTEM_H
#define BATTLE_SYSTEM_H

#include "entities/player.h"
#include "entities/enemy.h"
#include "entities/weapon.h"

enum class BattleState {
    PLAYER_TURN = 0,
    ENEMY_TURN,
    PLAYER_WIN,
    PLAYER_LOSE
};

class BattleSystem {
public:
    BattleSystem(Player* player, Enemy* enemy, Weapon* weapon);

    void Update();
    void PlayerAttack();
    bool IsOver() const;
    BattleState GetState() const;

private:
    void EnemyAttack();

    Player* m_player;
    Enemy* m_enemy;
    Weapon* m_weapon;
    BattleState m_state;
};

#endif