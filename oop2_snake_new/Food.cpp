#include "Snake.h"

extern Score _score;
extern int _MAX_LEN;
extern Snake _snake;
extern int _X, _Y;

Food::Food() {
	int x = INDENT;
	x += rand() * time(0) % (static_cast<__int64>(_X) - 8);
	if (x % 2 == 1) x -= 1;
	int y = INDENT;
	y += rand() * time(0) % (static_cast<__int64>(_Y) - 6);
	set_coordinates(x, y);
}

Food::Food(int x, int y) {
	set_coordinates(x, y);
}

bool Food::is_eaten() {
	Coordinates snake_coord = _snake.get_head_coordinates();
	Coordinates food_coord = get_coordinates();
	if (snake_coord.get_x() == food_coord.get_x() && 
		snake_coord.get_y() == food_coord.get_y()) {
		_MAX_LEN++;
		_score.set_score(_score.get_score() + 1);
		return 1;
	}
	return 0;
}