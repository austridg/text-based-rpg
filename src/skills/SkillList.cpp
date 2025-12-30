#include "SkillList.h"
#include "Skill.h"

// (name,isMagic,isDmg,points,cost,TargetType)
DamageHp BasicAttack("Attack", false, true, 10.f, 0.f, TargetType::ONE_ENEMY);
BuffDef  BasicDefend("Defend", false, false, 5.f, 0.f, TargetType::SELF);

// Warrior Skills
DamageHp StrongAttack("Strong Attack", false, true, 25.f, 15.f, TargetType::ONE_ENEMY);
BuffAtk  Warcry("Warcry", false, true, 15.f, 5.f, TargetType::ALL_ALLIES);

// Archer Skills
DamageHp ArrowShot("Arrow Shot", false, true, 25.f, 15.f, TargetType::ONE_ENEMY);
DamageHp Volley("Volley", false, true, 10.f, 8.75f, TargetType::ALL_ENEMIES);

// Mage Skills
DamageHp Fireball("Fireball", true, true, 13.f, 10.f, TargetType::ONE_ENEMY);
DebuffRes WeakenResistance("Weaken Resistance", true, true, 15.f, 20.f, TargetType::ONE_ENEMY);

// Healer Skills
HealHp BasicHeal("Heal", true, false, 10.f, 5.f, TargetType::ONE_ALLY);
BuffDef StrengthenDefense("Strengthen Defense", true, false, 20.f, 15.f, TargetType::ONE_ALLY);