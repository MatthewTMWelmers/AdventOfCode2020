#include <vector>
#include <string>

#include "../ClassHeaders/Seating.h"

Seating::Seating(std::vector<std::string> inputs, int tolerance, int observeFloor) {
	board = inputs;
	width = board[0].length();
	height = board.size();
	changed = 1;
	this->tolerance = tolerance;
	this->observeFloor = observeFloor;
}

int Seating::isStable() {
	return 1 - changed;
}

void Seating::evolve() {
	std::vector<std::string> nextBoard(board);

	changed = 0;
	for (int j = 0; j < width; j++) {
		for (int i = 0; i < height; i++) {
			char curr = board[i][j];
			char next = nextChar(curr, surroundFilled(i, j));

			if (curr != next) {
				changed = 1;
				nextBoard[i][j] = next;
			}
		}
	}

	board = nextBoard;
}

char Seating::nextChar(char curr, int surround) {
	if (curr == 'L' && surround == 0) return '#';
	if (curr == '#' && surround > tolerance) return 'L';
	return curr;
}

int Seating::surroundFilled(int x, int y) {
	int filled = 0;
	filled += directionFilled(x, y, -1, -1);
	filled += directionFilled(x, y, -1, 0);
	filled += directionFilled(x, y, -1, 1);
	filled += directionFilled(x, y, 0, -1);
	filled += directionFilled(x, y, 0, 1);
	filled += directionFilled(x, y, 1, -1);
	filled += directionFilled(x, y, 1, 0);
	filled += directionFilled(x, y, 1, 1);

	return filled;
}

int Seating::directionFilled(int x, int y, int dx, int dy) {
	x += dx;
	y += dy;

	while (x >= 0 && x < height && y >= 0 && y < width) {
		char chair = board[x][y];
		if (observeFloor || chair != '.') {
			return chair == '#';
		}

		x += dx;
		y += dy;
	}

	return 0;
}

int Seating::occupied() {
	int occ = 0;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			occ += board[i][j] == '#';
		}
	}

	return occ;
}