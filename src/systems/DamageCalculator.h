#ifndef DAMAGE_CALCULATOR_H
#define DAMAGE_CALCULATOR_H

class DamageCalculator {
public:
    static int CalculatePhysicalDamage(int attack, int defense);
    static int CalculateSeaDamage(int seaPower);
};

#endif