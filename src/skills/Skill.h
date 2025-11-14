#ifndef SKILL_H
#define SKILL_H

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
    bool isMagic;
    float points;
    float cost;
    TargetType targetType;
public:
    // constructor / destructor
    Skill(bool magic, float p, float c, TargetType tt);
    virtual ~Skill();

    // getters
    bool getIsMagic() const;
    float getPoints() const;
    float getCost() const;
    TargetType getTargetType() const;

    bool canUse(Character* source);

    virtual void useSkill(Character* source, Character* target) = 0;

    // print
    void cantUse(Character* source) const;
};

#endif