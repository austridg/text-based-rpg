#ifndef BUFFATK_H
#define BUFFATK_H

#include "Skill.h"

class Character;

class BuffAtk : public Skill {
public:
    BuffAtk(std::string n, bool magic, bool dmg, float p, float c, TargetType tt);

    void useSkill(Character* source, Character* target) override;
};

#endif