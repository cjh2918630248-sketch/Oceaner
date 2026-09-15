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

std::string Player::getName() const override {
    return m_name;
}

void Player::setName(std::string name) override {
    this->m_name = name;
}

int Player::getHp() const override {
    return m_hp;
}

void Player::setHp(int hp) override {
    this->m_hp = hp;
}

void Player::setPhysicalAttack(int physicalAttack) override {
    this->m_physicalAttack = physicalAttack;
}

void Player::setDefense(int defense) override {
    this->m_defense = defense;
}

void Player::setHp(int hp) override {
    this->m_hp = hp;
}
