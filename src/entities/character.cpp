#include "character.h"
#include <stdio.h>
#include <string>

Character::Character() {
    m_type = CharacterType::PLAYER;
}

CharacterType Character::getType() const {
    return m_type;
}

int Character::getPhysicalAttack() const {
    return m_physicalAttack;
}

int Character::getDefense() const {
    return m_defense;
}

int Character::getHp() const {
    return m_hp;
}

void Character::setHp(int hp) {
    this->m_hp = hp;
}

void Character::setPhysicalAttack(int physicalAttack) {
    this->m_physicalAttack = physicalAttack;
}

std::string Character::getName() const {
    return m_name;
}

void Character::setName(std::string name) {
    this->m_name = name;
}

void Character::setDefense(int defense) {
    this->m_defense = defense;
}

void Character::setType(CharacterType type) {
    this->m_type = type;
}
