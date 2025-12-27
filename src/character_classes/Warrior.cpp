#include "Warrior.h"
#include "../skills/SkillList.h"
#include "../skills/DamageHp.h"
#include "../skills/BuffAtk.h"
#include "../skills/BuffDef.h"

Warrior::Warrior(const std::string& n,int level)
    : Character(n, level) {
        stats.hp = warriorHp(level);
        stats.maxHp = warriorHp(level);
        stats.resource = warriorResource(level);
        stats.maxResource = warriorResource(level);
        stats.attack = warriorAtk(level);
        stats.maxAttack = warriorAtk(level);
        stats.defense = warriorDef(level);
        stats.maxDefense = warriorDef(level);
        stats.magic = warriorMagic(level);
        stats.maxMagic = warriorMagic(level);
        stats.resistance = warriorResistance(level);
        stats.maxResistance = warriorResistance(level);

        unlockableSkills = {
            {2,&StrongAttack},
            {3,&Warcry}
        };

        isMagic = false;

        characterClass = ClassType::Warrior;
    };

void Warrior::setHpStat() { stats.maxHp = warriorHp(stats.level); stats.hp = warriorHp(stats.level); }

void Warrior::setResourceStat() { stats.maxResource = warriorResource(stats.level); stats.resource = warriorResource(stats.level); }

void Warrior::setAtkStat() {stats.attack = warriorAtk(stats.level); }

void Warrior::setDefStat() {stats.defense = warriorDef(stats.level); }

void Warrior::setMagicStat() { stats.magic = warriorMagic(stats.level); }

void Warrior::setResistanceStat() { stats.resistance = warriorResistance(stats.level); }

void Warrior::printClass() const { std::cout << "Warrior"; }