#include "snake.h"

Field::Field(FIELD_SIZE field_size) {
	std::pair<int, int> size;
	switch (field_size) {
		case SMALL:
			size.first = 29;
			size.second = 15;
			break;
		case NORMAL:
			size.first = 33;
			size.second = 17;
			break;
		case LARGE:
			size.first = 47;
			size.second = 23;
			break;
		default:
			break;
	}

	std::string screen("mode con cols=");
	screen += std::to_string(size.first);
	screen += " lines=";
	screen += std::to_string(size.second);

	system(screen.c_str());

	this->field_size = size;

	this->score = Score();
	this->snake = Snake();
	this->food = Food();
}

void Field::display_field() {
	for (int x = 2; x < field_size.first - 2; x += 2) {
		set_cursor_coordinates(x, 3);
		std::cout << '#';
		set_cursor_coordinates(x, field_size.second - 2);
		std::cout << '#';
	}
	for (int y = 1; y < field_size.second - 4; y++) {
		set_cursor_coordinates(2, y + 2);
		std::cout << '#';
		set_cursor_coordinates(field_size.first - 3, y + 2);
		std::cout << '#';
	}

	set_cursor_coordinates(2, 1);
	std::cout << "SCORE:000";
}

void Field::place_food_in_random_place() {
TryAgain:
	int x = INDENT;
	x += rand() * time(0) % (static_cast<__int64_t>(field_size.first) - 8);
	if (x % 2 == 1) x -= 1;
	int y = INDENT;
	y += rand() * time(0) % (static_cast<__int64_t>(field_size.second) - 6);

	for (int i = 0; i < snake.get_displayed_length(); i++) {
		Coordinates segment_coord = snake.get_index_body_segment(i);
		if (segment_coord.get_x() == x && segment_coord.get_y() == y)
			goto TryAgain;
	}

	food.set_coordinates(x, y);

	set_cursor_coordinates(food.get_coordinates());

	std::cout << "F";
}

bool Field::is_food_eaten() {
	Coordinates snake_coord = snake.get_head_coordinates();
	Coordinates food_coord = food.get_coordinates();
	if (snake_coord.get_x() == food_coord.get_x() && 
		snake_coord.get_y() == food_coord.get_y()) {
		snake.set_actual_length(snake.get_actual_length() + 1);
		score.set_value(score.get_value() + 1);
		return 1;
	}
	return 0;
}

void Field::clear_field() {
	for (int i = 0; i < field_size.first; i++) {
		for (int j = 0; j < field_size.second; j++) {
			set_cursor_coordinates(i, j);
			std::cout << ' ';
		}
	}
}

void Field::delay(int time) {
	Delay(time);
}

void Field::set_cursor_coordinates(Coordinates coord) {
	SetCursorPosition(coord.get_x(), coord.get_y());
}

void Field::set_cursor_coordinates(int x, int y) {
	SetCursorPosition(x, y);
}

void Field::place_char(Coordinates coord, char chr) {
	set_cursor_coordinates(coord.get_x(), coord.get_y());
	std::cout << chr;
}

void Field::place_snake() {
	snake.set_head_coordinates(
		field_size.first / 4 + field_size.first / 4 % 2, 
		field_size.second / 2 + field_size.second / 2 % 2);
	Coordinates coord(snake.get_head_coordinates());
	set_cursor_coordinates(coord);

	for(int i = 0; i < 4; i++) {
		set_cursor_coordinates(coord);
		std::cout << ' ';
		delay(400);
		set_cursor_coordinates(coord);
	#if WEDGE_HEAD == 1
		std::cout << '>';
	#else 
		std::cout << '*';	
	#endif
		delay(400);
	}
}

void Field::change_snake_position() {
	Coordinates coord(snake.get_head_coordinates());
	int dir = snake.get_head_diraction();
	set_cursor_coordinates(coord);

	Coordinates segment_coord;

#if WEDGE_HEAD == 1
	if (dir == UP) {
		std::cout << '^';
		segment_coord.set_coordinates(coord.get_x(), coord.get_y() + 1);
	}
	else if (dir == DOWN) {
		std::cout << 'v';
		segment_coord.set_coordinates(coord.get_x(), coord.get_y() - 1);
	}
	else if (dir == LEFT) {
		std::cout << '<';
		segment_coord.set_coordinates(coord.get_x() + 2, coord.get_y());
	}
	else if (dir == RIGHT) {
		std::cout << '>';
		segment_coord.set_coordinates(coord.get_x() - 2, coord.get_y());
	}
#else
	std::cout << '*';
	if (dir == UP) segment_coord.set_coordinates(coord.get_x(), coord.get_y() + 1);
	else if (dir == DOWN) segment_coord.set_coordinates(coord.get_x(), coord.get_y() - 1);
	else if (dir == LEFT) segment_coord.set_coordinates(coord.get_x() + 2, coord.get_y());
	else if (dir == RIGHT) segment_coord.set_coordinates(coord.get_x() - 2, coord.get_y());
#endif

	snake.add_body_segment(segment_coord);

	set_cursor_coordinates(segment_coord);
	std::cout << '*';

	if (snake.get_displayed_length() > snake.get_actual_length() + 1) {
		set_cursor_coordinates(snake.del_and_get_last_body_segment());
		std::cout << ' ';
	}
}

void Field::update_score() {
	int score = this->score.get_value();
	set_cursor_coordinates(8, 1);
	if (score < 10) {
		std::cout << "00" << score;
	}
	else if (score < 100) {
		std::cout << "0" << score;
	}
	else {
		std::cout << score;
	}
}

void Field::kill_snake() {
	int len = snake.get_displayed_length();
	for (int i = 0; i < len; i++) {
		Coordinates coord = snake.get_index_body_segment(i);
		set_cursor_coordinates(coord);
		std::cout << ' ';
		delay(100);
	}
}

bool Field::is_time_to_kill_snake() {
	Coordinates head_coord = snake.get_head_coordinates();
	if (head_coord.get_x() < 3 || head_coord.get_x() > field_size.first - 4 || head_coord.get_y() < 4 || head_coord.get_y() > field_size.second - 3)
		return 1;
	for (int i = 0; i < snake.get_displayed_length(); i++) {
		Coordinates coord = snake.get_index_body_segment(i);
		if (coord.get_x() == head_coord.get_x() && coord.get_y() == head_coord.get_y()) {
			return 1;
		}
	}
	return 0;
}

void Field::the_end() {
	clear_field();
	set_cursor_coordinates((field_size.first - 7) / 2, field_size.second / 2);
	std::cout << "THE END";
}

void Field::clean_input() {
	ClearConsole();
}

void Field::start_game() {
	EnableNonBlockingInput();
	RemoveCursoreFromScreen();

	clean_input();
	display_field();
	place_food_in_random_place();
	place_snake();
	while (1) {
		snake.move_in_head_direction();
		if (is_time_to_kill_snake()) {
			kill_snake();
			the_end();
			DisableNonBlockingInput();
			ShowCursor();
			delay(500);
			clean_input();
			return;
		}
		change_snake_position();
		delay(150);
		if (is_food_eaten())
			place_food_in_random_place();
		update_score();
	}
}
