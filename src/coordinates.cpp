#include "snake.h"

Coordinates::Coordinates() {
	x = 0;
	y = 0;
}

Coordinates::Coordinates(int x, int y) {
	this->x = x;
	this->y = y;
}

bool Coordinates::operator==(Coordinates coord) {
	return x == coord.get_x() && y == coord.get_y();
}

Coordinates Coordinates::get_coordinates() {
	Coordinates coord(x, y);
	return coord;
}

int Coordinates::get_x() {
	return x;
}

int Coordinates::get_y() {
	return y;
}

void Coordinates::set_coordinates(Coordinates coord) {
	x = coord.get_x();
	y = coord.get_y();
}

void Coordinates::set_coordinates(int x, int y) {
	this->x = x;
	this->y = y;
}

void Coordinates::set_x(int val) {
	x = val;
}

void Coordinates::set_y(int val) {
	y = val;
}
