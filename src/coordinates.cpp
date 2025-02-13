#include "game.h"

Coordinates::Coordinates() {
	x = 0;
	y = 0;
}

Coordinates::Coordinates(int x, int y) {
	this->x = x;
	this->y = y;
}

bool Coordinates::operator==(Coordinates coord) {
	return x == coord.getX() && y == coord.getY();
}

Coordinates Coordinates::getCoordinates() {
	Coordinates coord(x, y);
	return coord;
}

int Coordinates::getX() {
	return x;
}

int Coordinates::getY() {
	return y;
}

void Coordinates::setCoordinates(Coordinates coord) {
	x = coord.getX();
	y = coord.getY();
}

void Coordinates::setCoordinates(int x, int y) {
	this->x = x;
	this->y = y;
}

void Coordinates::setX(int val) {
	x = val;
}

void Coordinates::setY(int val) {
	y = val;
}
