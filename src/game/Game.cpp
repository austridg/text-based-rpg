#include "Game.h"

Game::Game()
    : manager(&gameData) {

    gameData.arena.emplace_back(createEnemyParty(1));
    gameData.arena.emplace_back(createEnemyParty(2));
    gameData.arena.emplace_back(createEnemyParty(3));

    gameData.arena.emplace_back(Party(std::vector<Character*>{
        new Boss("Boss Man",4)
    }));

}

Game::~Game() {
    // delete player party
    for (size_t i = 0; i < gameData.playerParty.getPartySize(); i++) {
        delete gameData.playerParty[i];
    }

    // delete arena
    for (size_t i = 0; i < gameData.arena.size(); i++) {
        for (size_t j = 0; i < gameData.arena[i].getPartySize(); j++) {
            delete gameData.arena[i].getParty()[j];
        }
    }

    //  TODO - clear vector if you want to reuse later
}

// TODO - Make More Sophisticated
vector<Character*> Game::createEnemyParty(int level) {

    vector<Character*> party;

    party.emplace_back(new Enemy("Enemy 1",level));
    party.emplace_back(new Enemy("Enemy 2",level));
    party.emplace_back(new Enemy("Enemy 3",level));
    party.emplace_back(new Enemy("Enemy 4",level));

    return party;
}

void Game::createPlayerParty() {
    int choice;

    // create player party
    for (int i = 0; i < 4; i++) {

        // prompt for member name
        string name;
        cout << "Party Member " << i + 1 << ": " << endl;
        cout << "Name: ";
        cin >> name;

        // prompt for member class
        bool endLoop{};
        while(!endLoop) {
            cout << "Choose Class for " << name << ": " << endl;
            cout << "1) Warrior\n";
            cout << "2) Mage\n";
            cout << "3) Archer\n";
            cout << "4) Healer\n>";
            cin >> choice;

            if (choice < 1 || choice > 4) { cout << "Invalid Option.\n"; }
            else { endLoop = true; }
        }

        if (choice == 1) { gameData.playerParty.insertMember(new Warrior(name,1)); }
        if (choice == 2) { gameData.playerParty.insertMember(new Mage(name,1)); }
        if (choice == 3) { gameData.playerParty.insertMember(new Archer(name,1)); }
        if (choice == 4) { gameData.playerParty.insertMember(new Healer(name,1)); }

        clearConsole();

    }

}

void Game::clearConsole() const {
    cout << "\033[2J";
}

void Game::gameLoop() {
    createPlayerParty();
    manager.createMainMenu();

    while (!gameData.endGame) {

        manager.run();
        std::cout << gameData.partyIndex << std::endl;

    }
}

bool Game::combatLoop() {
    gameData.currentBattle.battleStart();

    std::cout << "==== Player Party =====\n";
    gameData.playerParty.printPartyInfo();
    std::cout << endl << "==== Enemy Party =====\n";
    gameData.arena[gameData.arenaIndex].printPartyInfo();
    std::cout << endl;

    manager.createFightMenu();

    while(gameData.currentBattle.playerParty.getIsAlive() && gameData.currentBattle.enemyParty.getIsAlive()) {
        gameData.currentBattle.printTurn();

        manager.run();

        gameData.currentBattle.turnCount++;
    }
}