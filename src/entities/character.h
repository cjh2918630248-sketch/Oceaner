#ifndef CHARACTER_H
#define CHARACTER_H
#include <string>

enum class CharacterType {
    PLAYER = 0,
    ENEMY = 1,
    NPC = 2
};

class Character {
public:
    Character();
    virtual ~Character() = default;

    CharacterType getType() const;
    std::string getName() const;
    void setName(std::string name);
    int getHp() const;
    int getPhysicalAttack() const;
    int getSeaPower() const;
    int getDefense() const;
    void setHp(int hp);
    void setPhysicalAttack(int physicalAttack);
    void setSeaPower(int seaPower);
    void setDefense(int defense);
    void setType(CharacterType type);

private:
    std::string m_name = "";
    int m_hp; // 生命值
    int m_physicalAttack; // 物理攻击
    int m_seaPower; // 海蚀伤害
    int m_defense; // 防御值
    CharacterType m_type; // 角色类型
};



#endif // CHARACTER_H
