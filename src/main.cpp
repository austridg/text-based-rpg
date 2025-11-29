#include "Terminal.hpp"
#include "Game.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

int main() {
    srand(time(0));

    terminal::setup();

    cout << terminal::foreground(terminal::red) << "===== WELCOME =====\n\n" << terminal::reset;

    Game game;
    
    game.createPlayerParty();
    game.gameLoop();

    return 0;
}