#include "Mage.h"

Mage::Mage(const std::string& n,int level)
    : Character(n, level) {
        stats.hp = mageHp(level);
        stats.maxHp = mageHp(level);
        stats.resource = mageResource(level);
        stats.maxResource = mageResource(level);
        stats.attack = mageAtk(level);
        stats.maxAttack = mageAtk(level);
        stats.defense = mageDef(level);
        stats.maxDefense = mageDef(level);
        stats.magic = mageMagic(level);
        stats.maxMagic = mageMagic(level);
        stats.resistance = mageResistance(level);
        stats.maxResistance = mageResistance(level);

        skills.emplace_back(&Fireball);

        unlockableSkills = {
            {2,&WeakenResistance}
        };

        isMagic = true;

        characterClass = ClassType::Mage;
    };

void Mage::setHpStat() { stats.maxHp = mageHp(stats.level); stats.hp = mageHp(stats.level); }

void Mage::setResourceStat() { stats.maxResource = mageResource(stats.level); stats.resource = mageResource(stats.level); }

void Mage::setAtkStat() {stats.attack = mageAtk(stats.level); }

void Mage::setDefStat() {stats.defense = mageDef(stats.level); }

void Mage::setMagicStat() { stats.magic = mageMagic(stats.level); }

void Mage::setResistanceStat() { stats.resistance = mageResistance(stats.level); }

void Mage::printClass() const { std::cout << "Mage"; }