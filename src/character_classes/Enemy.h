#ifndef ENEMY_H
#define ENEMY_H

#include "Character/Character.h"

class Enemy : public Character {
public:
    Enemy(const string& n,int lvl);

    void setHpStat() override;
    void setResourceStat() override;
    void setAtkStat() override;
    void setDefStat() override;
    void setMagicStat() override;
    void setResistanceStat() override;
};

#endif