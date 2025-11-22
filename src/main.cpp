#include "Game.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

int main() {
    srand(time(0));

    cout << "===== WELCOME =====\n\n";

    Game game;
    
    game.createPlayerParty();

    return 0;
}