#ifndef COMBAT_H
#define COMBAT_H

#include "../character/Character.h"
#include "../party/Party.h"
#include "Action.h"
#include <iostream>
#include <queue>

struct Combat {
    Party playerParty;
    Party enemyParty;
    vector<Character*> validTargets;
    int turnCount;
    int menuIndex;
    queue<Action> actionQueue;

    Combat(Party player, Party enemy);

    void printTurn() const;
    void endInfo(Party *winner) const;
    void battleStart() const;

    void getValidTargets(Character* source, Skill* skill, Party sourceParty, Party opposingParty);

    Character* getPlayerTarget(size_t choice);
    Skill* getPlayerSkill(Character* source,size_t choice);

    Character* getEnemyTarget(Character* source, Skill* skill);
    Skill* getEnemySkill(Character* source);

    void performAction(Character* source,Character* target,Skill* skill);

    void processTurn();

    int battleMenu();

    size_t skillMenu(Character* source);
    size_t targetMenu(Character* source,Skill* skill);

    bool combatLoop();
};

#endif