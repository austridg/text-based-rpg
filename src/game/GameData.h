#pragma once

#include "../combat/Action.h"
#include "../combat/Combat.h"
#include "../party/Party.h"
#include <queue>

enum class GameState { MAIN_MENU, BATTLE };

struct GameData {
	Party playerParty{};
	Party bossParty{};
	std::vector<Party> arena{};
	size_t arenaIndex = 0;
	size_t partyIndex = 0;
	Combat currentBattle{};
	GameState state = GameState::MAIN_MENU;
	bool endGame{};
};
