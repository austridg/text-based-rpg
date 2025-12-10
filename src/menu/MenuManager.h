#pragma once

#include <stack>
#include "Menu.h"
#include "../combat/Combat.h"
#include "../game/GameData.h"

class MenuManager {
private:
    std::stack<Menu> menuStack;
    GameData *gameData;
public:
    MenuManager(GameData *gm);

    void nextMenu(const Menu &menu);
    void prevMenu();

    void createMainMenu();
    void createFightMenu();
    void createSelectSkillMenu();
    void createSelectTargetMenu();
};