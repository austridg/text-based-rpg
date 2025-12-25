#include "Archer.h"

Archer::Archer(const std::string& n,int level)
    : Character(n, level) {
        stats.hp = archerHp(level);
        stats.maxHp = archerHp(level);
        stats.resource = archerResource(level);
        stats.maxResource = archerResource(level);
        stats.attack = archerAtk(level);
        stats.maxAttack = archerAtk(level);
        stats.defense = archerDef(level);
        stats.maxDefense = archerDef(level);
        stats.magic = archerMagic(level);
        stats.maxMagic = archerMagic(level);
        stats.resistance = archerResistance(level);
        stats.maxResistance = archerResistance(level);

        isMagic = false;

        characterClass = ClassType::Archer;
    };

void Archer::setHpStat() { stats.maxHp = archerHp(stats.level); stats.hp = archerHp(stats.level); }

void Archer::setResourceStat() { stats.maxResource = archerResource(stats.level); stats.resource = archerResource(stats.level); }

void Archer::setAtkStat() {stats.attack = archerAtk(stats.level); }

void Archer::setDefStat() {stats.defense = archerDef(stats.level); }

void Archer::setMagicStat() { stats.magic = archerMagic(stats.level); }

void Archer::setResistanceStat() { stats.resistance = archerResistance(stats.level); }

void Archer::printClass() const { std::cout << "Archer"; }