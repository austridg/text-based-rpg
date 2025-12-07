#include "MenuManager.h"
#include <cstdlib>

MenuManager::MenuManager() {
}

void MenuManager::createMainMenu(Party &party) {
    menuStack.emplace("Choose an Option:\n",std::vector<Command>{
        {"Fight",[this]() { createFightMenu(); }},
        {"Print Party Stats",[party]() { party.printPartyInfo(); }},
        {"Quit",[this]() { exit(0); }}
    });
}

