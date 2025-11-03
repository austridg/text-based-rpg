#include "Mage.h"

Mage::Mage(const string& n,int level)
    : Character(n, level, mageHp(level), mageHp(level),mageResource(level),mageResource(level)) {
        stats.emplace_back(Magic);
        
        Attack.current = mageAtk(level);
        Defense.current = mageDef(level);
        Magic.current = mageMagic(level);
    };

void Mage::setHpStat() { maxHp = mageHp(level); hp = mageHp(level); }

void Mage::setAtkStat() {Defense.current = mageAtk(level); }

void Mage::setDefStat() {Defense.current = mageDef(level); }