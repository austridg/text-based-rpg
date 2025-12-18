#include "Menu.h"
#include <iostream>
#include <limits>

Menu::Menu(std::string&& msg,const std::vector<Command>& opts)
    : menuMessage(msg), options(opts) {}

void Menu::runMenu() {
    // print menu message
    std::cout << menuMessage << std::endl;

    // print options
    for (size_t i=0;i < options.size(); i++) {
        std::cout << i + 1 << ") " << options[i].name << std::endl;
    }

    std::cout << ">";

    // cin option
    size_t choice = 0;

    bool validOption{};
    while(!validOption) {
            
        
        if(!(std::cin >> choice)) {
            std::cout << "Invalid Option.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        if(choice < 1 || choice > options.size()) {
            std::cout << "Out of Range.\n";
        }
        else { validOption = true; }
    }

    // invoke selected options function
    options[choice - 1].command();

}