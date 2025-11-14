#ifndef GAME_H
#define GAME_H

#include <vector>
#include "Character/Character.h"
#include "character_classes/Warrior.h"
#include "character_classes/Mage.h"
#include "character_classes/Archer.h"
#include "character_classes/Healer.h"
#include "character_classes/Enemy.h"
#include "character_classes/Boss.h"
#include "combat/Combat.h"
#include "party/Party.h"

class Game {
private:
    Party playerParty;
    vector<Party> arena;
    int currentIndex;
public:
    Game(vector<Character*> party);
    ~Game();

    vector<Character*> createEnemyParty(int level);
    vector<Character*> createPlayerParty();

    void gameLoop();
};

#endif