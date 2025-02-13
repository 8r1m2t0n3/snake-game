#include "game.h"

Window::Window(std::pair<int, int> size) {
	std::string screen("mode con cols=");
	screen += std::to_string(size.first);
	screen += " lines=";
	screen += std::to_string(size.second);

	system(screen.c_str());

	this->size = size;
}

std::pair<int, int> Window::getSize() {
	return size;
}

void Window::moveCursor(Coordinates coord) {
	SetCursorPosition(coord.getX(), coord.getY());
}

void Window::moveCursor(int x, int y) {
	SetCursorPosition(x, y);
}

void Window::displayCharacter(Coordinates coord, char chr) {
	moveCursor(coord);
	std::cout << chr << std::flush;
}

void Window::displayString(Coordinates coord, std::string str) {
	moveCursor(coord);
	std::cout << str << std::flush;
}

void Window::delay(int time) {
	Delay(time);
}

void Window::clearScreen() {
	ClearConsole();
}

void Window::enableNonBlockingInput() {
	EnableNonBlockingInput();
}

void Window::disableNonBlockingInput() {
	DisableNonBlockingInput();
}

void Window::hideCursore() {
	RemoveCursoreFromScreen();
}

void Window::showCursor() {
	ShowCursor();
}
