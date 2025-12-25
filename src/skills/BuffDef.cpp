#include "BuffDef.h"
#include "../character/Character.h"
#include "../Terminal.h"

BuffDef::BuffDef(std::string n, bool magic, bool dmg, float p, float c, TargetType tt)
    : Skill(n,magic,dmg,p,c,tt) {}

void BuffDef::useSkill(Character* source, Character* target) {
    float statPoints;

    statPoints = target->getDef() + points * (source->getLevel() * 0.5);

    target->setDefense(statPoints);
    std::cout << terminal::foreground(target->getHealthColor()) << target->getName() << terminal::reset << "'s defense was raised by " << ((isMagic) ? terminal::foreground(terminal::brightMagenta) : terminal::foreground(terminal::brightGreen)) << statPoints << terminal::reset << "!\n";
}