#include <functional>
#include <string>

enum class MenuState { FIGHT_MENU, SELECT_SKILL_MENU, SELECT_TARGET_MENU };

struct Command {
    std::string name;
    std::function<void()> command;
};

class Menu {
public:
    std::string menuMessage;
    std::vector<Command> options;

    Menu(std::string&& msg,std::vector<Command>& opts);
    void runMenu();
};