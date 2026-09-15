#ifndef PLAYER_H
#define PLAYER_H

#include "character.h"
#include <string>
#include <json.hpp>

class Player : public Character {
public:
    Player();
    ~Player();

    bool init();
    int getHp() const override;
    void setHp(int hp) override;
    int getPhysicalAttack() const override;
    void setPhysicalAttack(int physicalAttack) override;
    int getSeaPower() = delete;
    void setSeaPower(int seaPower) = delete;
    int getDefense() const override;
    void setDefense(int defense) override;
    std::string getName() const override;
    void setName(std::string name) override;

    nlohmann::json readFromJson();

private:
    int m_moveSpeed = 10;
};

#endif // PLAYER_H