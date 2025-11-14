#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <vector>
#include "Formulas.hpp"
#include "skills/Skill.h"
#include "skills/Skills.h"
#include "Stat.h"

using namespace std;

class Character {
protected:
    string name;
    Stats stats;
    float exp; // TODO - progression struct (similar to stats) (would need refactoring for leveling system)
    float nextLevel;
    float expDrop;
    float resource;
    bool isAlive;
    bool isDefending;
    bool isMagic;
    vector<Skill*> skills;
public:
    // Constructor / Destructor
    Character(string n,int l);

    virtual ~Character() = default;

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
    float getMagic() const;
    float getResistance() const;
    bool getIsMagic() const;
    bool getIsAlive() const;
    bool getIsDefending() const;
    const vector<Skill*>& getSkills();

    // setters
    void setHp(float h);
    void setResource(float r);
    void setAttack(float atk);
    void setDefense(float def);
    void setMagic(float m);
    void setResistance(float r);
    void setIsAlive(bool b);
    void setIsDefending(bool b);

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
};

#endif