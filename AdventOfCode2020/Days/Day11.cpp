#include <vector>
#include <string>
#include <iostream>

class Seating {
public:
	Seating(std::vector<std::string> inputs, int tolerance, int observeFloor) {
		board = inputs;
		width = board[0].length();
		height = board.size();
		changed = 1;
		this->tolerance = tolerance;
		this->observeFloor = observeFloor;
	}

	int isStable() {
		return 1 - changed;
	}

	void evolve() {
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

	char nextChar(char curr, int surround) {
		if (curr == 'L' && surround == 0) return '#';
		if (curr == '#' && surround > tolerance) return 'L';
		return curr;
	}

	int surroundFilled(int x, int y) {
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

	int directionFilled(int x, int y, int dx, int dy) {
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

	int occupied() {
		int occ = 0;
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				occ += board[i][j] == '#';
			}
		}

		return occ;
	}

private:
	std::vector<std::string> board;
	int width;
	int height;
	int changed;
	int observeFloor;
	int tolerance;
};

int day11star1(std::vector<std::string> inputs) {
	Seating s(inputs, 3, 1);
	while (!s.isStable()) {
		s.evolve();
	}

	return s.occupied();
}

int day11star2(std::vector<std::string> inputs) {
	Seating s(inputs, 4, 0);
	while (!s.isStable()) {
		s.evolve();
	}

	return s.occupied();
}