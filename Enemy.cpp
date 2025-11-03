#include "Enemy.h"

Enemy::Enemy(const string n,int level)
    : Character(n, level, enemyHp(level), enemyHp(level),enemyResource(level),enemyResource(level)) {
        Attack.current = enemyAtk(level);
        Defense.current = enemyDef(level);
    };

void Enemy::setHpStat() { maxHp = enemyHp(level); hp = enemyHp(level); }

void Enemy::setAtkStat() { Attack.current = enemyAtk(level); }

void Enemy::setDefStat() { Defense.current = enemyDef(level); }