#include "../skills/Skill.h"
#include "../Formulas.hpp"
#include "../character/Character.h"
#include <iostream>

Skill::Skill(std::string n, bool magic, bool dmg, float p, float c, TargetType tt)
    : name(n), isMagic(magic), isDmg(dmg), points(p), cost(c), targetType(tt) {}

Skill::~Skill() {}

bool Skill::canUse(Character* source) {
    if (source->getResource() < cost) { return false; }
    return true;
}

std::string Skill::getName() const { return name; }
bool Skill::getIsMagic() const { return isMagic; }
float Skill::getPoints() const { return points; }
float Skill::getCost() const { return cost; }
TargetType Skill::getTargetType() const { return targetType; }
terminal::Color Skill::getSkillColor() const {
    if(isMagic) {
        if(isDmg) { return terminal::brightBlue; }
        else { return terminal::brightMagenta; }
    }
    else {
        if(isDmg) { return terminal::brightRed; }
        else { return terminal::brightGreen; }
    }
}

void Skill::cantUse(Character* source) const {
    std::cout << (source->getIsMagic()) ? "Not Enough Mana!\n" : "Not Enough Stamina!\n";
}

// buffatk
BuffAtk::BuffAtk(std::string n, bool magic, bool dmg, float p, float c, TargetType tt)
    : Skill(n,magic,dmg,p,c,tt) {}

void BuffAtk::useSkill(Character* source, Character* target) {
    float statPoints;

    statPoints = points * (source->getLevel() * 0.5);

    target->setAttack(target->getAtk() + statPoints);
    std::cout << terminal::foreground(target->getHealthColor()) << target->getName() << terminal::reset << "'s attack was raised by " << ((isMagic) ? terminal::foreground(terminal::brightMagenta) : terminal::foreground(terminal::brightGreen)) << statPoints << terminal::reset << "!\n";
}

// buffdef
BuffDef::BuffDef(std::string n, bool magic, bool dmg, float p, float c, TargetType tt)
    : Skill(n,magic,dmg,p,c,tt) {}

void BuffDef::useSkill(Character* source, Character* target) {
    float statPoints;

    statPoints = points * (source->getLevel() * 0.5);

    target->setDefense(target->getDef() + statPoints);
    std::cout << terminal::foreground(target->getHealthColor()) << target->getName() << terminal::reset << "'s defense was raised by " << ((isMagic) ? terminal::foreground(terminal::brightMagenta) : terminal::foreground(terminal::brightGreen)) << statPoints << terminal::reset << "!\n";
}

// debuffres
DebuffRes::DebuffRes(std::string n, bool magic, bool dmg, float p, float c, TargetType tt)
    : Skill(n,magic,dmg,p,c,tt) {}

void DebuffRes::useSkill(Character* source, Character* target) {
    float statPoints;

    statPoints = target->getResistance() + points * (source->getLevel() * 0.5);

    target->setResistance(statPoints);
    std::cout << terminal::foreground(target->getHealthColor()) << target->getName() << terminal::reset << "'s defense was raised by " << ((isMagic) ? terminal::foreground(terminal::brightBlue) : terminal::foreground(terminal::brightRed)) << statPoints << terminal::reset << "!\n";
}

// damagehp
DamageHp::DamageHp(std::string n, bool magic, bool dmg, float p, float c, TargetType tt)
    : Skill(n,magic,dmg,p,c,tt) {}

void DamageHp::useSkill(Character* source, Character* target) {
    float dmgStat = (isMagic) ? source->getMagic() : source->getAtk();
    float dmgPoints;

    dmgPoints = target->getIsDefending() ? (dmgStat*0.2) * points - target->getDef()*1.5 : (dmgStat*0.2) * points - target->getDef();

    target->setHp(target->getHp() - dmgPoints);
    if (target->getHp() < 0) { target->setHp(0); }
    std::cout << terminal::foreground(target->getHealthColor()) << target->getName() << terminal::reset << " lost " << ((isMagic) ? terminal::foreground(terminal::brightBlue) : terminal::foreground(terminal::brightRed)) << dmgPoints << terminal::reset << " HP!\n";
}

HealHp::HealHp(std::string n, bool magic, bool dmg, float p, float c, TargetType tt)
    : Skill(n,magic,dmg,p,c,tt) {}

void HealHp::useSkill(Character* source, Character* target) {
    float healPoints;

    healPoints = (source->getMagic()*0.2) * points;

    target->setHp(target->getHp() + healPoints);
    if (target->getHp() > target->getMaxHp()) { target->setHp(target->getMaxHp()); }
    std::cout << terminal::foreground(target->getHealthColor()) << target->getName() << terminal::reset << " gained " << terminal::foreground(terminal::brightMagenta) << healPoints << terminal::reset << " HP!\n";
}