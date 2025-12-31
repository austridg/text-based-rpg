#include "Menu.h"
#include <iostream>
#include <limits>
#include "../Terminal.h"

Menu::Menu(std::string&& msg,const std::vector<Command>& opts)
    : menuMessage(msg), options(opts) {}

void Menu::runMenu() {

    terminal::setup();
    

    // cin option
    size_t choice = 0;

    bool validOption{};
    while(!validOption) {

        std::cout << menuMessage << "\n";

        // print options
        for (size_t i=0;i < options.size(); i++) {
            std::cout << i + 1 << ") " << options[i].name << "\n";
        }

        std::cout << ">";
            
        
        if(!(std::cin >> choice)) {
            terminal::clearConsole();
            std::cout << terminal::foreground(terminal::red) << "Invalid Option.\n" << terminal::reset;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << ">";
            continue;
        }

        if(choice < 1 || choice > options.size()) {
            terminal::clearConsole();
            std::cout << terminal::foreground(terminal::red) << "Out of Range.\n" << terminal::reset;
            std::cout << ">";
        }
        else { validOption = true; }
    }

    // invoke selected options function
    options[choice - 1].command();

}