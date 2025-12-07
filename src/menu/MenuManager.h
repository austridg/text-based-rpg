#pragma once

#include <stack>
#include "Menu.h"

class MenuManager {
private:
    std::stack<Menu> menuStack;
public:
    MenuManager();

    void nextMenu(const Menu &menu);
    void prevMenu();

    Menu createMainMenu();
    Menu createFightMenu();
};