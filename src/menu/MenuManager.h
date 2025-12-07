#pragma once

#include <stack>
#include "Menu.h"
#include "../Party/Party.h"

class MenuManager {
private:
    std::stack<Menu> menuStack;
public:
    MenuManager();

    void nextMenu(const Menu &menu);
    void prevMenu();

    void createMainMenu(Party &party);
    void createFightMenu();
    void createSelectSkillMenu();
    void createSelectTargetMenu();
};