#include "snake.h"

extern Field _field;
extern int _X, _Y;

Snake::Snake() {
	actual_length = DEFAULT_LEN - 1;
	head.set_coordinates(_X / 2 + _X / 2 % 2, _Y / 2 + _Y / 2 % 2);
	head.set_direction(RIGHT);
}

Head::Head() {
	set_coordinates(0, 0);
	set_direction(RIGHT);
}

Head::Head(int x, int y) {
	set_coordinates(x, y);
	set_direction(RIGHT);
}

void Head::check_diraction() {
	int dir = get_direction();

	if (GetAsyncKeyState(UP) && dir != DOWN) {
		set_direction(UP);
	}
	else if (GetAsyncKeyState(DOWN) && dir != UP) {
		set_direction(DOWN);
	}
	else if (GetAsyncKeyState(LEFT) && dir != RIGHT) {
		set_direction(LEFT);
	}
	else if (GetAsyncKeyState(RIGHT) && dir != LEFT) {
		set_direction(RIGHT);
	}
}

Coordinates Snake::get_head_coordinates() {
	return head.get_coordinates();
}

void Snake::move() {
	head.check_diraction();

	switch (head.get_direction()) {
	case UP:
		head.set_coordinates(head.get_x(), head.get_y() - 1);
		break;
	case DOWN:
		head.set_coordinates(head.get_x(), head.get_y() + 1);
		break;
	case LEFT:
		head.set_coordinates(head.get_x() - 2, head.get_y());
		break;
	case RIGHT:
		head.set_coordinates(head.get_x() + 2, head.get_y());
		break;
	default:
		return;
	}
}

bool Snake::is_time_to_die() {
	int head_x = head.get_x();
	int head_y = head.get_y();
	if (head_x < 3 || head_x > _X - 4 || head_y < 4 || head_y > _Y - 3)
		return 1;
	for (int i = 0; i < body.size(); i++) {
		Coordinates coord = get_index_body_segment(i);
		if (coord.get_x() == head.get_x() && coord.get_y() == head.get_y()) {
			return 1;
		}
	}
	return 0;
}

int Snake::get_head_diraction() {
	return head.get_direction();
}

int Snake::get_displayed_length() {
	return body.size();
}

int Snake::get_actual_length() {
	return actual_length;
}

void Snake::set_actual_length(int new_actual_length) {
	actual_length = new_actual_length;
}

void Snake::add_body_segment(Coordinates coord) {
	body.push(coord);
}

Coordinates Snake::del_and_get_last_body_segment() {
	Coordinates coord = body.front();
	body.pop();
	return coord;
}

Coordinates Snake::get_index_body_segment(int ind) {
	if (ind > body.size() || ind < 0) {
		Coordinates coord(0, 0);
		return coord;
	}
	std::queue<Coordinates> body_clone = body;
	while (ind != 0) {
		body_clone.pop();
		ind--;
	}
	return body_clone.front();
}
