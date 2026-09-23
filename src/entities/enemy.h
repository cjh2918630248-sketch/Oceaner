#ifndef ENEMY_H
#define ENEMY_H

#include <string>
#include <json.hpp>
#include "character.h"

enum class EnemyType {
    ENEMY01 = 1,
};

struct EnemyStatus{
    int hp;
    int physicalAttack;
    int defense;
    int seaPower;
};

class Enemy : public Character {
public:
    Enemy(short id);
    ~Enemy();

    bool init(short id);
    bool initEnemy01();
    int getHp() const override;
    void setHp(int hp) override;
    int getPhysicalAttack() const override;
    void setPhysicalAttack(int physicalAttack) override;
    int getDefense() const ;
    void setDefense(int defense);
    std::string getName() const override;
    void setName(std::string name) override;
    int getSeaPower() const;
    void setSeaPower(int seaPower);
    EnemyStatus* getStatus() const;

    nlohmann::json readFromJson();

private:
    short m_id;
    std::string m_name;
    EnemyStatus* m_status = nullptr;
};

#endif // ENEMY_H