#pragma once

#include <stack>
#include "Menu.h"
#include "../game/GameData.h"

class MenuManager {
private:
    std::stack<Menu> menuStack;
    GameData *gameData;
public:
    MenuManager(GameData *gm);

    void nextMenu(const Menu &menu);
    void prevMenu();

    bool nextPartyMember();
    bool prevPartyMember();

    int getFirstPartyIndex();
    int getLastPartyIndex();

    void createMainMenu();

    void createFightMenu();
    void createSelectSkillMenu();
    void createSelectTargetMenu();

    void run();
};