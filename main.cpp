#include "snake.h"

int main(int argc, char *argv[]) {
	if (argc > 2) {
		std::cout << "Wrong arguments number" << std::endl;
		return -1;
	}

	FIELD_SIZE fieldSize = NORMAL;

	if (argc == 2) {
		int argument = std::stoi(argv[1]);
		if (argument == 0) {
			fieldSize = SMALL;
		} 
		else if (argument == 1) {
			fieldSize = NORMAL;
		}
		else if (argument == 2) {
			fieldSize = LARGE;
		}
		else {
			std::cout << "Wrond argument" << std::endl;
			return -1;
		}
	} 
	Field field(fieldSize);
	field.start_game();
	return 0;
}
