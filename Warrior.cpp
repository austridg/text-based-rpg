#include "Warrior.h"

Warrior::Warrior(const string& n,int level)
    : Character(n, level, warriorHp(level), warriorHp(level),warriorResource(level),warriorResource(level)) {
        Attack.current = warriorAtk(level);
        Defense.current = warriorDef(level);
    };

void Warrior::setHpStat() { maxHp = warriorHp(level); hp = warriorHp(level); }

void Warrior::setAtkStat() {Defense.current = warriorAtk(level); }

void Warrior::setDefStat() {Defense.current = warriorDef(level); }