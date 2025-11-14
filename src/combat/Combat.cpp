#include "Combat.h"
#include <cstdlib>
#include <queue>


// constructor
Combat::Combat(Party player, Party enemy)
    : playerParty(player), enemyParty(enemy), turnCount(1) {}

// print info
void Combat::printTurn() const {
    cout << "===== Turn: " << turnCount << " =====\n";
}

void Combat::endInfo(Party *winners,Party *losers) const {
    // cout << losers->getName() << " HAS FALLEN!" << endl;
    cout << "====================================" << endl;
    cout << "BATTLE HAS ENDED!" << endl;
    cout << "WINNERS: ";
    for (int i = 0; i < winners->getPartySize(); i++) { cout << (*winners)[i]->getName() << " | "; } 
    cout << endl;
    cout << "====================================" << endl << endl;

    // TODO - Print XP, LVL, etc. 

}

void Combat::battleStart() const {
    cout << "====================================" << endl;
    cout << "BATTLE HAS BEGUN!" << endl;
    for (int i = 0; i < playerParty.getPartySize(); i++) { cout << playerParty[i]->getName() << " "; } 
    cout << endl;
    cout << "VS";
    for (int i = 0; i < enemyParty.getPartySize(); i++) { cout << enemyParty[i]->getName() << " "; } 
    cout << "====================================" << endl << endl;
}

void Combat::getValidTargets(Character* source, Skill* skill) {
    validTargets.clear();
    
    switch (skill->getTargetType()) {
        case TargetType::SELF:
            validTargets.emplace_back(source);
            break;
        case TargetType::ONE_ALLY:
        case TargetType::ALL_ALLIES:
            validTargets = playerParty.getParty();
            break;
        case TargetType::ONE_ENEMY:
        case TargetType::ALL_ENEMIES:
            validTargets = enemyParty.getParty();
            break;
    }
}

Character* Combat::getPlayerTarget(Character* source, Skill* skill) {
    getValidTargets(source, skill);

    while(true) {
        cout << "Choose your target: " << endl;
        for (int i = 0; i < validTargets.size(); i++) {
            cout << i+1 << ") " << validTargets[i]->getName()
                << " | HP: " << validTargets[i]->getHp() << " / " << validTargets[i]->getMaxHp(); 
        }
        cout << ">";

        int choice;
        cin >> choice;

        if(choice > 0 && choice <= validTargets.size()) {
            return validTargets[choice - 1];
        }
    }
}

// player turn
Skill* Combat::getPlayerSkill(Character* source) {
    // temp variable for vector or skills
    const vector<Skill*>& skillList = source->getSkills();
    Skill* pickedSkill;

    // prompt for player's choice
    while(true) {
        // print player's turn
        cout << source->getName() << "'s Turn:\n";

        // print out useable skills
        source->printSkills();

        // get player choice
        int choice;

        if (choice > 0 && choice <= skillList.size()) { // valid choice | return picked skill
            pickedSkill = skillList[choice - 1]; // offset by 1

            if(pickedSkill->canUse(source)) return pickedSkill;
            else { pickedSkill->cantUse(source); }
        }
        else { cout << "Invalid Option.\n"; }
    }
}

Character* Combat::getEnemyTarget(Character* source, Skill* skill) {
    getValidTargets(source,skill);

    while(true) {
        int choice = (rand() % 100) * validTargets.size() / 100; // generate choice randomly
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
    // check if character can use skill
    skill->canUse(source);

    // decrease resource
    source->setResource(source->getResource() - skill->getCost());
    
    // use skill on target
    skill->useSkill(source,target);
}

void Combat::processTurn(Party player, Party enemy) {
    queue<Action> actionQueue;

    // reset or decrement status effect for player party

    for (int i = 0; i < player.getPartySize(); i++ ) {
        Skill* skill = getPlayerSkill(player[i]);
        Character* target = getPlayerTarget(player[i],skill);
        actionQueue.push(Action(player[i],target,skill));
    }

    for (int i = 0; actionQueue.empty(); i++) {
        performAction(
            actionQueue.front().source,
            actionQueue.front().target,
            actionQueue.front().skill
        );
        actionQueue.pop();
    }

    // reset or decrement status effect for enemy party

    for (int i = 0; i < enemy.getPartySize(); i++) {
        Skill* skill = getEnemySkill(enemy[i]);
        Character* target = getEnemyTarget(enemy[i],skill);
        actionQueue.push(Action(enemy[i],target,skill));
    }

    for (int i = 0; actionQueue.empty(); i++) {
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

    playerParty.printPartyInfo();
    enemyParty.printPartyInfo();

    while(playerParty.getIsAlive() && enemyParty.getIsAlive()) {
        printTurn();

        processTurn(playerParty,enemyParty);

        turnCount++;
    }

    if (playerParty.getIsAlive()) { 
        winner = &playerParty; 
        loser = &enemyParty; 

        float expDropped;
        for (int i = 0; i < loser->getPartySize(); i++) {
            expDropped += (*loser)[i]->getExpDrop();
        }

        expDropped /= winner->getPartySize();

        for (int i = 0; i < winner->getPartySize(); i++) {
            (*winner)[i]->canLevel(expDropped);
        }

        endInfo(winner,loser);
        return true; 
    }
    else { 
        winner = &enemyParty; 
        loser = &playerParty; 
        endInfo(winner,loser);
        return false; 
    }
}