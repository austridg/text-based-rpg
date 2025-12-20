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