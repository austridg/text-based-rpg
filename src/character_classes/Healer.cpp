#include "Healer.h"

Healer::Healer(const string& n,int level)
    : Character(n, level) {
        stats.hp = healerHp(level);
        stats.maxHp = healerHp(level);
        stats.resource = healerResource(level);
        stats.maxResource = healerResource(level);
        stats.attack = healerAtk(level);
        stats.maxAttack = healerAtk(level);
        stats.defense = healerDef(level);
        stats.maxDefense = healerDef(level);
        stats.magic = healerMagic(level);
        stats.maxMagic = healerMagic(level);
        stats.resistance = healerResistance(level);
        stats.maxResistance = healerResistance(level);

        characterClass = ClassType::Healer;
    };

void Healer::setHpStat() { stats.maxHp = healerHp(stats.level); stats.hp = healerHp(stats.level); }

void Healer::setResourceStat() { stats.maxResource = healerResource(stats.level); stats.resource = healerResource(stats.level); }

void Healer::setAtkStat() {stats.attack = healerAtk(stats.level); }

void Healer::setDefStat() {stats.defense = healerDef(stats.level); }

void Healer::setMagicStat() { stats.magic = healerMagic(stats.level); }

void Healer::setResistanceStat() { stats.resistance = healerResistance(stats.level); }

void Healer::printClass() const { std::cout << "Healer"; }