#include "Game.h"

Game::Game()
    : currentIndex(0) {

    arena.emplace_back(createEnemyParty(1));
    arena.emplace_back(createEnemyParty(2));
    arena.emplace_back(createEnemyParty(3));

    bossParty.insertMember(new Boss("Boss Man",4));

    arena.emplace_back(bossParty);
}

Game::~Game() {
    // delete player party
    for (size_t i = 0; i < playerParty.getPartySize(); i++) {
        delete playerParty[i];
    }

    // delete arena
    for (size_t i = 0; i < arena.size(); i++) {
        for (size_t j = 0; i < arena[i].getPartySize(); j++) {
            delete arena[i].getParty()[j];
        }
    }
}

Game& Game::getInstance() {
    static Game Instance;
    return Instance;
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

        if (choice == 1) { playerParty.insertMember(new Warrior(name,1)); }
        if (choice == 2) { playerParty.insertMember(new Mage(name,1)); }
        if (choice == 3) { playerParty.insertMember(new Archer(name,1)); }
        if (choice == 4) { playerParty.insertMember(new Healer(name,1)); }

        clearConsole();

    }

}

void Game::printMenu() const {
    cout << "Choose an option: \n";
    cout << "1. Fight\n";
    cout << "2. Print Party Stats\n";
    cout << "3. Quit\n";
    cout << ">";
}

void Game::clearConsole() const {
    cout << "\033[2J";
}

void Game::gameLoop() {
    GameData* gm;
    MenuManager manager(gm);
    int choice;

    bool endGame{};
    while (!endGame) {

        manager.createMainMenu();

}