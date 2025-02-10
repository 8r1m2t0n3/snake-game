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
	void set_direction(DIRECTION dir);
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
	void check_direction();
};

class Snake {
private:
	Head head;
	std::queue<Coordinates> body;
	int actual_length;
public:
	Snake();
	void set_head_coordinates(int x, int y);
	void set_head_direction(DIRECTION dir);
	Coordinates get_head_coordinates();
	int get_head_diraction();
	int get_displayed_length();
	int get_actual_length();
	void set_actual_length(int new_actual_length);
	void move_in_head_direction();
	void add_body_segment(Coordinates coord);
	Coordinates del_and_get_last_body_segment();
	Coordinates get_index_body_segment(int index);
};

class Score {
private:
	int value;
public:
	Score() {
		value = 0;
	}
	int get_value() {
		return value;
	}
	void set_value(int value) {
		this->value = value;
	}
};

class Food : public Coordinates {
public:
	Food() = default;
	Food(int x, int y) {
		set_coordinates(x, y);
	}
};

class Field {
private:
	Score score;
	Snake snake;
	Food food;
	std::pair<int, int> field_size;
public:
	Field(FIELD_SIZE field_size);
	void start_game();
private:
	void clean_input();
	void display_field();
	void clear_field();
	void place_food_in_random_place();
	bool is_food_eaten();
	bool is_time_to_kill_snake();
	void place_char(Coordinates coord, char chr);
	void delay(int time);
	void set_cursor_coordinates(Coordinates coordinates);
	void set_cursor_coordinates(int x, int y);
	void place_snake();
	void change_snake_position();
	void update_score();
	void kill_snake();
	void the_end();
};
