#include "game.h"

Snake::Snake() {
	actualLength = DEFAULT_LEN - 1;
	head.setDirection(RIGHT);
}

void Snake::setHeadCoordinates(int x, int y) {
	head.setCoordinates(x, y);
}

void Snake::setHeadDirection(DIRECTION dir) {
	head.setDirection(dir);
}

Head::Head() {
	setDirection(RIGHT);
}

Head::Head(int x, int y) {
	setCoordinates(x, y);
	setDirection(RIGHT);
}

void Head::checkDirection() {
	int dir = getDirection();
	int pressedKey = GetPressedKey();

	if (pressedKey == RIGHT && dir != LEFT) {
		setDirection(RIGHT);
	}
	else if (pressedKey == UP && dir != DOWN) {
		setDirection(UP);
	}
	else if (pressedKey == DOWN && dir != UP) {
		setDirection(DOWN);
	}
	else if (pressedKey == LEFT && dir != RIGHT) {
		setDirection(LEFT);
	}
}

Coordinates Snake::getHeadCoordinates() {
	return head.getCoordinates();
}

void Snake::moveInHeadDirection() {
	head.checkDirection();

	switch (head.getDirection()) {
	case UP:
		head.setCoordinates(head.getX(), head.getY() - 1);
		break;
	case DOWN:
		head.setCoordinates(head.getX(), head.getY() + 1);
		break;
	case LEFT:
		head.setCoordinates(head.getX() - 2, head.getY());
		break;
	case RIGHT:
		head.setCoordinates(head.getX() + 2, head.getY());
		break;
	default:
		return;
	}
}

int Snake::getHeadDiraction() {
	return head.getDirection();
}

int Snake::getDisplayedLength() {
	return body.size();
}

int Snake::getActualLength() {
	return actualLength;
}

void Snake::setActualLength(int new_actual_length) {
	actualLength = new_actual_length;
}

void Snake::addBodySegment(Coordinates coord) {
	body.push(coord);
}

Coordinates Snake::deleteAndGetLastBodySegment() {
	Coordinates coord = body.front();
	body.pop();
	length--;
	return coord;
}

Coordinates Snake::getBodySegment(int ind) {
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
