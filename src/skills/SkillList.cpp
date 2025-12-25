#include "SkillList.h"

#include "DamageHp.h"
#include "BuffDef.h"

// (name,isMagic,isDmg,points,cost,TargetType)
DamageHp BasicAttack("Attack", false, true, 10, 0, TargetType::ONE_ENEMY);
BuffDef  BasicDefend("Defend", false, false, 5, 50, TargetType::SELF);
DamageHp ArrowShot("Arrow Shot", false, true, 25, 15, TargetType::ONE_ENEMY);