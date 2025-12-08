#include "MenuManager.h"
#include <cstdlib>

MenuManager::MenuManager() {
}

void MenuManager::createMainMenu(Party &party) {
    menuStack.emplace("Choose an Option:\n",std::vector<Command>{
        {"Fight",[this]() { createFightMenu(); }}, // TODO - fix
        {"Print Party Stats",[party]() { party.printPartyInfo(); }},
        {"Quit",[this]() { exit(0); }}
    });
}

void MenuManager::createFightMenu(Party &playerParty,Party &enemyParty) {
    menuStack.emplace("Choose an Option:\n",std::vector<Command>{
        {"Fight",[this]() { createSelectSkillMenu(); }},
        {"Print Battle Info",[playerParty,enemyParty]() { 
            cout << "==== Player Party =====\n";
            playerParty.printPartyInfo();
            cout << endl << "==== Enemy Party =====\n";
            enemyParty.printPartyInfo();
        }}
    });
}