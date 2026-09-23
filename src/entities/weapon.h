#ifndef WEAPON_H
#define WEAPON_H

#include <string>
#include <json.hpp>

enum class WeaponType {
    WEAPON01 = 1,
};

class Weapon {
public:
    Weapon(short id = 1);
    ~Weapon();

    bool init(short id);
    bool initWeapon01();
    std::string getName() const;
    int getPhysicalAttack() const;
    int getSeaPower() const;
    short getId() const;
    nlohmann::json readFromJson();
    

private:
    short m_id;
    std::string m_name;
    int m_physicalAttack;
    int m_seaPower;
    
};

#endif // WEAPON_H