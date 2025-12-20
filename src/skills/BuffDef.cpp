#include "BuffDef.h"
#include "../character/Character.h"

BuffDef::BuffDef(std::string n, bool magic, bool dmg, float p, float c, TargetType tt)
    : Skill(n,magic,dmg,p,c,tt) {}

void BuffDef::useSkill(Character* source, Character* target) {
    float statPoints;

    statPoints = target->getDef() + points * (source->getLevel() * 0.5);

    target->setDefense(statPoints);
    std::cout << target->getName() << "'s defense was raised by " << statPoints << "!\n";
}