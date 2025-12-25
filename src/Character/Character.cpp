#include "Character.h"
#include "../skills/SkillList.h"
#include "../skills/BuffDef.h"
#include "../skills/DamageHp.h"

// constructor
Character::Character(std::string n, int l) 
    : name(n), exp(0), nextLevel(nextLevelFormula(l)), expDrop(expDropFormula(l)), isAlive(true), isDefending(false) { 
    stats.level = l;
    skills.emplace_back(&BasicAttack);
    skills.emplace_back(&BasicDefend);
}

// getters
std::string Character::getName() const { return name; }
int Character::getLevel() const { return stats.level; }
float Character::getExp() const { return exp; }
float Character::getNextLevel() const { return nextLevel; }
float Character::getExpDrop() const { return expDrop; }
float Character::getMaxHp() const { return stats.maxHp; }
float Character::getHp() const { return stats.hp; }
float Character::getResource() const { return stats.resource; }
float Character::getMaxResource() const { return stats.maxResource; }
float Character::getAtk() const { return stats.attack; }
float Character::getMaxAtk() const { return stats.maxAttack; }
float Character::getDef() const { return stats.defense; }
float Character::getMaxDef() const { return stats.maxDefense; }
float Character::getMagic() const { return stats.magic; }
float Character::getMaxMagic() const { return stats.maxMagic; }
float Character::getResistance() const { return stats.resistance; }
float Character::getMaxResistance() const { return stats.maxResistance; }
bool Character::getIsAlive() const { return isAlive; }
bool Character::getIsDefending() const { return isDefending; }
bool Character::getIsMagic() const { return isMagic; }
const std::vector<Skill*>& Character::getSkills() { return skills; }
size_t Character::getSkillListSize() const { return skills.size(); }
terminal::Color Character::getClassColor() const {
    switch(this->characterClass) {
        case ClassType::Warrior:
            return terminal::brightRed;
            break;
        case ClassType::Mage:
            return terminal::brightBlue;
            break;
        case ClassType::Archer:
            return terminal::brightGreen;
            break;
        case ClassType::Healer:
            return terminal::brightMagenta;
            break;
        case ClassType::Enemy:
        case ClassType::Boss:
            return terminal::white;
            break;
    }
}
terminal::Color Character::getHealthColor() const {
    if(stats.hp >= (0.7*stats.maxHp)) { return terminal::brightGreen; }
    else if(stats.hp >= (0.3*stats.maxHp)) { return terminal::brightYellow; }
    else { return terminal::brightRed; }
}

// setters
void Character::setHp(float h) { stats.hp = h; }
void Character::setResource(float r) { stats.resource = r; }
void Character::setAttack(float atk) { stats.attack = atk; }
void Character::setDefense(float def) { stats.defense = def; }
void Character::setMagic(float m) { stats.magic = m; }
void Character::setResistance(float r) { stats.resistance = r; }
void Character::setIsAlive(bool b) { isAlive = b; }
void Character::setIsDefending(bool b) { isDefending = b; }
void Character::setIsMagic(bool b) { isMagic = b; }

void Character::fullHeal() {
    if (!isAlive) return;

    stats.hp = stats.maxHp;
}

void Character::levelUp() {
    stats.level = stats.level + 1;

    checkNewSkill();

    this->setHpStat();
    this->setResourceStat();
    this->setAtkStat();
    this->setDefStat();
    this->setMagicStat();
    this->setResistanceStat();
}

void Character::canLevel(float xp) {
    exp += xp;

    if (exp >= nextLevel) {
        float difference = exp - nextLevel;
        levelUp();
        exp = difference;
        nextLevel = nextLevelFormula(stats.level);
    }
}

// print info
void Character::printInfo() const {

    std::cout << terminal::foreground(getClassColor()) << "===== " << name << " ( ";
    printClass();
    std::cout << " ) =====\n" << terminal::reset;
    std::cout << "LEVEL: " << stats.level << " (" << exp << "exp / " << nextLevel << "exp)" << " | ";
    std::cout << "HP: " << stats.hp << " / " << stats.maxHp << " | ";
    std::cout << ((this->getIsMagic()) ? "Mana: " : "Stamina: ") << stats.resource << " / " << stats.maxResource << " | ";
    std::cout << "ATK: " << stats.attack << " | ";
    std::cout << "DEF: " << stats.defense << " | ";
    std::cout << "MAG: " << stats.magic << " | ";
    std::cout << "RES: " << stats.resistance << " | ";
    std::cout << "STATUS: " << (isAlive ? "Alive" : "Dead");
    std::cout << std::endl << std::endl;
}

void Character::printSkills() const {
    for (size_t i = 0; i < skills.size(); i++) {
        std::cout << i + 1 << ") " << skills[i]->getName() << std::endl;
    }
}

void Character::checkNewSkill() {
    if(unlockableSkills[stats.level]) {
        skills.emplace_back(unlockableSkills[stats.level]);
    }
}