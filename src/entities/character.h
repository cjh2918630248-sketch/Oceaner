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
    virtual std::string getName() const = 0;
    virtual void setName(std::string name);
    virtual int getHp() const = 0;
    virtual int getPhysicalAttack() const = 0;
    int getSeaPower() const;
    virtual int getDefense() const;
    virtual void setHp(int hp) = 0;
    virtual void setPhysicalAttack(int physicalAttack) = 0;
    void setSeaPower(int seaPower);
    virtual void setDefense(int defense) = 0;
    virtual void setType(CharacterType type);

protected:
    std::string m_name = "";
    int m_hp; // 生命值
    int m_physicalAttack; // 物理攻击
    int m_seaPower; // 海蚀伤害
    int m_defense; // 防御值
    CharacterType m_type; // 角色类型
};



#endif // CHARACTER_H
