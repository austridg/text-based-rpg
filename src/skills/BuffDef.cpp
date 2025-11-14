#include "BuffDef.h"
#include "Character/Character.h"

BuffDef::BuffDef(bool magic, float p, float c, TargetType tt)
    : Skill(magic,p,c,tt) {}

void BuffDef::useSkill(Character* source, Character* target) {
    if (!canUse(source)) return;

    target->setDefense(target->getDef() + points * (source->getLevel() * 0.5));
}