#include "Combat.h"
#include "../menu/Menu.h"
#include <cstdlib>
#include <queue>
#include <stack>


// constructor
Combat::Combat(Party player, Party enemy)
    : playerParty(player), enemyParty(enemy), turnCount(1), currentMenuState(MenuState::FIGHT_MENU) {}

// print info
void Combat::printTurn() const {
    std::cout << "===== Turn: " << turnCount << " =====\n";
}

void Combat::endInfo(Party *winners) const {
    // std::cout << losers->getName() << " HAS FALLEN!" << endl;
    std::cout << "====================================" << endl;
    std::cout << "BATTLE HAS ENDED!" << endl;
    std::cout << "WINNERS: ";
    for (size_t i = 0; i < winners->getPartySize(); i++) { std::cout << (*winners)[i]->getName() << " | "; } 
    std::cout << endl;
    std::cout << "====================================" << endl << endl;

    // TODO - Print XP, LVL, etc. 

}

void Combat::battleStart() const {
    std::cout << "====================================" << endl;
    std::cout << "BATTLE HAS BEGUN!" << endl;
    // Print Player Party
    for (size_t i = 0; i < playerParty.getPartySize(); i++) { std::cout << playerParty[i]->getName() << " "; } 
    std::cout << endl;
    std::cout << "VS\n";
    // Print Enemy Party
    for (size_t i = 0; i < enemyParty.getPartySize(); i++) { std::cout << enemyParty[i]->getName() << " "; } 
    std::cout << endl << "====================================" << endl << endl;
}

void Combat::getValidTargets(Party sourceParty, Party opposingParty) {
    validTargets.clear();
    
    switch (skill->getTargetType()) {
        case TargetType::SELF:
            validTargets.emplace_back(source);
            break;
        case TargetType::ONE_ALLY:
        case TargetType::ALL_ALLIES:
            validTargets = sourceParty.getParty();
            break;
        case TargetType::ONE_ENEMY:
        case TargetType::ALL_ENEMIES:
            validTargets = opposingParty.getParty();
            break;
    }

    for (auto it = validTargets.begin(); it != validTargets.end(); ) {
        if (!(*it)->getIsAlive()) { it = validTargets.erase(it); }
        else { it++; }
    }
}

Character* Combat::getPlayerTarget() {
    getValidTargets(source, skill,playerParty,enemyParty);

    while(true) {
        std::cout << "Choose your target: " << endl;
        for (size_t i = 0; i < validTargets.size(); i++) {
            std::cout << i+1 << ") " << validTargets[i]->getName()
                << " | HP: " << validTargets[i]->getHp() << " / " << validTargets[i]->getMaxHp() << endl;
        }
        std::cout << ">";

        size_t choice;
        cin >> choice;

        if(choice > 0 && choice <= validTargets.size()) {
            return validTargets[choice - 1];
        }
        else { std::cout << "Invalid Option.\n"; }
    }
}

// player turn
void Combat::getPlayerSkill() {
    // temp variable for vector or skills
    const vector<Skill*>& skillList = source->getSkills();
    Skill* pickedSkill;

    // prompt for player's choice
    while(true) {
        // print player's turn
        std::cout << source->getName() << "'s Turn:\n";

        // print out useable skills
        source->printSkills();

        std::cout << ">";

        // get player choice
        size_t choice;
        cin >> choice;

        if (choice > 0 && choice <= skillList.size()) { // valid choice | return picked skill
            pickedSkill = skillList[choice - 1]; // offset by 1

            if(pickedSkill->canUse(source)) return pickedSkill;
            else { pickedSkill->cantUse(source); }
        }
        else { std::cout << "Invalid Option.\n"; }
    }
}

Character* Combat::getEnemyTarget(Character* source, Skill* skill) {
    getValidTargets(source,skill,enemyParty,playerParty);

    // TODO - Make more sophisticated
    while(true) {
        size_t choice = (rand() % 100) * validTargets.size() / 100; // generate choice randomly
        return validTargets[choice];
    }
}

// enemy turn
Skill* Combat::getEnemySkill(Character* source) {
    const vector<Skill*>& skillList = source->getSkills();
    Skill* pickedSkill;

    // TODO - Make better (more sophisticated)
    while(true) {
        int choice = (rand() % 100) * skillList.size() / 100; // generate choice randomly
        pickedSkill = skillList[choice];
        if(pickedSkill->canUse(source)) return pickedSkill;
    }
}

void Combat::performAction(Character* source, Character* target, Skill* skill) {
    // decrease resource
    source->setResource(source->getResource() - skill->getCost());
    
    // use skill on target
    skill->useSkill(source,target);

    // check if dead
    if(target->getHp() <= 0) { target->setIsAlive(false); std::cout << target->getName() << " has fallen!\n"; }
}

void Combat::processTurn() {

    // TODO - reset or decrement status effect for player party
    
    // perform actions
    while(!actionQueue.empty()) {
        performAction(
            actionQueue.front().source,
            actionQueue.front().target,
            actionQueue.front().skill
        );
        actionQueue.pop();
    }

    // TODO - reset or decrement status effect for enemy party

    // get choice from each player party member
    for (size_t i = 0; i < enemyParty.getPartySize(); i++) {
        if (!enemyParty[i]->getIsAlive()) { continue; }

        Skill* skill = getEnemySkill(enemyParty[i]);
        Character* target = getEnemyTarget(enemyParty[i],skill);
        actionQueue.push(Action(enemyParty[i],target,skill));
    }

    // perform actions
    while(!actionQueue.empty()) {
        performAction(
            actionQueue.front().source,
            actionQueue.front().target,
            actionQueue.front().skill
        );
        actionQueue.pop();
    }

}

// combat loop
bool Combat::combatLoop() {
    Party* winner;
    Party* loser;

    // vector<Command> fightMenuOptions;
    // fightMenuOptions.push_back({"Party Stats",[this]() { playerParty.printPartyInfo(); }});

    // Menu mainMenu("Main Menu",fightMenuOptions);
    // Menu selectSkillMenu("Select Skill",fightMenuOptions);
    // Menu selectTargetMenu("Select Target",fightMenuOptions);
    // mainMenu.runMenu();

    // stack<Menu> menuStack;
    // menuStack.push(mainMenu);

    // menuStack.top().runMenu();
    // menuStack.pop();

    battleStart();

    std::cout << "==== Player Party =====\n";
    playerParty.printPartyInfo();
    std::cout << endl << "==== Enemy Party =====\n";
    enemyParty.printPartyInfo();
    std::cout << endl;

    while(playerParty.getIsAlive() && enemyParty.getIsAlive()) {
        printTurn();

        

        turnCount++;
    }

    if (playerParty.getIsAlive()) { 
        winner = &playerParty; 
        loser = &enemyParty; 

        float expDropped;
        for (size_t i = 0; i < loser->getPartySize(); i++) {
            expDropped += (*loser)[i]->getExpDrop();
        }

        expDropped /= winner->getPartySize();

        for (size_t i = 0; i < winner->getPartySize(); i++) {
            (*winner)[i]->canLevel(expDropped);
        }

        endInfo(winner);
        return true; 
    }
    else { 
        winner = &enemyParty; 
        loser = &playerParty; 
        endInfo(winner);
        return false; 
    }
}