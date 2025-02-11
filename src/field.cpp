#include "game.h"

void set_cursor_coordinates(Coordinates coord) {
	SetCursorPosition(coord.getX(), coord.getY());
}

void set_cursor_coordinates(int x, int y) {
	SetCursorPosition(x, y);
}

Field::Field(FIELD_SIZE fieldSize) {
	std::pair<int, int> size;
	switch (fieldSize) {
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

	this->fieldSize = size;

	this->score = Score();
	this->snake = Snake();
	this->food = Food();
}

void Field::displayField() {
	for (int x = 2; x < fieldSize.first - 2; x += 2) {
		set_cursor_coordinates(x, 3);
		std::cout << '#' << std::flush;;
		set_cursor_coordinates(x, fieldSize.second - 2);
		std::cout << '#' << std::flush;;
	}
	for (int y = 1; y < fieldSize.second - 4; y++) {
		set_cursor_coordinates(2, y + 2);
		std::cout << '#' << std::flush;;
		set_cursor_coordinates(fieldSize.first - 3, y + 2);
		std::cout << '#' << std::flush;;
	}

	set_cursor_coordinates(2, 1);
	std::cout << "SCORE:000" << std::flush;;
}

void Field::placeFoodRandomly() {
TryAgain:
	int x = INDENT + rand() * time(0) % (static_cast<__int64_t>(fieldSize.first) - 8);
	if (x % 2 == 1) x -= 1;
	int y = INDENT + rand() * time(0) % (static_cast<__int64_t>(fieldSize.second) - 6);

	for (int i = 0; i < snake.getDisplayedLength(); i++) {
		Coordinates segment_coord = snake.getBodySegment(i);
		if (segment_coord.getX() == x && segment_coord.getY() == y)
			goto TryAgain;
	}

	food.setCoordinates(x, y);

	set_cursor_coordinates(food.getCoordinates());

	std::cout << "F" << std::flush;;
}

bool Field::isFoodEaten() {
	Coordinates snake_coord = snake.getHeadCoordinates();
	Coordinates food_coord = food.getCoordinates();
	if (snake_coord.getX() == food_coord.getX() && 
		snake_coord.getY() == food_coord.getY()) {
		snake.setActualLength(snake.getActualLength() + 1);
		score.setValue(score.getValue() + 1);
		return 1;
	}
	return 0;
}

void Field::clearField() {
	for (int i = 0; i < fieldSize.first * fieldSize.second; i++) {
		set_cursor_coordinates(
			i % fieldSize.first,
			i / fieldSize.first);
		std::cout << ' ' << std::flush;;
	}
}

void Field::delay(int time) {
	Delay(time);
}

void Field::placeCharacter(Coordinates coord, char chr) {
	set_cursor_coordinates(coord.getX(), coord.getY());
	std::cout << chr;
}

void Field::placeSnake() {
	snake.setHeadCoordinates(
		fieldSize.first / 4 + fieldSize.first / 4 % 2, 
		fieldSize.second / 2 + fieldSize.second / 2 % 2);
	Coordinates coord(snake.getHeadCoordinates());
	set_cursor_coordinates(coord);

	for(int i = 0; i < 4; i++) {
		set_cursor_coordinates(coord);
		std::cout << ' ' << std::flush;;
		delay(400);
		set_cursor_coordinates(coord);
	#if WEDGE_HEAD == 1
		std::cout << '>' << std::flush;
	#else 
		std::cout << '*' << std::flush;;	
	#endif
		delay(400);
	}
}

void Field::displaySnake() {
	Coordinates coord(snake.getHeadCoordinates());
	int dir = snake.getHeadDiraction();
	set_cursor_coordinates(coord);

	Coordinates segment_coord;

#if WEDGE_HEAD == 1
	if (dir == UP) {
		std::cout << '^' << std::flush;;
		segment_coord.setCoordinates(coord.getX(), coord.getY() + 1);
	}
	else if (dir == DOWN) {
		std::cout << 'v' << std::flush;;
		segment_coord.setCoordinates(coord.getX(), coord.getY() - 1);
	}
	else if (dir == LEFT) {
		std::cout << '<' << std::flush;;
		segment_coord.setCoordinates(coord.getX() + 2, coord.getY());
	}
	else if (dir == RIGHT) {
		std::cout << '>' << std::flush;;
		segment_coord.setCoordinates(coord.getX() - 2, coord.getY());
	}
#else
	std::cout << '*' << std::flush;;
	if (dir == UP) segment_coord.setCoordinates(coord.getX(), coord.getY() + 1);
	else if (dir == DOWN) segment_coord.setCoordinates(coord.getX(), coord.getY() - 1);
	else if (dir == LEFT) segment_coord.setCoordinates(coord.getX() + 2, coord.getY());
	else if (dir == RIGHT) segment_coord.setCoordinates(coord.getX() - 2, coord.getY());
#endif

	snake.addBodySegment(segment_coord);

	set_cursor_coordinates(segment_coord);
	std::cout << '*' << std::flush;;

	if (snake.getDisplayedLength() > snake.getActualLength() + 1) {
		set_cursor_coordinates(snake.deleteAndGetLastBodySegment());
		std::cout << ' ' << std::flush;;
	}
}

void Field::updateScore() {
	int score = this->score.getValue();
	set_cursor_coordinates(8, 1);
	if (score < 10) {
		std::cout << "00" << score << std::flush;;
	}
	else if (score < 100) {
		std::cout << "0" << score << std::flush;;
	}
	else {
		std::cout << score << std::flush;;
	}
}

void Field::killSnake() {
	int len = snake.getDisplayedLength();
	for (int i = 0; i < len; i++) {
		Coordinates coord = snake.getBodySegment(i);
		set_cursor_coordinates(coord);
		std::cout << ' ' << std::flush;;
		delay(100);
	}
}

bool Field::isSnakeKilled() {
	Coordinates head_coord = snake.getHeadCoordinates();
	if (head_coord.getX() < 3 || 
		head_coord.getX() > fieldSize.first - 4 || 
		head_coord.getY() < 4 || 
		head_coord.getY() > fieldSize.second - 3) {
		return 1;
	}
	for (int i = 0; i < snake.getDisplayedLength(); i++) {
		Coordinates coord = snake.getBodySegment(i);
		if (coord.getX() == head_coord.getX() && 
			coord.getY() == head_coord.getY()) {
			return 1;
		}
	}
	return 0;
}

void Field::theEnd() {
	clearField();
	set_cursor_coordinates(
		(fieldSize.first - 7) / 2, 
		fieldSize.second / 2);
	std::cout << "THE END" << std::flush;;
}

void Field::clearScreen() {
	ClearConsole();
}

void Field::startGame() {
	EnableNonBlockingInput();
	RemoveCursoreFromScreen();

	clearScreen();
	displayField();
	placeFoodRandomly();
	placeSnake();
	while (1) {
		snake.moveInHeadDirection();
		if (isSnakeKilled()) {
			killSnake();
			theEnd();
			DisableNonBlockingInput();
			ShowCursor();
			delay(500);
			clearScreen();
			return;
		}
		displaySnake();
		delay(150);
		if (isFoodEaten())
			placeFoodRandomly();
		updateScore();
	}
}