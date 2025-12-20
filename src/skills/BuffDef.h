#ifndef BUFFDEF_H
#define BUFFDEF_H

#include "Skill.h"

class Character;

class BuffDef : public Skill {
public:
    BuffDef(std::string n, bool magic, bool dmg, float p, float c, TargetType tt);

    void useSkill(Character* source, Character* target) override;
};

#endif