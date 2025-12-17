#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <vector>
#include <iostream>
#include "../Formulas.hpp"
#include "../skills/Skill.h"
#include "../skills/SkillList.h"
#include "Stat.h"

using namespace std;

enum class ClassType{
    Warrior,
    Mage,
    Archer,
    Healer,
    Boss,
    Enemy
};

class Character {
protected:
    string name;
    Stats stats;
    float exp; // TODO - progression struct (similar to stats) (would need refactoring for leveling system)
    float nextLevel;
    float expDrop;
    bool isAlive;
    bool isDefending;
    bool isMagic;
    vector<Skill*> skills;
    ClassType characterClass;
public:
    // Constructor / Destructor
    Character(string n,int l);

    virtual ~Character() = default;

    // getters
    std::string getName() const;
    int getLevel() const;
    float getExp() const;
    float getNextLevel() const;
    float getExpDrop() const;
    float getMaxHp() const;
    float getHp() const;
    float getResource() const;
    float getMaxResource() const;
    float getAtk() const;
    float getMaxAtk() const;
    float getDef() const;
    float getMaxDef() const;
    float getMagic() const;
    float getMaxMagic() const;
    float getResistance() const;
    float getMaxResistance() const;
    bool getIsAlive() const;
    bool getIsDefending() const;
    bool getIsMagic() const;
    const vector<Skill*>& getSkills();
    size_t getSkillListSize() const;

    // setters
    void setHp(float h);
    void setAttack(float atk);
    void setDefense(float def);
    void setResource(float r);
    void setMagic(float m);
    void setResistance(float r);
    void setIsAlive(bool b);
    void setIsDefending(bool b);
    void setIsMagic(bool b);

    typedef float(*construct_attack)(int level);

    // set stats FOR LEVELING
    virtual void setHpStat() = 0;
    virtual void setResourceStat() = 0;
    virtual void setAtkStat() = 0;
    virtual void setDefStat() = 0;
    virtual void setMagicStat() = 0;
    virtual void setResistanceStat() = 0;

    // full heal
    void fullHeal();

    // defend
    virtual void defend();

    // reset
    void resetIsDefending();

    void canLevel(float xp);

    void levelUp();

    // print info
    void printInfo() const;

    void printSkills() const;

    virtual void printClass() const = 0;
};

#endif