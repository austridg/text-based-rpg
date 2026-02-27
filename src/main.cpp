#include "../src/game/Game.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

int main() {
	srand(time(0));

	terminal::setup();

	Game game;

	game.gameLoop();

	return 0;
}
