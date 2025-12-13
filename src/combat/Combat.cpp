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

Character* Combat::getEnemyTarget(Character* source, Skill* skill) {
    getValidTargets(enemyParty,playerParty);

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