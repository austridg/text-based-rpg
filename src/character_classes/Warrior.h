#ifndef WARRIOR_H
#define WARRIOR_H

#include "Character/Character.h"

class Warrior : public Character {
public:
    Warrior(const string& n,int lvl);

    void setHpStat() override;
    void setResourceStat() override;
    void setAtkStat() override;
    void setDefStat() override;
    void setMagicStat() override;
    void setResistanceStat() override;
};

#endif