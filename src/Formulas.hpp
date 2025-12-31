#pragma once

// Core Formulas (TODO TODO TODO)
inline constexpr float nextLevelFormula(int level) { return level * 125; }
inline constexpr float expDropFormula(int level) { return level * 600; }
inline constexpr float expDropBossFormula(int level) { return level * 103.7; }

// Warrior
inline constexpr float warriorHp(int level) { return 250 + level * 8; }
inline constexpr float warriorResource(int level) { return 50 + level * 8; }
inline constexpr float warriorAtk(int level) { return 15 + level * 4; }
inline constexpr float warriorDef(int level) { return 7 + level * 3; }
inline constexpr float warriorMagic(int) { return 0; } // warrior can't use magic
inline constexpr float warriorResistance(int level) { return 5 + level * 2; }

// Mage
inline constexpr float mageHp(int level) { return 180 + level * 6; }
inline constexpr float mageResource(int level) { return 60 + level * 9; }
inline constexpr float mageAtk(int level) { return 9 + level * 3; }
inline constexpr float mageDef(int level) { return 5 + level * 2; }
inline constexpr float mageMagic(int level) { return 17 + level * 4; }
inline constexpr float mageResistance(int level) { return 7 + level * 3; }

// Archer
inline constexpr float archerHp(int level) { return 200 + level * 7; }
inline constexpr float archerResource(int level) { return 60 + level * 9; }
inline constexpr float archerAtk(int level) { return 13 + level * 3; }
inline constexpr float archerDef(int level) { return 7 + level * 3; }
inline constexpr float archerMagic(int) { return 0; } // archer can't use magic
inline constexpr float archerResistance(int level) { return 5 + level * 2; }

// Healer
inline constexpr float healerHp(int level) { return 170 + level * 5; }
inline constexpr float healerResource(int level) { return 60 + level * 9; }
inline constexpr float healerAtk(int level) { return 7 + level * 2; }
inline constexpr float healerDef(int level) { return 5 + level * 2; } 
inline constexpr float healerMagic(int level) { return 17 + level * 4; }
inline constexpr float healerResistance(int level) { return 9 + level * 4; }

// Enemy
inline constexpr float enemyHp(int level) { return 250 + level * 5; }
inline constexpr float enemyResource(int level) { return 45 + level * 5; }
inline constexpr float enemyAtk(int level) { return 15 + level * 3; }
inline constexpr float enemyDef(int level) { return 7 + level * 2; }
inline constexpr float enemyMagic(int) { return 0; } // normal enemy can't use magic
inline constexpr float enemyResistance(int level) { return 5 + level * 2; }

// Boss
inline constexpr float bossHp(int level) { return 500 + level * 8; }
inline constexpr float bossResource(int level) { return 50 + level * 8; }
inline constexpr float bossAtk(int level) { return 17 + level * 4; }
inline constexpr float bossDef(int level) { return 7 + level * 3; }
inline constexpr float bossMagic(int level) { return 17 + level * 4; }
inline constexpr float bossResistance(int level) { return 7 + level * 3; }

inline constexpr float resourceRegenerationStat(int level) { return (level*0.2f) + level; }