#include "game.h"

int main(int argc, char *argv[]) {
	if (argc > 2) {
		std::cout << "Wrong number of arguments" << std::endl;
		return -1;
	}

	FIELD_SIZE fieldSize = NORMAL;

	if (argc == 2) {
		switch(std::stoi(argv[1])) {
			case 0:
				fieldSize = SMALL;
				break;
			case 1:
				fieldSize = NORMAL;
				break;
			case 2:
				fieldSize = LARGE;
				break;
			default:
				std::cout << "Wrond argument" << std::endl;
				return -1;
		}
	} 
	Field field(fieldSize);
	field.startGame();
	return 0;
}
