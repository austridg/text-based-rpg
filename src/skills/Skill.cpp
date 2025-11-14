#include "skills/Skill.h"
#include "Formulas.hpp"
#include "Character/Character.h"
#include <iostream>

Skill::Skill(bool magic, float p, float c, TargetType tt)
    : isMagic(magic), points(p), cost(c), targetType(tt) {}

Skill::~Skill() {}

bool Skill::canUse(Character* source) {
    if (source->getResource() < cost) { return false; }
    return true;
}

bool Skill::getIsMagic() const { return isMagic; }
float Skill::getPoints() const { return points; }
float Skill::getCost() const { return cost; }
TargetType Skill::getTargetType() const { return targetType; }

void Skill::cantUse(Character* source) const {
    cout << (source->getIsMagic()) ? "Not Enough Mana!\n" : "Not Enough Stamina!\n";
}