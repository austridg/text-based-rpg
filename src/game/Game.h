#ifndef GAME_H
#define GAME_H

#include <vector>
#include <stack>
#include "../character/Character.h"
#include "../character_classes/Warrior.h"
#include "../character_classes/Mage.h"
#include "../character_classes/Archer.h"
#include "../character_classes/Healer.h"
#include "../character_classes/Enemy.h"
#include "../character_classes/Boss.h"
#include "../combat/Combat.h"
#include "../party/Party.h"
#include "../menu/Menu.h"
#include "../menu/MenuManager.h"
#include "GameData.h"

class Game {
private:
    GameData gameData;
public:
    Game();
    ~Game();

    vector<Character*> createEnemyParty(int level);
    
    void createPlayerParty();

    void clearConsole() const;

    void gameLoop();
};

#endif