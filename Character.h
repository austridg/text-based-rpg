#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <vector>
#include "formulas.hpp"
#include "Skill.h"
#include "Skills.hpp"
#include "Stat.hpp"

using namespace std;

class Character {
protected:
    string name;
    int level;
    float exp;
    float nextLevel;
    float expDrop;
    float maxHp;
    float hp;
    float maxResource; // TODO - Mana or Stamina Refactor
    float resource;
    bool isAlive;
    bool isDefending;
    bool isMagic;
    vector<Stat> stats; // TODO - Refine Stats Vector Functionality
    vector<Skill> skills;
public:
    // Constructor / Destructor
    Character(string n,int l, float maxH,float h,float maxR,float r);

    virtual ~Character();

    // getters
    const string& getName() const;
    int getLevel() const;
    float getExp() const;
    float getNextLevel() const;
    float getExpDrop() const;
    float getMaxHp() const;
    float getHp() const;
    float getMaxResource() const;
    float getResource() const;
    float getAtk() const;
    float getDef() const;
    bool getIsMagic() const;
    bool getIsAlive() const;
    bool getIsDefending() const;

    // setters
    void setHp(float h);
    void setResource(float r);
    void setIsAlive(bool b);
    void setIsDefending(bool b);
    void setResource(float r);

    // set stats
    virtual void setHpStat() = 0;
    virtual void setAtkStat() = 0;
    virtual void setDefStat() = 0;
    virtual void setResourceStat() = 0;

    // take dmg
    virtual void takeDmg(float amount);

    // heal
    virtual void heal();

    // full heal
    void fullHeal();

    // attack
    virtual void attack(Character& target);

    // defend
    virtual void defend();

    // reset
    void reset();

    void canLevel(Character& target);

    void levelUp();

    // print info
    void printInfo() const;
};

#endif