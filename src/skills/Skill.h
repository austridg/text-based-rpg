#ifndef SKILL_H
#define SKILL_H

#include <string>
#include "../Terminal.h"

enum class TargetType {
    SELF,
    ONE_ALLY,
    ALL_ALLIES,
    ONE_ENEMY,
    ALL_ENEMIES
};

class Character;

class Skill {
protected:
    std::string name;
    bool isMagic;
    bool isDmg;
    float points;
    float cost;
    TargetType targetType;
public:
    // constructor / destructor
    Skill(std::string n, bool magic, bool dmg, float p, float c, TargetType tt);
    virtual ~Skill();

    // getters
    std::string getName() const;
    bool getIsMagic() const;
    float getPoints() const;
    float getCost() const;
    TargetType getTargetType() const;
    terminal::Color getSkillColor() const;

    bool canUse(Character* source);

    virtual void useSkill(Character* source, Character* target) = 0;

    // print
    void cantUse(Character* source) const;
};

#endif