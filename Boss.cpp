#include "Boss.h"

Boss::Boss(const string n,int level)
    : Character(n, level, bossHp(level), bossHp(level),bossResource(level),bossResource(level)) { 
        expDrop = expDropBossFormula(level); 

        Attack.current = bossAtk(level);
        Defense.current = bossDef(level);
    }

void Boss::setHpStat() { maxHp = bossHp(level); hp = bossHp(level); }

void Boss::setAtkStat() { Attack.current = bossAtk(level); }

void Boss::setDefStat() { Defense.current = bossDef(level); }