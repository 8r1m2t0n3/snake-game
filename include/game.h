#include <iostream>
#include <random>
#include <time.h>
#include <iostream>
#include <queue>
#include <string>
#include "console_handler.h"

/* -------- CHANGEABLE -------- */
#define DEFAULT_LEN 4
#define WEDGE_HEAD 1 // 0 or 1
/* ---------------------------- */

/* --------- CONSTANTS --------- */
#define INDENT 4
/* ---------------------------- */

enum FIELD_SIZE { 
	SMALL = 0, 
	NORMAL, 
	LARGE 
};

#ifdef _WIN32

enum DIRECTION {
	UP = VK_UP,
	DOWN = VK_DOWN,
	LEFT = VK_LEFT,
	RIGHT = VK_RIGHT
};

#elif __linux__

enum DIRECTION {
	UP = 65,
	DOWN = 66,
	LEFT = 68,
	RIGHT = 67
};

#endif

class Direction {
private:
	DIRECTION direction;
public:
	void setDirection(DIRECTION dir);
	int getDirection();
};

class Coordinates {
private:
	int x;
	int y;
public:
	Coordinates();
	Coordinates(int x, int y);
	bool operator==(Coordinates coord);
	Coordinates getCoordinates();
	int getX();
	int getY();
	void setX(int x);
	void setY(int y);
	void setCoordinates(Coordinates coord);
	void setCoordinates(int x, int y);
};

class Head : public Coordinates, public Direction {
public:
	Head();
	Head(int x, int y);
	void checkDirection();
};

class Snake {
private:
	Head head;
	std::queue<Coordinates> body;
	int actualLength;
public:
	Snake();
	void setHeadCoordinates(int x, int y);
	void setHeadDirection(DIRECTION dir);
	Coordinates getHeadCoordinates();
	int getHeadDiraction();
	int getDisplayedLength();
	int getActualLength();
	void setActualLength(int new_actual_length);
	void moveInHeadDirection();
	void addBodySegment(Coordinates coord);
	Coordinates deleteAndGetLastBodySegment();
	Coordinates getBodySegment(int index);
};

class Score {
private:
	int value;
public:
	Score() {
		value = 0;
	}
	int getValue() {
		return value;
	}
	void setValue(int value) {
		this->value = value;
	}
};

class Food : public Coordinates {
public:
	Food() = default;
	Food(int x, int y) {
		setCoordinates(x, y);
	}
};

class Window {
private:
	std::pair<int, int> size;
public:
	Window() = default;
	Window(std::pair<int, int> size);
	std::pair<int, int> getSize();
	void moveCursor(Coordinates coord);
	void moveCursor(int x, int y);
	void displayCharacter(Coordinates coord, char chr);
	void displayString(Coordinates coord, std::string str);
	void delay(int time);
	void clearScreen();
	void enableNonBlockingInput();
	void disableNonBlockingInput();
	void hideCursore();
	void showCursor();
};

class Game {
private:
	Window window;
	Score score;
	Snake snake;
	Food food;
public:
	Game(FIELD_SIZE fieldSize);
	void displayField();
	void placeFoodRandomly();
	bool isFoodEaten();
	void clearField();
	void playSnakeAppearanceAnimation();
	void displaySnake();
	void displayScore();
	bool isSnakeCollidingWithObstacle();
	void killSnake();
	void displayGameEndLabel();
	void start();
};
