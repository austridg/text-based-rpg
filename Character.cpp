#include "Character.h"
#include <iostream>

// constructor
Character::Character(string n, int l, float max, float h, float a, float d)
    : name(n), level(l), maxHp(max), hp(h), atk(a), def(d), isAlive(true), isDefending(false), exp(0), nextLevel(nextLevelFormula(l)), expDrop(expDropFormula(l)), isMagic(false) {};

// destructor
Character::~Character() {};

// getters
const string& Character::getName() const { return name; }
int Character::getLevel() const { return level; }
float Character::getExp() const { return exp; }
float Character::getNextLevel() const { return nextLevel; }
float Character::getExpDrop() const { return expDrop; }
float Character::getMaxHp() const { return maxHp; }
float Character::getHp() const { return hp; }
float Character::getAtk() const { return atk; }
float Character::getDef() const { return def; }
bool Character::getIsAlive() const { return isAlive; }
bool Character::getIsDefending() const { return isDefending; }

// setters
void Character::setIsAlive(bool b) { isAlive = b; }
void Character::setIsDefending(bool b) { isDefending = b; }

// take dmg
void Character::takeDmg(float amount) {
    if (!isAlive) return;
    
    float dmg;

    // ATK*1.5 - DEF
    if (isDefending) { dmg = amount*1.5 - def*1.5; }
    else { dmg = amount*1.5 - def; }

    if (dmg <= 0) {
        cout << name << " didn't take any damage!\n";
        return;
    }

    hp -= dmg;

    if (hp <= 0) { isAlive = false; hp = 0; }
}

// heal
void Character::heal() {
    if (!isAlive) return;

    hp += 5;

    if (hp > maxHp) { hp = maxHp; }
}

void Character::fullHeal() {
    if (!isAlive) return;

    hp = maxHp;
}

// attack
void Character::attack(Character& target) {
    cout << name << " attacked " << target.getName() << "!" << endl;
    target.takeDmg(atk);
    cout << target.getName() << " HP: " << target.getHp() << " / " << target.getMaxHp() << endl;
}

// defend
void Character::defend() {
    isDefending = true;

    cout << name << " is now defending!\n";
}

// reset
void Character::reset() {
    if (isDefending) { isDefending = false; }
}

void Character::levelUp() {
    level = level + 1;
    this->setHp();
    this->setAtk();
    this->setDef();
}

void Character::canLevel(Character& target) {
    exp += target.getExpDrop();

    if (exp >= nextLevel) {
        float difference = exp - nextLevel;
        levelUp();
        exp = difference;
        nextLevel = nextLevelFormula(level);
    }
}

// print info
void Character::printInfo() const {
    cout << "===== " << name << " =====\n";
    cout << "LEVEL: " << level << " (" << exp << "exp / " << nextLevel << "exp)" << endl;
    cout << "HP: " << hp << " / " << maxHp << endl;
    cout << "ATK: " << atk << endl;
    cout << "DEF: " << def << endl;
    cout << "STATUS: " << (isAlive ? "Alive" : "Dead") << endl;
}