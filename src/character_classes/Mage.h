#ifndef MAGE_H
#define MAGE_H

#include "Character/Character.h"

class Mage : public Character {
public:
    Mage (const string& n,int lvl);

    void setHpStat() override;
    void setResourceStat() override;
    void setAtkStat() override;
    void setDefStat() override;
    void setMagicStat() override;
    void setResistanceStat() override;
};

#endif