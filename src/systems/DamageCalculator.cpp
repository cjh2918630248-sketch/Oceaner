#include "systems/DamageCalculator.h"

int DamageCalculator::CalculatePhysicalDamage(int attack, int defense) {
    int damage = attack - defense;
    return damage > 0 ? damage : 1;
}

int DamageCalculator::CalculateSeaDamage(int seaPower) {
    return seaPower;
}