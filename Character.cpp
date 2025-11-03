#include "Character.h"
#include <iostream>

// constructor
Character::Character(string n, int l, float max, float h, float maxR, float r)
    : name(n), level(l), maxHp(max), hp(h), maxResource(maxR), resource(r), isAlive(true), isDefending(false), exp(0), nextLevel(nextLevelFormula(l)), expDrop(expDropFormula(l)), isMagic(false) {
        stats.emplace_back(Attack);
        stats.emplace_back(Defense);

        skills.emplace_back(basicAttack);
        skills.emplace_back(basicDefend);
    };

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
float Character::getMaxResource() const { return maxResource; }
float Character::getResource() const { return resource; }
float Character::getAtk() const { return Attack.current; }
float Character::getDef() const { return Defense.current; }
bool Character::getIsMagic() const { return isMagic; }
bool Character::getIsAlive() const { return isAlive; }
bool Character::getIsDefending() const { return isDefending; }

// setters
void Character::setHp(float h) { hp = h; }
void Character::setResource(float r) { resource = r; }
void Character::setIsAlive(bool b) { isAlive = b; }
void Character::setIsDefending(bool b) { isDefending = b; }
void Character::setResource(float r) { resource = r; }

// take dmg
void Character::takeDmg(float amount) {
    if (!isAlive) return;
    
    float dmg;

    // ATK*1.5 - DEF
    if (isDefending) { dmg = amount*1.5 - Defense.current*1.5; }
    else { dmg = amount*1.5 - Defense.current; }

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
    target.takeDmg(Attack.current);
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
    this->setHpStat();
    this->setAtkStat();
    this->setDefStat();
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
    cout << "ATK: " << Attack.current << endl;
    cout << "DEF: " << Defense.current << endl;
    cout << "STATUS: " << (isAlive ? "Alive" : "Dead") << endl;
}