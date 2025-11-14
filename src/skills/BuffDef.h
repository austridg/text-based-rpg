#ifndef BUFFDEF_H
#define BUFFDEF_H

#include "Skill.h"

class Character;

class BuffDef : public Skill {
public:
    BuffDef(bool magic, float p, float c, TargetType tt);

    void useSkill(Character* source, Character* target) override;
};

#endif