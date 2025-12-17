#include "Combat.h"
#include "../menu/Menu.h"
#include <cstdlib>
#include <queue>
#include <stack>
#include <algorithm>
#include <utility>


// constructor
Combat::Combat()
    : turnCount(1), source(nullptr), target(nullptr), skill(nullptr), winner(nullptr), loser(nullptr) {}

Combat::Combat(Party player, Party enemy)
    : playerParty(std::move(player)), enemyParty(std::move(enemy)), turnCount(1), source(nullptr), target(nullptr), skill(nullptr), winner(nullptr), loser(nullptr) {}

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

void Combat::getValidTargets(const Party& sourceParty, const Party& opposingParty, Character* actingCharacter, Skill* actingSkill) {
    validTargets.clear();

    // bail out early if there is no acting skill; prevents dereferencing garbage
    if (actingSkill == nullptr) { return; }
    
    switch (actingSkill->getTargetType()) {
        case TargetType::SELF:
            validTargets.emplace_back(actingCharacter);
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

    validTargets.erase(
        std::remove_if(validTargets.begin(), validTargets.end(),
            [](Character* c) { return c == nullptr || !c->getIsAlive(); }),
        validTargets.end());
}

Character* Combat::getEnemyTarget(Character* actingSource, Skill* actingSkill) {
    getValidTargets(enemyParty, playerParty, actingSource, actingSkill);

    if (validTargets.empty()) { return nullptr; }

    // TODO - Make more sophisticated
    size_t choice = static_cast<size_t>(rand() % validTargets.size());
    return validTargets[choice];
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
    while(!actionDeque.empty()) {
        performAction(
            actionDeque.front().source,
            actionDeque.front().target,
            actionDeque.front().skill
        );
        actionDeque.pop_front();
    }

    // TODO - reset or decrement status effect for enemy party

    // get choice from each player party member
    for (size_t i = 0; i < enemyParty.getPartySize(); i++) {
        if (!enemyParty[i]->getIsAlive()) { continue; }

        Skill* skill = getEnemySkill(enemyParty[i]);
        Character* target = getEnemyTarget(enemyParty[i], skill);
        if (target != nullptr) {
            actionDeque.push_front(Action(enemyParty[i], target, skill));
        }
    }

    // perform actions
    while(!actionDeque.empty()) {
        performAction(
            actionDeque.front().source,
            actionDeque.front().target,
            actionDeque.front().skill
        );
        actionDeque.pop_front();
    }
}

bool Combat::endBattle() {

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
