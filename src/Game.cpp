#include "Game.h"

Game::Game() {

    arena.emplace_back(createEnemyParty(1));
    arena.emplace_back(createEnemyParty(2));
    arena.emplace_back(createEnemyParty(3));

    vector<Character*> bossParty;
    bossParty.emplace_back(Boss("Boss Man",4));

    arena.emplace_back(bossParty);
}

// TODO - Make More Sophisticated
vector<Character*> Game::createEnemyParty(int level) {

    // TODO - FIX POSSIBLE COMPILER ERROR
    // - Storing pointers but actual variable is destoryed.

    vector<Character*> party;

    party.emplace_back(Enemy("Enemy 1",level));
    party.emplace_back(Enemy("Enemy 2",level));
    party.emplace_back(Enemy("Enemy 3",level));
    party.emplace_back(&Enemy("Enemy 4",level));

    return party;
}

void Game::createPlayerParty() {

    vector<Character*> party;

    int choice;

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
            cout << "4) Healer\n";
            cin >> choice;
            
            switch(choice) {
                case 1:
                    party.emplace_back(Warrior(name,1));
                    endLoop = true;
                    break;
                case 2:
                    party.emplace_back(Mage(name,1));
                    endLoop = true;
                    break;
                case 3:
                    party.emplace_back(Archer(name,1));
                    endLoop = true;
                    break;
                case 4:
                    party.emplace_back(Healer(name,1));
                    endLoop = true;
                    break;
                default:
                    cout << "Invalid Option.";
                    break;
            }
        }
        
        playerParty = party;
        return;

    }

}

void Game::printMenu() const {
    cout << "Choose an option: \n";
    cout << "1. Fight\n";
    cout << "2. Print Party Stats\n";
    cout << "3. Quit\n";
    cout << ">";
}

void Game::gameLoop() {
    bool endGame{};
    while (!endGame) {
        int choice;

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
                // TODO - Print All Members Info
                break;
            case 3:
                // TODO - Quit
                break;
            default:
                // TODO - Error Handle
                break;
        }
    }
}