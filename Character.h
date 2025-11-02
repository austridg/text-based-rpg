#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include "formulas.hpp"
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
    float atk;
    float def;
    float isAlive;
    float isDefending;
    bool isMagic;
public:
    // Constructor / Destructor
    Character(string n,int l, float maxH,float h,float a,float d);

    virtual ~Character();

    // getters
    const string& getName() const;
    int getLevel() const;
    float getExp() const;
    float getNextLevel() const;
    float getExpDrop() const;
    float getMaxHp() const;
    float getHp() const;
    float getAtk() const;
    float getDef() const;
    bool getIsAlive() const;
    bool getIsDefending() const;

    // setters
    void setIsAlive(bool b);
    void setIsDefending(bool b);

    // set stats
    virtual void setHp() = 0;
    virtual void setAtk() = 0;
    virtual void setDef() = 0;

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