#include "SkillList.h"

#include "DamageHp.h"
#include "BuffDef.h"
#include "BuffAtk.h"

// (name,isMagic,isDmg,points,cost,TargetType)
DamageHp BasicAttack("Attack", false, true, 10, 0, TargetType::ONE_ENEMY);
BuffDef  BasicDefend("Defend", false, false, 5, 0, TargetType::SELF);

// Warrior Skills
DamageHp StrongAttack("Strong Attack", false, true, 25, 15, TargetType::ONE_ENEMY);
BuffAtk  Warcry("Warcry", false, true, 15, 20, TargetType::ALL_ALLIES);

// Archer Skills
DamageHp ArrowShot("Arrow Shot", false, true, 25, 15, TargetType::ONE_ENEMY);
DamageHp Volley("Volley", false, true, 10, 35, TargetType::ALL_ENEMIES);

// Mage Skills
DamageHp Fireball("Fireball", true, false, 25, 15, TargetType::ONE_ENEMY);
