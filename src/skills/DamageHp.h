#ifndef DAMAGEHP_H
#define DAMAGEHP_H

#include "Skill.h"

class Character;

class DamageHp : public Skill {
public:
    DamageHp(std::string n, bool magic, bool dmg, float p, float c, TargetType tt);

    void useSkill(Character* source, Character* target) override;
};

#endif