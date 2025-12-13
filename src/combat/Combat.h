#ifndef COMBAT_H
#define COMBAT_H

#include "../character/Character.h"
#include "../party/Party.h"
#include "Action.h"
#include "../menu/MenuManager.h"
#include <iostream>

struct Combat {
    Party playerParty;
    Party enemyParty;
    vector<Character*> validTargets;
    int turnCount;
    queue<Action> actionQueue;
    Character* source;
    Character* target;
    Skill* skill;
    MenuState currentMenuState;

    Combat(Party player, Party enemy);

    void printTurn() const;
    void endInfo(Party *winner) const;
    void battleStart() const;

    void getValidTargets(Party sourceParty, Party opposingParty);

    Character* getPlayerTarget();
    void getPlayerSkill();

    Character* getEnemyTarget(Character* source, Skill* skill);
    Skill* getEnemySkill(Character* source);

    void fightMenu();

    void performAction(Character* source,Character* target,Skill* skill);

    void processTurn();

    bool combatLoop();
};

#endif