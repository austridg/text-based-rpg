#include "Enemy.h"

Enemy::Enemy(const string& n,int level)
    : Character(n, level) {
        stats.hp = enemyHp(level);
        stats.maxHp = enemyHp(level);
        stats.resource = enemyResource(level);
        stats.maxResource = enemyResource(level);
        stats.attack = enemyAtk(level);
        stats.maxAttack = enemyAtk(level);
        stats.defense = enemyDef(level);
        stats.maxDefense = enemyDef(level);
        stats.magic = enemyMagic(level);
        stats.maxMagic = enemyMagic(level);
        stats.resistance = enemyResistance(level);
        stats.maxResistance = enemyResistance(level);

        characterClass = ClassType::Enemy;
    };

void Enemy::setHpStat() { stats.maxHp = enemyHp(stats.level); stats.hp = enemyHp(stats.level); }

void Enemy::setResourceStat() { stats.maxResource = enemyResource(stats.level); stats.resource = enemyResource(stats.level); }

void Enemy::setAtkStat() {stats.attack = enemyAtk(stats.level); }

void Enemy::setDefStat() {stats.defense = enemyDef(stats.level); }

void Enemy::setMagicStat() { stats.magic = enemyMagic(stats.level); }

void Enemy::setResistanceStat() { stats.resistance = enemyResistance(stats.level); }

void Enemy::printClass() const { std::cout << "Enemy"; }