#include "Combat.h"
#include "../menu/Menu.h"
#include <cstdlib>
#include <queue>
#include <stack>
#include <algorithm>
#include <utility>
#include "../Terminal.h"


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
    std::cout << ((playerParty.getIsAlive()) ? terminal::foreground(terminal::brightGreen) : terminal::foreground(terminal::brightRed)) << "====================================" << std::endl;
    std::cout << "BATTLE HAS ENDED!" << std::endl;
    std::cout << "WINNERS: ";
    for (size_t i = 0; i < winners->getPartySize(); i++) { std::cout << (*winners)[i]->getName() << " | "; } 
    std::cout << std::endl;
    std::cout << "====================================" << std::endl << std::endl << terminal::reset;

    // TODO - Print XP, LVL, etc. 

}

void Combat::battleStart() const {
    std::cout << "====================================" << std::endl;
    std::cout << "BATTLE HAS BEGUN!" << std::endl;
    // Print Player Party
    for (size_t i = 0; i < playerParty.getPartySize(); i++) { std::cout << playerParty[i]->getName() << " "; } 
    std::cout << std::endl;
    std::cout << "VS\n";
    // Print Enemy Party
    for (size_t i = 0; i < enemyParty.getPartySize(); i++) { std::cout << enemyParty[i]->getName() << " "; } 
    std::cout << std::endl << "====================================" << std::endl << std::endl;
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
    const std::vector<Skill*>& skillList = source->getSkills();
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

    for(size_t i = 0; i < playerParty.getPartySize(); i++) {
        if(playerParty[i]->getDef() > playerParty[i]->getMaxDef()) {
            playerParty[i]->setDefense(playerParty[i]->getMaxDef());
        }

        if(playerParty[i]->getAtk() > playerParty[i]->getMaxAtk()) {
            playerParty[i]->setAttack(playerParty[i]->getMaxAtk());
        }

        if(playerParty[i]->getMagic() > playerParty[i]->getMaxMagic()) {
            playerParty[i]->setMagic(playerParty[i]->getMaxMagic());
        }

        if(playerParty[i]->getResistance() > playerParty[i]->getMaxResistance()) {
            playerParty[i]->setResistance(playerParty[i]->getMaxResistance());
        }

        // resource regen
        playerParty[i]->setResource(playerParty[i]->getResource() + (0.5 * playerParty[i]->getMaxResource()));
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

    for(size_t i = 0; i < enemyParty.getPartySize(); i++) {
        if(enemyParty[i]->getDef() > enemyParty[i]->getMaxDef()) {
            enemyParty[i]->setDefense(enemyParty[i]->getMaxDef());
        }

        if(enemyParty[i]->getAtk() > enemyParty[i]->getMaxAtk()) {
            enemyParty[i]->setAttack(enemyParty[i]->getMaxAtk());
        }

        if(enemyParty[i]->getMagic() > enemyParty[i]->getMaxMagic()) {
            enemyParty[i]->setMagic(enemyParty[i]->getMaxMagic());
        }

        if(enemyParty[i]->getResistance() > enemyParty[i]->getMaxResistance()) {
            enemyParty[i]->setResistance(enemyParty[i]->getMaxResistance());
        }

        enemyParty[i]->setResource(enemyParty[i]->getResource() + (0.5 * enemyParty[i]->getMaxResource()));
    }

    // get choice from each player party member
    for(size_t i = 0; i < enemyParty.getPartySize(); i++) {
        if (!enemyParty[i]->getIsAlive()) { continue; }

        Skill* skill = getEnemySkill(enemyParty[i]);
        Character* target = getEnemyTarget(enemyParty[i], skill);
        if (target != nullptr) {
            actionDeque.push_back(Action(enemyParty[i], target, skill));
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

        terminal::foreground(terminal::brightGreen);
        endInfo(winner);
        return false;
    }
    else { 
        winner = &enemyParty; 
        loser = &playerParty; 
        endInfo(winner);
        return true;
    }
}
