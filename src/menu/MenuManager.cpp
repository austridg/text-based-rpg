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
        {"Fight",[this]() { createSelectSkillMenu(); }},
        {"Print Battle Info",[this]() { 
            cout << "==== Player Party =====\n";
            gameData->playerParty.printPartyInfo();
            cout << endl << "==== Enemy Party =====\n";
            gameData->arena[gameData->currentIndex].printPartyInfo();
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
    if(gameData->partyIndex != 0) {
        skillMenuOptions.emplace_back(Command{
            "[BACK]",
            [this]() { 
                gameData->partyIndex--;
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

                if(gameData->partyIndex == gameData->)
                gameData->partyIndex++;
                menuStack.pop();
            }
        });
    }

    // back command
    targetMenuOptions.emplace_back(Command{
        "[BACK]",
        [this]() { menuStack.pop(); }
    });
}

// TODO - Add checks for party index - no dead members allowed to pick skill
// TODO - Finish createSelectTargetMenu()