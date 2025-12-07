#include "MenuManager.h"

MenuManager::MenuManager() {
    Menu mainMenu("Choose an Option",std::vector<Command>{
        {"Fight",[this]() { nextMenu(createFightMenu()); }},
        {"Print Party Stats",[]() { }},
        {"Quit",[]() { }}
    });

    menuStack.push(mainMenu);
}

Menu MenuManager::createMainMenu() {
    Menu mainMenu("Choose an Option",std::vector<Command>{
        {"Fight",[this]() { nextMenu(createFightMenu()); }},
        {"Print Party Stats",[]() {  }},
        {"Quit",[]() { }}
    });
}