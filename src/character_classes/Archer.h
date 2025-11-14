#ifndef ARCHER_H
#define ARCHER_H

#include "Character/Character.h"

class Archer : public Character {
public:
    Archer (const string& n,int lvl);

    void setHpStat() override;
    void setResourceStat() override;
    void setAtkStat() override;
    void setDefStat() override;
    void setMagicStat() override;
    void setResistanceStat() override;
};

#endif