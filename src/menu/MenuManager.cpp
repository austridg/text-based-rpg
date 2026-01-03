#include "MenuManager.h"
#include <cstdlib>

MenuManager::MenuManager(GameData *gm)
:   gameData(gm) {}

void MenuManager::createMainMenu() {
    menuStack.emplace("Choose an Option:",std::vector<Command>{
        {"Fight",[this]() { 
            gameData->currentBattle = Combat(gameData->playerParty,gameData->arena[gameData->arenaIndex]);
            gameData->state = GameState::BATTLE;

            gameData->currentBattle.battleStart();
            
            terminal::clearConsole();
            gameData->currentBattle.printTurn();
            createFightMenu();
        }},
        {"Print Party Stats",[this]() { terminal::clearConsole(); gameData->playerParty.printPartyInfo(); }},
        {"Quit",[this]() { exit(0); }}
    });
}

void MenuManager::createFightMenu() {
    menuStack.emplace(
        "Choose an Option:",
        std::vector<Command>{
        {"Fight",[this]() { 
            terminal::clearConsole();
            createSelectSkillMenu();
        }},
        {"Print Battle Info",[this]() { 
            terminal::clearConsole();
            std::cout << "===== Player Party =====\n";
            gameData->playerParty.printPartyInfo();
            std::cout << "\n" << "===== Enemy Party =====\n";
            gameData->arena[gameData->arenaIndex].printPartyInfo();
        }}
    });
}

void MenuManager::createSelectSkillMenu() {
    // skill menu options (temporary var)
    std::vector<Command> skillMenuOptions;

    // looping over SkillListSize and adding each skill as a command in the skillMenuOptions vector
    for(size_t i = 0; i < gameData->playerParty[gameData->partyIndex]->getSkillListSize(); i++) {

        skillMenuOptions.emplace_back(Command{
            terminal::foreground(gameData->playerParty[gameData->partyIndex]->getSkills()[i]->getSkillColor()) + gameData->playerParty[gameData->partyIndex]->getSkills()[i]->getName() + terminal::foreground(terminal::white),
            [this,i]() { 
        
                // check if character can use skill
                if (!gameData->playerParty[gameData->partyIndex]->getSkills()[i]->canUse(gameData->playerParty[gameData->partyIndex])) {
                    terminal::clearConsole();
                    std::cout << terminal::foreground(terminal::red) << "Not enough " << ((gameData->playerParty[gameData->partyIndex]->getIsMagic()) ? "mana.\n" : "stamina.\n") << terminal::reset;
                }
                else {
                    auto pickedSkill = gameData->playerParty[gameData->partyIndex]->getSkills()[i];
                    if(pickedSkill != nullptr) { gameData->currentBattle.skill = pickedSkill; }
                    gameData->currentBattle.source = gameData->playerParty[gameData->partyIndex];
                    terminal::clearConsole();
                    createSelectTargetMenu();
                }
            }
        });
    }

    // back command - only added if not the first party member
    if(gameData->partyIndex != getFirstPartyIndex()) {
        skillMenuOptions.emplace_back(Command{
            terminal::foreground(terminal::yellow) + "[BACK]" + terminal::foreground(terminal::white),
            [this]() {
                prevPartyMember();
                terminal::clearConsole();
                createSelectSkillMenu();
                gameData->currentBattle.actionDeque.pop_back();
            }
        });
    }

    skillMenuOptions.emplace_back(Command{
        terminal::foreground(terminal::red) + "[CANCEL]" + terminal::foreground(terminal::white),
        [this]() {
                gameData->partyIndex = getFirstPartyIndex();
                menuStack.pop();
                menuStack.pop();
                terminal::clearConsole();
                gameData->currentBattle.printTurn();
                createFightMenu();
        }
    });

    // creating and adding menu to menuStack
    menuStack.emplace(
        gameData->currentBattle.playerParty[gameData->partyIndex]->getName() + "'s Turn:\n" + "Choose a Move:",
        skillMenuOptions
    );
}

