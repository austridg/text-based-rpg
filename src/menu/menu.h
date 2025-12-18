#pragma once

#include <functional>
#include <string>

struct Command {
    std::string name;
    std::function<void()> command;
};

class Menu {
public:
    std::string menuMessage;
    std::vector<Command> options;

    Menu(std::string&& msg,const std::vector<Command>& opts);
    void runMenu();
};