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

    size_t getFirstPartyIndex();
    size_t getLastPartyIndex();

    void createMainMenu();
    
    // TODO - later
    void createPartyMemberNameMenu();
    void createPartyMemberClassMenu();

    void createFightMenu();
    void createSelectSkillMenu();
    void createSelectTargetMenu();

    void run();

    void printTopStack() const;

    void clearConsole() const;
};