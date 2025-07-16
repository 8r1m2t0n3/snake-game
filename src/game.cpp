#include "game.h"

void Game::displayField() {
    std::pair<int, int> windowSize = this->window.getSize();
    for (int x = 2; x < windowSize.first - 2; x += 2) {
        this->window.displayCharacter(Coordinates(x, 3), '#');
        this->window.displayCharacter(Coordinates(x, windowSize.second - 2), '#');
	}
	for (int y = 1; y < windowSize.second - 4; y++) {
        this->window.displayCharacter(Coordinates(2, y + 2), '#');
        this->window.displayCharacter(Coordinates(windowSize.first - 3, y + 2), '#');
	}

    this->window.displayString(Coordinates(2, 1), "SCORE:000");
}

void Game::placeFoodRandomly() {
    std::pair<int, int> windowSize = this->window.getSize();
    TryAgain:
        int x = INDENT + rand() * time(0) % (static_cast<__int64_t>(windowSize.first) - 8);
        if (x % 2 == 1) x -= 1;
        int y = INDENT + rand() * time(0) % (static_cast<__int64_t>(windowSize.second) - 6);
    
        for (int i = 0; i < this->snake.getDisplayedLength(); i++) {
            Coordinates segmentCoord = this->snake.getBodySegment(i);
            if (segmentCoord.getX() == x && segmentCoord.getY() == y)
                goto TryAgain;
        }
    
        this->food.setCoordinates(x, y);
        this->window.displayCharacter(this->food.getCoordinates(), 'F');
}

bool Game::isFoodEaten() {
	Coordinates snakeCoord = this->snake.getHeadCoordinates();
	Coordinates foodCoord = this->food.getCoordinates();
	if (snakeCoord.getX() == foodCoord.getX() && 
		snakeCoord.getY() == foodCoord.getY()) {
		this->snake.setActualLength(this->snake.getActualLength() + 1);
		score.setValue(score.getValue() + 1);
		return 1;
	}
	return 0;
}

void Game::playSnakeAppearanceAnimation() {
    std::pair<int, int> windowSize = this->window.getSize();
	this->snake.setHeadCoordinates(
		windowSize.first / 4 + windowSize.first / 4 % 2, 
		windowSize.second / 2 + windowSize.second / 2 % 2);

	for(int i = 0; i < 4; i++) {
        this->window.displayCharacter(this->snake.getHeadCoordinates(), ' ');
		this->window.delay(400);
	#if WEDGE_HEAD == 1
        this->window.displayCharacter(this->snake.getHeadCoordinates(), '>');
	#else 
        this->window.displayCharacter(this->snake.getHeadCoordinates(), '*');
	#endif
		this->window.delay(400);
	}
}

void Game::displaySnake() {
	Coordinates snakeHeadCoord(this->snake.getHeadCoordinates());
	int dir = this->snake.getHeadDiraction();

	Coordinates segmentCoord;

#if WEDGE_HEAD == 1
    switch (dir) {
        case UP:
            this->window.displayCharacter(snakeHeadCoord, '^');
            segmentCoord.setCoordinates(snakeHeadCoord.getX(), snakeHeadCoord.getY() + 1);
            break;
        case DOWN:
            this->window.displayCharacter(snakeHeadCoord, 'v');
            segmentCoord.setCoordinates(snakeHeadCoord.getX(), snakeHeadCoord.getY() - 1);
            break;
        case LEFT:
            this->window.displayCharacter(snakeHeadCoord, '<');
            segmentCoord.setCoordinates(snakeHeadCoord.getX() + 2, snakeHeadCoord.getY());
            break;
        case RIGHT:
            this->window.displayCharacter(snakeHeadCoord, '>');
            segmentCoord.setCoordinates(snakeHeadCoord.getX() - 2, snakeHeadCoord.getY());
            break;
        default:
            break;
    }
#else
	std::cout << '*' << std::flush;;
	if (dir == UP) segmentCoord.setCoordinates(snakeHeadCoord.getX(), snakeHeadCoord.getY() + 1);
	else if (dir == DOWN) segmentCoord.setCoordinates(snakeHeadCoord.getX(), snakeHeadCoord.getY() - 1);
	else if (dir == LEFT) segmentCoord.setCoordinates(snakeHeadCoord.getX() + 2, snakeHeadCoord.getY());
	else if (dir == RIGHT) segmentCoord.setCoordinates(snakeHeadCoord.getX() - 2, snakeHeadCoord.getY());
#endif

	this->snake.addBodySegment(segmentCoord);
    this->window.displayCharacter(segmentCoord, '*');

	if (this->snake.getDisplayedLength() > this->snake.getActualLength() + 1) {
        this->window.displayCharacter(this->snake.deleteAndGetLastBodySegment(), ' ');
	}
}

void Game::displayScore() {
	int score = this->score.getValue();

	if (score < 10) {
        this->window.displayString(Coordinates(8, 1), "00" + std::to_string(score));
	}
	else if (score < 100) {
        this->window.displayString(Coordinates(8, 1), "0" + std::to_string(score));
	}
	else {
        this->window.displayString(Coordinates(8, 1), std::to_string(score));
	}
}

bool Game::isSnakeCollidingWithObstacle() {
    std::pair<int, int> windowSize = this->window.getSize();

	Coordinates snakeHeadCoord = snake.getHeadCoordinates();

	if (snakeHeadCoord.getX() < 3 || 
		snakeHeadCoord.getX() > windowSize.first - 4 || 
		snakeHeadCoord.getY() < 4 || 
		snakeHeadCoord.getY() > windowSize.second - 3) {
		return 1;
	}
	for (int i = 0; i < this->snake.getDisplayedLength(); i++) {
		Coordinates snakeBodySegmentCoord = this->snake.getBodySegment(i);
		if (snakeBodySegmentCoord.getX() == snakeHeadCoord.getX() && 
			snakeBodySegmentCoord.getY() == snakeHeadCoord.getY()) {
			return 1;
		}
	}
	return 0;
}

void Game::killSnake() {
	int len = this->snake.getDisplayedLength();
	for (int i = 0; i < len; i++) {
        this->window.displayCharacter(this->snake.getBodySegment(i), ' ');
		this->window.delay(100);
	}
}

void Game::clearField() {
    std::pair<int, int> windowSize = this->window.getSize();
	for (int i = 0; i < windowSize.first * windowSize.second; i++) {
		this->window.displayCharacter(Coordinates(i % windowSize.first, i / windowSize.first), ' ');
	}
}

void Game::displayGameEndLabel() {
    clearField();
    std::pair<int, int> windowSize = this->window.getSize();
    this->window.displayString(
        Coordinates(
            (windowSize.first - 7) / 2, 
            windowSize.second / 2),
        "THE END");
}

Game::Game(FIELD_SIZE fieldSize) {
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

    	this->window = Window(size);
    	this->score = Score();
	this->snake = Snake();
	this->food = Food();
}

void Game::start() {
	this->window.enableNonBlockingInput();
	this->window.hideCursore();
	this->window.clearScreen();

	displayField();
	placeFoodRandomly();
	playSnakeAppearanceAnimation();
	while (1) {
		snake.moveInHeadDirection();
		if (isSnakeCollidingWithObstacle()) {
			killSnake();
			displayGameEndLabel();
			this->window.disableNonBlockingInput();
			this->window.showCursor();
			this->window.delay(500);
			this->window.clearScreen();
			return;
		}
		displaySnake();
		this->window.delay(SNAKE_SPEED);
		if (isFoodEaten())
			placeFoodRandomly();
		displayScore();
	}
}
