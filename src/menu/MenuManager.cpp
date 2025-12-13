#include "MenuManager.h"
#include <cstdlib>

MenuManager::MenuManager(GameData *gm)
:   gameData(gm) {}

void MenuManager::createMainMenu() {
    menuStack.emplace("Choose an Option:\n",std::vector<Command>{
        {"Fight",[this]() { createFightMenu(); }}, // TODO - fix
        {"Print Party Stats",[this]() { gameData->playerParty.printPartyInfo(); }},
        {"Quit",[this]() { exit(0); }}
    });
}

void MenuManager::createFightMenu() {
    menuStack.emplace("Choose an Option:\n",std::vector<Command>{
        {"Fight",[this]() { 
            gameData->currentBattle = Combat(gameData->playerParty,gameData->arena[gameData->arenaIndex]);
            gameData->currentBattle.combatLoop();
        }},
        {"Print Battle Info",[this]() { 
            cout << "==== Player Party =====\n";
            gameData->playerParty.printPartyInfo();
            cout << endl << "==== Enemy Party =====\n";
            gameData->arena[gameData->arenaIndex].printPartyInfo();
        }}
    });
}

void MenuManager::createSelectSkillMenu() {
    // skill menu options (temporary var)
    std::vector<Command> skillMenuOptions;

    // looping over SkillListSize and adding each skill as a command in the skillMenuOptions vector
    for(int i = 0; i < gameData->playerParty[gameData->partyIndex]->getSkillListSize(); i++) {

        skillMenuOptions.emplace_back(Command{
            gameData->playerParty[gameData->partyIndex]->getSkills()[i]->getName(),
            [this,i]() { 
                auto pickedSkill = gameData->playerParty[gameData->partyIndex]->getSkills()[i];
                if(pickedSkill != nullptr) { gameData->currentBattle.skill = pickedSkill; }
                gameData->currentBattle.source = gameData->playerParty[gameData->partyIndex];
                createSelectTargetMenu();
            }
        });
    }

    // back command - only added if not the first party member
    if(gameData->partyIndex != getFirstPartyIndex()) {
        skillMenuOptions.emplace_back(Command{
            "[BACK]",
            [this]() {
                prevPartyMember();
                createSelectSkillMenu();
            }
        });
    }
    
    // creating and adding menu to menuStack
    menuStack.emplace("Choose a Move: ",skillMenuOptions);
}

void MenuManager::createSelectTargetMenu() {
    // target menu options (temporary var)
    std::vector<Command> targetMenuOptions;

    // get valid targets for current party member
    gameData->currentBattle.getValidTargets(gameData->currentBattle.playerParty,gameData->currentBattle.enemyParty);

    // loop over valid targets and add them to targetMenuOptions
    for(int i = 0; i < gameData->currentBattle.validTargets.size(); i++) {
        targetMenuOptions.emplace_back(Command{
            gameData->currentBattle.validTargets[i]->getName(),
            [this,i]() {
                gameData->currentBattle.target = gameData->currentBattle.validTargets[i];
                gameData->currentBattle.actionQueue.push(Action(
                    gameData->currentBattle.source,
                    gameData->currentBattle.target,
                    gameData->currentBattle.skill
                ));

                // if false, there's no more party members, so invoke processTurn()
                if(!nextPartyMember()) { gameData->currentBattle.processTurn(); }

                menuStack.pop();
            }
        });
    }

    // back command
    targetMenuOptions.emplace_back(Command{
        "[BACK]",
        [this]() { menuStack.pop(); }
    });

    menuStack.emplace("Choose a Target: ",targetMenuOptions);
}

// TODO - Add checks for party index - no dead members allowed to pick skill
// TODO - Finish createSelectTargetMenu()

// ------------------------------------->

int MenuManager::getFirstPartyIndex() {
    for(int i = 0; i < gameData->playerParty.getPartySize(); i++) {
        if(!gameData->playerParty[i]->getIsAlive()) { continue; }
        return i;
    }
}

int MenuManager::getLastPartyIndex() {
    for(int i = gameData->playerParty.getPartySize() - 1; i >= 0; i--) {
        if(!gameData->playerParty[i]->getIsAlive()) { continue; }
        return i;
    }
}

bool MenuManager::nextPartyMember() {
    int currentPartyIndex = gameData->partyIndex;
    bool validPartyIndex{};

    for(currentPartyIndex; !validPartyIndex; currentPartyIndex++) {
        if(gameData->playerParty.getPartySize() == currentPartyIndex + 1) { break; }
        if(!gameData->playerParty[currentPartyIndex + 1]->getIsAlive()) { continue; }

        gameData->partyIndex++;
        validPartyIndex = true;
    }

    return validPartyIndex;

}

bool MenuManager::prevPartyMember() {
    int currentPartyIndex = gameData->partyIndex;
    bool validPartyIndex{};

    for(currentPartyIndex; !validPartyIndex; currentPartyIndex++) {
        if(gameData->playerParty.getPartySize() == currentPartyIndex - 1) { break; }
        if(!gameData->playerParty[currentPartyIndex - 1]->getIsAlive()) { continue; }

        gameData->partyIndex--;
        validPartyIndex = true;
    }

    return validPartyIndex;
}

// ------------------------------------->

void MenuManager::run() {
    while(!menuStack.empty()) menuStack.top().runMenu();
}