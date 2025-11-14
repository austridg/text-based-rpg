#ifndef HEALER_H
#define HEALER_H

#include "Character/Character.h"

class Healer : public Character {
public:
    Healer (const string& n,int lvl);

    void setHpStat() override;
    void setResourceStat() override;
    void setAtkStat() override;
    void setDefStat() override;
    void setMagicStat() override;
    void setResistanceStat() override;
};

#endif