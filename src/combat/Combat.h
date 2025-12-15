#ifndef COMBAT_H
#define COMBAT_H

#include "../character/Character.h"
#include "../party/Party.h"
#include "Action.h"
#include <iostream>
#include <deque>

struct Combat {
    Party playerParty;
    Party enemyParty;
    vector<Character*> validTargets;
    int turnCount;
    deque<Action> actionDeque;
    Character* source;
    Character* target;
    Skill* skill;
    Party* winner;
    Party* loser;

    Combat() = default;
    Combat(Party player, Party enemy);

    void printTurn() const;
    void endInfo(Party *winner) const;
    void battleStart() const;

    void getValidTargets(Party sourceParty, Party opposingParty);

    Character* getEnemyTarget();
    Skill* getEnemySkill(Character* source);

    void performAction(Character* source,Character* target,Skill* skill);

    void processTurn();

    bool endBattle();
};

#endif