#pragma once

#include "../game/GameData.h"
#include "Menu.h"
#include <stack>

class MenuManager {
  private:
	std::stack<Menu> menuStack;
	GameData* gameData;

  public:
	MenuManager(GameData* gm);

	void nextMenu(const Menu& menu);
	void prevMenu();

	bool nextPartyMember();
	bool prevPartyMember();

	size_t getFirstPartyIndex();
	size_t getLastPartyIndex();

	void createMainMenu();

	void createFightMenu();
	void createSelectSkillMenu();
	void createSelectTargetMenu();

	void run();

	void printTopStack() const;
};
