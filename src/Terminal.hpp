#ifndef TERMINAL_H
#define TERMINAL_H

#include <Windows.h>

#include <iostream>
#include <sstream>
#include <iomanip>
#include <cstdint>

// NOTE: `using namespace std;` breaks the Windows.h file
// due to ambiguous byte definitions so this file should either
// be included before Character.h to prevent that or the using should
// be removed as it is considered bad practice for this exact reason.

// implemented using ANSI escape codes which are well explained in the following
// including why windows requires some setup before they work
// https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797
// https://learn.microsoft.com/en-us/windows/console/console-virtual-terminal-sequences
// 
// there are more things that ANSI escape codes are capable of, like setting the position of
// the cursor, turning on and off the cursors blinking, scrolling the terminal,
// deleting or inserting characters, setting the width of the terminal, etc.

// however there are some thing that are only possible specifically on each OS
// using their respective APIs winapi / Windows.h on windows, x11 / wayland on linux, whatever the hell OSX / mac uses...

// example usage:
// terminal::setup(); // make sure to call setup so the windows terminal will understand the ANSI escape codes
// 
// std::cout << terminal::foreground(terminal::red) << "I'm Red!" << terminal::reset << '\n';
// std::cout << terminal::both(terminal::green, terminal::red) << terminal::underline << "Green on Red" << terminal::reset << '\n';
// std::cout << terminal::invert << terminal::both(terminal::green, terminal::red) << terminal::underline << "Red on Green" << terminal::reset << '\n';
namespace terminal {
    struct Color {
        uint8_t r, g, b;

        Color(uint8_t r, uint8_t g, uint8_t b) : r(r), g(g), b(b) {}
        Color(uint32_t code) : r((code & 0xFF0000) >> 16), g((code & 0x00FF00) >> 8), b(code & 0x0000FF) {}
    };

    // standardize the colors instead of using the built-in 16 color variants
    static Color black = Color(0x000000);
    static Color red = Color(0xAA0000);
    static Color green = Color(0x00AA00);
    static Color yellow = Color(0xAAAA00);
    static Color blue = Color(0x0000AA);
    static Color magenta = Color(0xAA00AA);
    static Color cyan = Color(0x00AAAA);
    static Color white = Color(0xAAAAAA);
    
    static Color brightBlack = Color(0x555555);
    static Color brightRed = Color(0xFF5555);
    static Color brightGreen = Color(0x55FF55);
    static Color brightYellow = Color(0xFFFF55);
    static Color brightBlue = Color(0x5555FF);
    static Color brightMagenta = Color(0xFF55FF);
    static Color brightCyan = Color(0x55FFFF);
    static Color brightWhite = Color(0xFFFFFF);
    
    static const std::string ESCAPE = "\x1b[";
    
    // ensures windows will support ANSI escape codes, on mac and linux
    // they should just work out of the box but that needs to be validated
    void setup() {
#if defined(_WIN32)
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
        GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    
        DWORD dwMode = 0;
        GetConsoleMode(hConsole, &dwMode);
        dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        SetConsoleMode(hConsole, dwMode);
#elif defined(__OSX__)
        // TODO: handle any Mac / OSX specific setup if needed
#elif defined(__linux__)
        // TODO: handle any Linux specific setup if needed
#endif
    }

    // clear any text effect (underline, foreground, background, inversion)
    std::ostream& reset(std::ostream& os) {
        os << "\x1b[0m";
        return os;
    }

    std::ostream& underline(std::ostream& os) {
        os << "\x1b[4m";
        return os;
    }

    std::ostream& negative(std::ostream& os) {
        os << "\x1b[7m";
        return os;
    }

    std::ostream& invert(std::ostream& os) {
        return negative(os);
    }

    std::string foreground(Color color) {
        std::ostringstream code;
        code << ESCAPE << "38;2;" << (int)color.r << ';' << (int)color.g << ';' << (int)color.b << 'm';
        return code.str();
    }

    std::string background(Color color) {
        std::ostringstream code;
        code << ESCAPE << "48;2;" << (int)color.r << ';' << (int)color.g << ';' << (int)color.b << 'm';
        return code.str();
    }

    std::string both(Color foreground, Color background) {
        std::ostringstream code;
        code << ESCAPE << "38;2;" << (int)foreground.r << ';' << (int)foreground.g << ';' << (int)foreground.b << 'm';
        code << ESCAPE << "48;2;" << (int)background.r << ';' << (int)background.g << ';' << (int)background.b << 'm';
        return code.str();
    }
}

#endif // TERMINAL_H