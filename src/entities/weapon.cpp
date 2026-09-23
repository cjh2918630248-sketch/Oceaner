#include "weapon.h"
#include <stdio.h>
#include <fstream>

Weapon::Weapon(short id) : m_id(id) {
    if (init(id)) {
        printf("Weapon %s initialized.\n", m_name.c_str());
    }
}

Weapon::~Weapon() {
}

bool Weapon::init(short id) {
    switch (id) {
        case static_cast<short>(WeaponType::WEAPON01):
            return initWeapon01();
        default:
            return false;
    }
   
    return true;
}

bool Weapon::initWeapon01() {
    nlohmann::json j = readFromJson();
    m_name = j["Sword01"]["Name"];
    m_physicalAttack = j["Sword01"]["PhysicalAttack"];
    m_seaPower = j["Sword01"]["SeaPower"];
    if (m_name.empty() || m_physicalAttack == 0) {
        return false;
    }
    return true;
}

nlohmann::json Weapon::readFromJson() {
    std::ifstream f("data/weapons.json");
    nlohmann::json j = nlohmann::json::parse(f);
    return j;
}

short Weapon::getId() const {
    return m_id;
}

std::string Weapon::getName() const {
    return m_name;
}

int Weapon::getPhysicalAttack() const {
    return m_physicalAttack;
}

int Weapon::getSeaPower() const {
    return m_seaPower;
}   

