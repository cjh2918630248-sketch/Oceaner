#include "systems/BattleSystem.h"
#include "systems/DamageCalculator.h"
#include <stdio.h>

BattleSystem::BattleSystem(Player* player, Enemy* enemy, Weapon* weapon)
    : m_player(player), m_enemy(enemy), m_weapon(weapon),
      m_state(BattleState::PLAYER_TURN) {
}

void BattleSystem::Update() {
    if (IsOver()) {
        return;
    }
    if (m_state == BattleState::ENEMY_TURN) {
        EnemyAttack();
        if (!IsOver()) {
            m_state = BattleState::PLAYER_TURN;
        }
    }
}

void BattleSystem::PlayerAttack() {
    if (m_state != BattleState::PLAYER_TURN || IsOver()) {
        return;
    }

    double scaled = m_player->getPhysicalAttack() / 100.0;
    int totalAttack = scaled * m_weapon->getPhysicalAttack();
    int seaPower = m_weapon->getSeaPower();

    int physDamage = DamageCalculator::CalculatePhysicalDamage(totalAttack, m_enemy->getDefense());
    int seaDamage = DamageCalculator::CalculateSeaDamage(seaPower);
    int totalDamage = physDamage + seaDamage;

    m_enemy->setHp(m_enemy->getHp() - totalDamage);
    printf("%s 对 %s 造成 %d 点伤害（物理 %d + 海蚀 %d）\n",
           m_player->getName().c_str(), m_enemy->getName().c_str(),
           totalDamage, physDamage, seaDamage);

    if (m_enemy->getHp() <= 0) {
        m_state = BattleState::PLAYER_WIN;
    } else {
        m_state = BattleState::ENEMY_TURN;
    }
}

void BattleSystem::EnemyAttack() {
    int damage = DamageCalculator::CalculatePhysicalDamage(
        m_enemy->getPhysicalAttack(), m_player->getDefense());
    m_player->setHp(m_player->getHp() - damage);
    printf("%s 对 %s 造成 %d 点伤害\n",
           m_enemy->getName().c_str(), m_player->getName().c_str(), damage);

    if (m_player->getHp() <= 0) {
        m_state = BattleState::PLAYER_LOSE;
    }
}

bool BattleSystem::IsOver() const {
    return m_state == BattleState::PLAYER_WIN || m_state == BattleState::PLAYER_LOSE;
}

BattleState BattleSystem::GetState() const {
    return m_state;
}