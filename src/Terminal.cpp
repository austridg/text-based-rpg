#include "Terminal.h"

void terminal::setup() {
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

std::ostream& terminal::reset(std::ostream& os) {
	os << ESCAPE << "0m";
	return os;
}

std::ostream& terminal::underline(std::ostream& os) {
	os << ESCAPE << "4m";
	return os;
}

std::ostream& terminal::negative(std::ostream& os) {
	os << ESCAPE << "7m";
	return os;
}

std::ostream& terminal::invert(std::ostream& os) { return negative(os); }

std::string terminal::foreground(Color color) {
	std::ostringstream code;
	code << ESCAPE << "38;2;" << (int)color.r << ';' << (int)color.g << ';'
		 << (int)color.b << 'm';
	return code.str();
}

std::string terminal::background(Color color) {
	std::ostringstream code;
	code << ESCAPE << "48;2;" << (int)color.r << ';' << (int)color.g << ';'
		 << (int)color.b << 'm';
	return code.str();
}

std::string terminal::both(Color foreground, Color background) {
	std::ostringstream code;
	code << ESCAPE << "38;2;" << (int)foreground.r << ';' << (int)foreground.g
		 << ';' << (int)foreground.b << 'm';
	code << ESCAPE << "48;2;" << (int)background.r << ';' << (int)background.g
		 << ';' << (int)background.b << 'm';
	return code.str();
}

void terminal::clearConsole() { std::cout << "\x1B[2J\x1B[H"; }
