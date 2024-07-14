#include "Snake.h"

Field _field(SMALL);
Snake _snake;
Food _food;
Score _score;

int main() {
	_field.build_Field();
	_field.place_snake(_snake);
	while (1) {
		_field.place_food(_food);
		_snake.move();
		if (_snake.is_time_to_die()) {
			_field.kill_snake(_snake);
			_field.the_end();
			return 0;
		}
		_field.change_snake_position(_snake);
		_field.deley(150);
		if (_food.is_eaten())
			_food = _field.replace_food();
		_field.update_score();
	}
}

/* ############### BUGS ############### */

// food appears inside the snake
// sometimes before death head just disappears

/* #################################### */