void MenuManager::createSelectTargetMenu() {
    // target menu options (temporary var)
    std::vector<Command> targetMenuOptions;
    
    // get valid targets for current party member
    gameData->currentBattle.getValidTargets(
        gameData->currentBattle.playerParty,
        gameData->currentBattle.enemyParty,
        gameData->currentBattle.playerParty[gameData->partyIndex],
        gameData->currentBattle.skill
    );

    // add action to deque if target type is "ALL_ENEMIES"
    if(gameData->currentBattle.skill->getTargetType() == TargetType::ALL_ENEMIES || gameData->currentBattle.skill->getTargetType() == TargetType::ALL_ALLIES) {
        std::string targetMessage;

        for(size_t i = 0; i < gameData->currentBattle.validTargets.size(); i++) {
            targetMessage += terminal::foreground(gameData->currentBattle.validTargets[i]->getHealthColor()) + gameData->currentBattle.validTargets[i]->getName() + terminal::foreground(terminal::white);
            if(!((i + 1) == gameData->currentBattle.validTargets.size())) { targetMessage += ", "; }
        }

        targetMenuOptions.emplace_back(Command{
            targetMessage,
            [this]() {
                for(size_t i = 0; i < gameData->currentBattle.validTargets.size(); i++) {
                    gameData->currentBattle.target = gameData->currentBattle.validTargets[i];

                    gameData->currentBattle.actionDeque.push_back(Action(
                        gameData->currentBattle.source,
                        gameData->currentBattle.target,
                        gameData->currentBattle.skill
                    ));
                }

                // if false, there's no more party members, so invoke processTurn()
                if(!nextPartyMember()) {
                    terminal::clearConsole();
                    gameData->currentBattle.processTurn();
                    // if battle is over then end battle
                    if(!(gameData->currentBattle.playerParty.getIsAlive()) || !(gameData->currentBattle.enemyParty.getIsAlive())) {
                        gameData->endGame = gameData->currentBattle.endBattle();
                        gameData->playerParty.healParty();
                        gameData->partyIndex = getFirstPartyIndex();
                        gameData->arenaIndex++;
                        menuStack.pop();
                        menuStack.pop();
                        menuStack.pop();
                        return;
                    }
                                        
                    gameData->partyIndex = getFirstPartyIndex();
                    menuStack.pop();
                    menuStack.pop();
                    gameData->currentBattle.printTurn();
                }
                else {
                    menuStack.pop();
                    menuStack.pop();
                    terminal::clearConsole();
                    createSelectSkillMenu();
                }
            }
        });
    }
    else {
        // loop over valid targets and add them to targetMenuOptions
        for(size_t i = 0; i < gameData->currentBattle.validTargets.size(); i++) {
            targetMenuOptions.emplace_back(Command{
            terminal::foreground(gameData->currentBattle.validTargets[i]->getHealthColor()) + gameData->currentBattle.validTargets[i]->getName() + terminal::foreground(terminal::white),
                [this,i]() {
                    gameData->currentBattle.target = gameData->currentBattle.validTargets[i];

                    gameData->currentBattle.actionDeque.push_back(Action(
                        gameData->currentBattle.source,
                        gameData->currentBattle.target,
                        gameData->currentBattle.skill
                    ));

                    // if false, there's no more party members, so invoke processTurn()
                    if(!nextPartyMember()) {
                        terminal::clearConsole();
                        gameData->currentBattle.processTurn();
                        // if battle is over then end battle
                        if(!(gameData->currentBattle.playerParty.getIsAlive()) || !(gameData->currentBattle.enemyParty.getIsAlive())) {
                            gameData->endGame = gameData->currentBattle.endBattle();
                            gameData->playerParty.healParty();
                            gameData->partyIndex = getFirstPartyIndex();
                            gameData->arenaIndex++;
                            menuStack.pop();
                            menuStack.pop();
                            menuStack.pop();
                            return;
                        }
                                        
                        gameData->partyIndex = getFirstPartyIndex();
                        menuStack.pop();
                        menuStack.pop();
                        gameData->currentBattle.printTurn();
                    }
                    else {
                        menuStack.pop();
                        menuStack.pop();
                        terminal::clearConsole();
                        createSelectSkillMenu();
                    }
                }
            });
        }

    }

    

    // back command
    targetMenuOptions.emplace_back(Command{
        terminal::foreground(terminal::yellow) + "[BACK]" + terminal::foreground(terminal::white),
        [this]() { terminal::clearConsole(); menuStack.pop(); }
    });

    targetMenuOptions.emplace_back(Command{
        terminal::foreground(terminal::red) + "[CANCEL]" + terminal::foreground(terminal::white),
        [this]() {
                gameData->partyIndex = getFirstPartyIndex();
                menuStack.pop();
                menuStack.pop();
                terminal::clearConsole();
                gameData->currentBattle.printTurn();
                createFightMenu();
        }
    });

    menuStack.emplace("Choose a Target: ",targetMenuOptions);
}

// ------------------------------------->

size_t MenuManager::getFirstPartyIndex() {
    for(size_t i = 0; i < gameData->playerParty.getPartySize(); i++) {
        if(!gameData->playerParty[i]->getIsAlive()) { continue; }
        return i;
    }

    return -1;
}

size_t MenuManager::getLastPartyIndex() {
    for(size_t i = gameData->playerParty.getPartySize() - 1; i > 0; i--) {
        if(!gameData->playerParty[i]->getIsAlive()) { continue; }
        return i;
    }

    return -1;
}

bool MenuManager::nextPartyMember() {

    for(size_t i = gameData->partyIndex + 1; i < gameData->playerParty.getPartySize(); ++i) {
        if(gameData->playerParty[i]->getIsAlive()) { gameData->partyIndex = i; return true; }
    }

    return false;

}

bool MenuManager::prevPartyMember() {

    if(gameData->partyIndex == 0) { return false; }
    
    for(size_t i = gameData->partyIndex; i > 0; --i) {
        size_t prev = i - 1;
        if(gameData->playerParty[prev]->getIsAlive()) { gameData->partyIndex = prev; return true; }
    }

    return false;

}

// ------------------------------------->

void MenuManager::run() {
    if(!menuStack.empty()) menuStack.top().runMenu();
}

// -----------------  DEBUG FUNCS  -------------------->

void MenuManager::printTopStack() const {
    std::cout << menuStack.top().menuMessage << "\n";
}