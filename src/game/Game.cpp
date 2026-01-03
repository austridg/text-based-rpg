#include "Game.h"

Game::Game()
    : manager(&gameData) {

    gameData.arena.emplace_back(createEnemyParty(1));
    gameData.arena.emplace_back(createEnemyParty(2));
    gameData.arena.emplace_back(createEnemyParty(3));

    gameData.arena.emplace_back(Party(std::vector<Character*>{
        new Boss("Maldor",5)
    }));
}

Game::~Game() {
    // delete player party
    for (size_t i = 0; i < gameData.playerParty.getPartySize(); i++) {
        delete gameData.playerParty[i];
    }

    // delete arena
    for (size_t i = 0; i < gameData.arena.size(); i++) {
        for (size_t j = 0; j < gameData.arena[i].getPartySize(); j++) {
            delete gameData.arena[i].getParty()[j];
        }
    }

    //  TODO - clear vector if you want to reuse later
}

// TODO - Make More Sophisticated
std::vector<Character*> Game::createEnemyParty(int level) {

    std::vector<Character*> party;

    for(size_t i = 0; i < 4; i++) {

        std::string name = possibleNames[randNumber(0,19)];

        switch(randNumber(0,3)) {
            case 0:
                party.emplace_back(new Warrior(name,level));
                break;
            case 1:
                party.emplace_back(new Mage(name,level));
                break;
            case 2:
                party.emplace_back(new Archer(name,level));
                break;
            case 3:
                party.emplace_back(new Healer(name,level));
                break;
        }

    }

    return party;
}

void Game::createPlayerParty() {
    int choice;

    // create player party
    for (int i = 0; i < 4; i++) {

        // prompt for member name
        std::string name;
        std::cout << "Party Member " << i + 1 << ": " << "\n";
        std::cout << "Name: ";
        std::cin >> name;
        clearConsole();

        // prompt for member class
        bool endLoop{};
        while(!endLoop) {
            std::cout << "Choose Class for " << name << ": " << "\n";
            std::cout << "1) " << terminal::foreground(terminal::brightRed) << "Warrior\n" << terminal::reset;
            std::cout << "2) " << terminal::foreground(terminal::brightBlue) << "Mage\n" << terminal::reset;
            std::cout << "3) " << terminal::foreground(terminal::brightGreen) << "Archer\n" << terminal::reset;
            std::cout << "4) " << terminal::foreground(terminal::brightMagenta) << "Healer\n" << terminal::reset;
            std::cout << terminal::reset << ">";
            std::cin >> choice;

            clearConsole();

            if (choice < 1 || choice > 4) { std::cout << terminal::foreground(terminal::red) << "Invalid Option.\n" << terminal::reset; }
            else { endLoop = true; }
        }

        if (choice == 1) { gameData.playerParty.insertMember(new Warrior(name,1)); }
        if (choice == 2) { gameData.playerParty.insertMember(new Mage(name,1)); }
        if (choice == 3) { gameData.playerParty.insertMember(new Archer(name,1)); }
        if (choice == 4) { gameData.playerParty.insertMember(new Healer(name,1)); }

    }

}

void Game::gameLoop() {
    createPlayerParty();
    terminal::background(terminal::white);
    manager.createMainMenu();

    while (!gameData.endGame) {

        manager.run();

    }
}

const std::string& Game::generateName() {
    return possibleNames[(rand() % 19)];
}

void Game::clearConsole() const {
    std::cout << "\x1B[2J\x1B[H";
}