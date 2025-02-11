#include "console_handler.h"
#include <iostream>

#ifdef _WIN32

#include <windows.h>
#include <conio.h>

void ClearConsole() {
    std::cout << "\033[2J\033[H" << std::flush;
}

void Delay(int sleepTime) {
    Sleep(sleepTime);
}

bool IsKeyPressed(int keyCode) {
    return GetAsyncKeyState(keyCode) & 0x8000;
}

void SetCursorPosition(int x, int y) {
    COORD pos = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void RemoveCursoreFromScreen() {
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = 0;
	SetConsoleCursorInfo(out, &cursorInfo);
}

void ShowCursor() {
    // implementation does not required for windows
}

void EnableNonBlockingInput() {
    // implementation does not required for windows
}

void DisableNonBlockingInput() {
    // implementation does not required for windows
}

#elif __linux__

#include <unistd.h>
#include <termios.h>
#include <fcntl.h>

struct termios orig_termios;

void ClearConsole() {
    std::cout << "\033[2J\033[H" << std::flush;
}

void Delay(int sleepTime) {
    usleep(sleepTime * 1000);
}

void EnableNonBlockingInput() {
    struct termios tt;
    tcgetattr(STDIN_FILENO, &orig_termios);

    tt = orig_termios;
    tt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &tt);

    fcntl(STDIN_FILENO, F_SETFL, fcntl(STDIN_FILENO, F_GETFL) | O_NONBLOCK);
}

void DisableNonBlockingInput() {
    tcsetattr(STDIN_FILENO, TCSANOW, &orig_termios);
    fcntl(STDIN_FILENO, F_SETFL, fcntl(STDIN_FILENO, F_GETFL) & ~O_NONBLOCK);
}

int GetPressedKey() {
    getchar();
    getchar();
    return getchar();
}

void SetCursorPosition(int x, int y) {
    std::cout << "\033[" << y << ";" << x << "H" << std::flush;
}

void RemoveCursoreFromScreen() {
    std::cout << "\033[?25l" << std::flush;
}

void ShowCursor() {
    std::cout << "\033[?25h" << std::flush;
}

#endif
