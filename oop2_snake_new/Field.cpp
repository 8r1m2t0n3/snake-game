#include "Snake.h"

extern int _MAX_LEN;
extern Food _food;
extern Snake _snake;
extern Score _score;

int _X, _Y;

Field::Field(int psize) {
	pair<int, int> size;
	switch (psize) {
	case SMALL:
		size.first = 33;
		size.second = 17;
		break;
	case MEDIUM:
		size.first = 47;
		size.second = 23;
		break;
	case BIG:
		size.first = 61;
		size.second = 30;
		break;
	default:
		break;
	}
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = 0;
	SetConsoleCursorInfo(out, &cursorInfo);

	string screen("mode con cols=");
	screen += to_string(size.first);
	screen += " lines=";
	screen += to_string(size.second);

	system(screen.c_str());
	_X = size.first;
	_Y = size.second;
}

void Field::build_Field() {
	for (int x = 2; x < _X - 2; x += 2) {
		set_cursor_coordinates(x, 3);
		cout << '#';
		set_cursor_coordinates(x, _Y - 2);
		cout << '#';
	}
	for (int y = 1; y < _Y - 4; y++) {
		set_cursor_coordinates(2, y + 2);
		cout << '#';
		set_cursor_coordinates(_X - 3, y + 2);
		cout << '#';
	}

	set_cursor_coordinates(2, 1);
	cout << "SCORE:000";
}

void Field::place_food(Food food) {
	set_cursor_coordinates(food.get_coordinates());
	cout << "F";
}

void Field::clear_Field() {
	for (int i = 0; i < _X; i++) {
		for (int j = 0; j < _Y; j++) {
			set_cursor_coordinates(i, j);
			cout << ' ';
		}
	}
}

void Field::deley(int time) {
	Sleep(time);
}

void Field::set_cursor_coordinates(Coordinates coordinates) {
	COORD coord;
	coord.X = coordinates.get_x();
	coord.Y = coordinates.get_y();
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void Field::set_cursor_coordinates(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void Field::place_char(Coordinates coord, char chr) {
	set_cursor_coordinates(coord);
	cout << chr;
}

Food Field::replace_food() {
TryAgain:
	Food new_food;
	for (int i = 0; i < _snake.get_length(); i++) {
		Coordinates segment_coord = _snake.get_index_body_segment(i);
		if (segment_coord == new_food.get_coordinates())
			goto TryAgain;
	}
	return new_food;
}

void Field::place_snake(Snake& snake) {
	Coordinates coord(snake.get_head_coordinates());
	set_cursor_coordinates(coord);
}

void Field::change_snake_position(Snake& snake) {
	Coordinates coord(snake.get_head_coordinates());
	int dir = snake.get_head_diraction();
	set_cursor_coordinates(coord);

	Coordinates segment_coord;

#if WEDGE_HEAD == 1
	if (dir == UP) {
		cout << '^';
		segment_coord.set_coordinates(coord.get_x(), coord.get_y() + 1);
	}
	else if (dir == DOWN) {
		cout << 'v';
		segment_coord.set_coordinates(coord.get_x(), coord.get_y() - 1);
	}
	else if (dir == LEFT) {
		cout << '<';
		segment_coord.set_coordinates(coord.get_x() + 2, coord.get_y());
	}
	else if (dir == RIGHT) {
		cout << '>';
		segment_coord.set_coordinates(coord.get_x() - 2, coord.get_y());
	}
#else
	cout << '*';
	if (dir == UP) segment_coord.set_coordinates(coord.get_x(), coord.get_y() + 1);
	else if (dir == DOWN) segment_coord.set_coordinates(coord.get_x(), coord.get_y() - 1);
	else if (dir == LEFT) segment_coord.set_coordinates(coord.get_x() + 2, coord.get_y());
	else if (dir == RIGHT) segment_coord.set_coordinates(coord.get_x() - 2, coord.get_y());
#endif

	snake.add_body_segment(segment_coord);

	set_cursor_coordinates(segment_coord);
	cout << '*';

	if (snake.get_length() > _MAX_LEN + 1) {
		set_cursor_coordinates(snake.get_and_del_last_body_segment());
		cout << ' ';
	}
}

void Field::update_score() {
	int score = _score.get_score();
	set_cursor_coordinates(8, 1);
	if (score < 10) {
		cout << "00" << score;
	}
	else if (score < 100) {
		cout << "0" << score;
	}
	else {
		cout << score;
	}
}

void Field::kill_snake(Snake& snake) {
	int len = snake.get_length();
	for (int i = 0; i < len; i++) {
		Coordinates coord = snake.get_index_body_segment(i);
		set_cursor_coordinates(coord);
		cout << ' ';
		deley(100);
	}
}

void Field::the_end() {
	clear_Field();
	set_cursor_coordinates((_X - 7) / 2, _Y / 2);
	cout << "THE END";
	char chr = _getch();
	chr = _getch();
}
