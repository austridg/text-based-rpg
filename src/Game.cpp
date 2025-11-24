#include "Game.h"

Game::Game() {

    arena.emplace_back(createEnemyParty(1));
    arena.emplace_back(createEnemyParty(2));
    arena.emplace_back(createEnemyParty(3));

    bossParty.insertMember(new Boss("Boss Man",4));

    arena.emplace_back(bossParty);
}

Game::~Game() {
    // delete player party
    for (int i = 0; i < playerParty.getPartySize(); i++) {
        delete playerParty[i];
    }

    // delete arena
    for (int i = 0; i < arena.size(); i++) {
        for (int j = 0; i < arena[i].getPartySize(); j++) {
            delete arena[i].getParty()[j];
        }
    }
}

// TODO - Make More Sophisticated
vector<Character*> Game::createEnemyParty(int level) {

    // TODO - FIX POSSIBLE COMPILER ERROR
    // - Storing pointers but actual variable is destoryed.

    vector<Character*> party;

    party.emplace_back(new Enemy("Enemy 1",level));
    party.emplace_back(new Enemy("Enemy 2",level));
    party.emplace_back(new Enemy("Enemy 3",level));
    party.emplace_back(new Enemy("Enemy 4",level));

    return party;
}

void Game::createPlayerParty() {
    vector<Character*> party;
    int choice;

    // create player party
    for (int i = 0; i < 4; i++) {
        Character* newPartyMember;

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
            cout << "4) Healer\n";
            cin >> choice;

            if (choice < 1 || choice > 4) { cout << "Invalid Option.\n"; }

            endLoop = true;
        }

        if (choice == 1) { newPartyMember = new Warrior(name,1); }
        if (choice == 2) { newPartyMember = new Mage(name,1); }
        if (choice == 3) { newPartyMember = new Archer(name,1); }
        if (choice == 4) { newPartyMember = new Healer(name,1); }

        playerParty.insertMember(newPartyMember);

    }

    playerParty = party;

}

void Game::printMenu() const {
    cout << "Choose an option: \n";
    cout << "1. Fight\n";
    cout << "2. Print Party Stats\n";
    cout << "3. Quit\n";
    cout << ">";
}

void Game::gameLoop() {
    int choice;

    bool endGame{};
    while (!endGame) {

        // get player choice
        printMenu();
        cin >> choice;

        switch(choice) {
            case 1: {
                cout << "Entering battle " << currentIndex + 1 << " of " << (int)arena.size() << endl;

                Combat battle(playerParty, arena[currentIndex]);
                bool result = battle.combatLoop();

                if(!result) { cout << "===== GAME OVER =====\n"; break; }

                playerParty.healParty();

                currentIndex++;

                if (currentIndex >= (int)arena.size()) { 
                    cout << "====================================================" << endl;
                    cout << "===== CONGRATULATIONS - YOU DEFEATED THE ARENA =====" << endl; 
                    cout << "====================================================" << endl;
                    endGame = true;
                }
                }
                break;
            case 2:
                playerParty.printPartyInfo();
                break;
            case 3:
                endGame = true;
                break;
            default:
                cout << "Invalid Option.\n";
                break;
        }
    }
}