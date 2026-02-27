#ifndef COMBAT_H
#define COMBAT_H

#include "../character/Character.h"
#include "../party/Party.h"
#include "Action.h"
#include <deque>
#include <iostream>

struct Combat {
	Party playerParty;
	Party enemyParty;
	std::vector<Character*> validTargets;
	int turnCount{1};
	std::deque<Action> actionDeque;
	Character* source{};
	Character* target{};
	Skill* skill{};
	Party* winner{};
	Party* loser{};

	Combat();
	Combat(Party player, Party enemy);

	void printTurn() const;
	void endInfo(Party* winner) const;
	void battleStart() const;

	void getValidTargets(const Party& sourceParty, const Party& opposingParty,
						 Character* actingCharacter, Skill* actingSkill);

	Character* getEnemyTarget(Character* actingSource, Skill* actingSkill);
	Skill* getEnemySkill(Character* source);

	void performAction(Character* source, Character* target, Skill* skill);

	void processTurn();

	bool endBattle();
};

#endif
