#include "enemy.h"
#include <stdio.h>
#include <fstream>

Enemy::Enemy(short id) 
        : m_id(id)
{
    if (init(id)) {
        setType(CharacterType::ENEMY);
        printf("Enemy %s initialized.\n", m_name.c_str());
    }
}

Enemy::~Enemy() {
}

bool Enemy::init(short id) {
    switch (id) {
        case static_cast<short>(EnemyType::ENEMY01):
            return initEnemy01();
        default:
            return false;
    }
   
    return true;
}

bool Enemy::initEnemy01() {
    nlohmann::json j = readFromJson();
    m_status = new EnemyStatus();
    m_name = j["Gebulin"]["Name"];
    m_status->hp = j["Gebulin"]["Status"]["Hp"];
    m_status->physicalAttack = j["Gebulin"]["Status"]["PhysicalAttack"];
    m_status->defense = j["Gebulin"]["Status"]["Defense"];
    m_status->seaPower = j["Gebulin"]["Status"]["SeaPower"];
    if (m_name.empty()) {
        return false;
    }
    return true;
}

nlohmann::json Enemy::readFromJson() {
    std::ifstream f("data/enemies.json");
    nlohmann::json j = nlohmann::json::parse(f);
    return j;
}

std::string Enemy::getName() const {
    return m_name;
}

void Enemy::setName(std::string name) {
    this->m_name = name;
}

int Enemy::getHp() const {
    return m_status->hp;
}

void Enemy::setHp(int hp) {
    this->m_status->hp = hp;
}

int Enemy::getPhysicalAttack() const {
    return m_status->physicalAttack;
}

void Enemy::setPhysicalAttack(int physicalAttack) {
    this->m_status->physicalAttack = physicalAttack;
}

int Enemy::getDefense() const {
    return m_status->defense;
}

void Enemy::setDefense(int defense) {
    this->m_status->defense = defense;
}

int Enemy::getSeaPower() const {
    return m_status->seaPower;
}

void Enemy::setSeaPower(int seaPower) {
    this->m_status->seaPower = seaPower;
}

EnemyStatus* Enemy::getStatus() const {
    return m_status;
}