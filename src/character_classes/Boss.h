#ifndef BOSS_H
#define BOSS_H

#include "Character/Character.h"

class Boss : public Character {
public:
    Boss(const string& n,int lvl);

    void setHpStat() override;
    void setResourceStat() override;
    void setAtkStat() override;
    void setDefStat() override;
    void setMagicStat() override;
    void setResistanceStat() override;
};

#endif