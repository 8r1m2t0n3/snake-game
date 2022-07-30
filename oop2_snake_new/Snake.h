#include <iostream>
#include <windows.h>
#include <random>
#include <time.h>
#include <conio.h>
#include <iostream>
#include <queue>
#include <string>
using namespace std;

/* -------- CHANGEABLE -------- */
#define DEFAULT_LEN 4

#define WEDGE_HEAD 1 // 0 or 1
/* ---------------------------- */

/* --------- CONSTANT --------- */
#define UP VK_UP
#define DOWN VK_DOWN
#define LEFT VK_LEFT
#define RIGHT VK_RIGHT

#define SMALL 0
#define MEDIUM 1
#define BIG 2

#define INDENT 4
/* ---------------------------- */

class Direction {
private:
	int direction;
public:
	void set_direction(int dir);
	int get_direction();
};

class Coordinates {
private:
	int x;
	int y;
public:
	Coordinates();
	Coordinates(int x, int y);
	bool operator==(Coordinates coord);
	Coordinates get_coordinates();
	int get_x();
	int get_y();
	void set_coordinates(Coordinates coord);
	void set_coordinates(int x, int y);
	void set_x(int val);
	void set_y(int val);
};

class Head : public Coordinates, public Direction {
public:
	Head();
	Head(int x, int y);
	void check_diraction();
};

class Snake {
private:
	Head head;
	queue<Coordinates> body;
	int length;
public:
	Snake();
	Coordinates get_head_coordinates();
	int get_head_diraction();
	int get_length();
	void set_length(int length);
	void move();
	bool is_time_to_die();
	void add_body_segment(Coordinates coord);
	Coordinates get_and_del_last_body_segment();
	Coordinates get_index_body_segment(int ind);
};

class Score {
private:
	int score;
public:
	Score() {
		score = 0;
	}
	int get_score() {
		return score;
	}
	void set_score(int score) {
		this->score = score;
	}
};

class Food : public Coordinates {
public:
	Food();
	Food(int x, int y);
	bool is_eaten();
};

class Field {
private:
	Score score;
	Snake snake;
	Food food;
public:
	Field(int psize);
	void build_Field();
	void clear_Field();
	void place_food(Food food);
	Food replace_food();
	void place_char(Coordinates coord, char chr);
	void deley(int time);
	void set_cursor_coordinates(Coordinates coordinates);
	void set_cursor_coordinates(int x, int y);
	void place_snake(Snake& snake);
	void change_snake_position(Snake& snake);
	void update_score();
	void kill_snake(Snake& snake);
	void the_end();
};
