#include "Menu.h"
#include <iostream>

Menu::Menu(std::string&& msg,std::vector<Command>& opts)
    : menuMessage(msg), options(opts) {}

void Menu::runMenu() {
    while(true) {
        // print menu message
        std::cout << menuMessage << std::endl << ">";

        // print options
        for (size_t i=0;i < options.size(); i++) {
            std::cout << i + 1 << ") " << options[i].name;
        }

        // cin option
        size_t choice = 0;

        bool validOption{};
        while(!validOption) {
            std::cin >> choice;
        
            if(std::cin.fail()) {
                std::cout << "Invalid Option.\n";
                std::cin.clear();
                continue;
            }

            if(choice <= 0 || choice < options.size()) {
                std::cout << "Invalid Option.\n";
            }
            else { validOption = true; }
        }

        // invoke selected options function
        options[choice - 1].command();
    }
}