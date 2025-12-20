#include "SkillList.h"

#include "DamageHp.h"
#include "BuffDef.h"

DamageHp BasicAttack("Attack", false, true, 10, 0, TargetType::ONE_ENEMY);
BuffDef  BasicDefend("Defend", false, false, 5, 0, TargetType::SELF);