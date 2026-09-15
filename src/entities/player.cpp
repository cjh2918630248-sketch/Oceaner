#include "player.h"
#include <stdio.h>
#include <fstream>

Player::Player() {
    if(init()){
        setName(m_name);
        setHp(m_hp);
        setPhysicalAttack(m_physicalAttack);
        setDefense(m_defense);
        setType(CharacterType::PLAYER);
        printf("Player %s initialized.\n", m_name.c_str());
    }
}

Player::~Player() {
}

bool Player::init() {
    nlohmann::json j = readFromJson();
    m_name = j["Player"]["Name"];
    m_hp = j["Player"]["Status"]["Hp"];
    m_physicalAttack = j["Player"]["physicalAttack"];
    m_defense = j["Player"]["Status"]["Defense"];
    if(m_name.empty()){
        return false;
    }
    return true;
}

nlohmann::json Player::readFromJson() {
    std::ifstream f("data/characters.json");
    nlohmann::json j = nlohmann::json::parse(f);
    return j;
}

std::string Player::getName() const {
    return m_name;
}

void Player::setName(std::string name) {
    this->m_name = name;
}

int Player::getHp() const {
    return m_hp;
}

void Player::setHp(int hp) {
    this->m_hp = hp;
}

int Player::getPhysicalAttack() const {
    return m_physicalAttack;
}

void Player::setPhysicalAttack(int physicalAttack) {
    this->m_physicalAttack = physicalAttack;
}

void Player::setDefense(int defense) {
    this->m_defense = defense;
}

int Player::getDefense() const {
    return m_defense;
}
