#include "Game.h"

Game::Game(vector<Character*> party) 
    : playerParty(Party(party)) {

    arena.emplace_back(createEnemyParty(1));
    arena.emplace_back(createEnemyParty(2));
    arena.emplace_back(createEnemyParty(3));

    vector<Character*> bossParty;
    bossParty.emplace_back(Boss("Boss Man",4));

    arena.emplace_back(bossParty);
}

vector<Character*> Game::createEnemyParty(int level) {
    vector<Character*> party;

    party.emplace_back(Enemy("Enemy 1",level));
    party.emplace_back(Enemy("Enemy 2",level));
    party.emplace_back(Enemy("Enemy 3",level));
    party.emplace_back(Enemy("Enemy 4",level));

    return party;
}

vector<Character*> Game::createPlayerParty() {

    for (int i = 0; i < 4; i++) {
        string name;

        cout << "Party Member " << i + 1 << ": " << endl;
        cout << "Name: ";
        cin >> name;

        cout << "Choose Class for " << name << ": " << endl;
        // TODO - Get Class
    }

}

void Game::gameLoop() {
    while (true) {
        int choice;

        cout << "Choose an option: \n";
        cout << "1. Fight\n";
        cout << "2. Print Player Stats\n";
        cout << "3. Quit\n";

        cin >> choice;

        if (choice == 1) {
            cout << "Entering battle " << currentIndex + 1 << " of " << (int)arena.size() << endl;

            Combat battle(player, arena[currentIndex]);
            bool result = battle.combatLoop();

            if(!result) { cout << "===== GAME OVER =====\n"; return; }

            player->fullHeal();

            currentIndex++;

            if (currentIndex >= (int)arena.size()) { 
                cout << "====================================================" << endl;
                cout << "===== CONGRATULATIONS - YOU DEFEATED THE ARENA =====" << endl; 
                cout << "====================================================" << endl;
                return; 
            }
        } else if (choice == 2) {
            player->printInfo();
        } else if (choice == 3) {
            cout << "===== GAME OVER =====\n"; 
            return;
        } else {
            cout << "Invalid Option.\n";
        }
    }
}