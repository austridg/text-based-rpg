#include "Boss.h"

Boss::Boss(const std::string& n,int level)
    : Character(n, level) {
        stats.hp = bossHp(level);
        stats.maxHp = bossHp(level);
        stats.resource = bossResource(level);
        stats.maxResource = bossResource(level);
        stats.attack = bossAtk(level);
        stats.maxAttack = bossAtk(level);
        stats.defense = bossDef(level);
        stats.maxDefense = bossDef(level);
        stats.magic = bossMagic(level);
        stats.maxMagic = bossMagic(level);
        stats.resistance = bossResistance(level);
        stats.maxResistance = bossResistance(level);

        skills.emplace_back(&Fireball);
        skills.emplace_back(&BasicHeal);
        skills.emplace_back(&WeakenResistance);
        skills.emplace_back(&StrengthenDefense);
        skills.emplace_back(&Hellfire);

        isMagic = false;

        characterClass = ClassType::Boss;
    };

void Boss::setHpStat() { stats.maxHp = bossHp(stats.level); stats.hp = bossHp(stats.level); }

void Boss::setResourceStat() { stats.maxResource = bossResource(stats.level); stats.resource = bossResource(stats.level); }

void Boss::setAtkStat() {stats.attack = bossAtk(stats.level); }

void Boss::setDefStat() {stats.defense = bossDef(stats.level); }

void Boss::setMagicStat() { stats.magic = bossMagic(stats.level); }

void Boss::setResistanceStat() { stats.resistance = bossResistance(stats.level); }

void Boss::printClass() const { std::cout << "Boss"; }