#include "scenes/BattleScene.h"
#include <raylib.h>

BattleScene::BattleScene()
    : m_enemy(static_cast<short>(EnemyType::ENEMY01)),
      m_weapon(static_cast<short>(WeaponType::WEAPON01)),
      m_battle(&m_player, &m_enemy, &m_weapon) {
}

BattleScene::~BattleScene() {
}

void BattleScene::Update() {
    if (IsKeyPressed(KEY_SPACE)) {
        m_battle.PlayerAttack();
    }
    m_battle.Update();
}

void BattleScene::Draw() {
    DrawText(TextFormat("Player HP: %d", m_player.getHp()), 20, 20, 24, DARKGRAY);
    DrawText(TextFormat("Enemy HP: %d", m_enemy.getHp()), 20, 60, 24, DARKGRAY);
    DrawText("Press SPACE to attack", 20, 500, 20, LIGHTGRAY);

    if (m_battle.GetState() == BattleState::PLAYER_WIN) {
        DrawText("You Win!", 320, 250, 40, GREEN);
    } else if (m_battle.GetState() == BattleState::PLAYER_LOSE) {
        DrawText("You Lose!", 320, 250, 40, RED);
    }
}