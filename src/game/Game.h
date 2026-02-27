#ifndef GAME_H
#define GAME_H

#include "../Random.h"
#include "../Terminal.h"
#include "../character/Character.h"
#include "../character_classes/Archer.h"
#include "../character_classes/Boss.h"
#include "../character_classes/Healer.h"
#include "../character_classes/Mage.h"
#include "../character_classes/Warrior.h"
#include "../combat/Combat.h"
#include "../menu/Menu.h"
#include "../menu/MenuManager.h"
#include "../party/Party.h"
#include "GameData.h"
#include "../Terminal.h"
#include "../Random.h"

class Game {
  private:
	GameData gameData;
	MenuManager manager;
	std::array<std::string, 20> possibleNames{
		"Alex",	 "Ryan",   "Austin", "Erik",  "Plankton", "Nightowl", "Sean",
		"Lyra",	 "Morgan", "Harry",	 "Apple", "Jerry",	  "Julia",	  "William",
		"Sarah", "Ava",	   "Kevin",	 "Mark",  "Olivia",	  "Bob"};

  public:
	Game();
	~Game();

	std::vector<Character*> createEnemyParty(int level);

	void createPlayerParty();

	void gameLoop();

	const std::string& generateName();

	void clearConsole() const;
};

#endif
