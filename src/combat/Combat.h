#ifndef COMBAT_H
#define COMBAT_H

#include "../character/Character.h"
#include "../party/Party.h"
#include "Action.h"
#include <iostream>

struct Combat {
    Party playerParty;
    Party enemyParty;
    vector<Character*> validTargets;
    int turnCount;
    MenuState currentMenuState;

    Combat(Party player, Party enemy);

    void printTurn() const;
    void endInfo(Party *winner) const;
    void battleStart() const;

    void getValidTargets(Character* source, Skill* skill, Party sourceParty, Party opposingParty);

    Character* getPlayerTarget(Character* source, Skill* skill);
    Skill* getPlayerSkill(Character* source);

    Character* getEnemyTarget(Character* source, Skill* skill);
    Skill* getEnemySkill(Character* source);

    void fightMenu();

    void performAction(Character* source,Character* target,Skill* skill);

    void processTurn(Party player, Party enemy);

    bool combatLoop();
};

#endif