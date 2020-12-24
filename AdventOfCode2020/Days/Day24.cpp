#include <vector>
#include <string>
#include <set>
#include <regex>

std::set<std::pair<int, int>> init(std::vector<std::string> inputs) {
	int x, y;
	std::regex inputRegex("[ns]?[ew]");
	std::smatch smatch;
	std::set<std::pair<int, int>> tiles;
	for (std::string input : inputs) {
		x = y = 0;
		while (std::regex_search(input, smatch, inputRegex)) {
			std::string dir = smatch.str(0);
			if (dir == "e") {
				x += 2;
			}
			if (dir == "w") {
				x -= 2;
			}
			if (dir == "ne") {
				y++;
				x++;
			}
			if (dir == "nw") {
				y++;
				x--;
			}
			if (dir == "se") {
				y--;
				x++;
			}
			if (dir == "sw") {
				y--;
				x--;
			}
			input = smatch.suffix();
		}
		std::pair<int, int> tile(x, y);
		if (tiles.count(tile)) {
			tiles.erase(tile);
		}
		else {
			tiles.insert(tile);
		}
	}

	return tiles;
}

std::set<std::pair<int, int>> iter(std::set<std::pair<int, int>> tiles, int* minx, int* miny, int* maxx, int* maxy) {
	std::set<std::pair<int, int>> tilesCpy;
	for (int x = *minx - 1; x <= *maxx + 1; x++) {
		for (int y = *miny - 1; y <= *maxy + 1; y++) {
			if ((x + y + 1) % 2) {
				std::pair<int, int> tile(x, y);
				int black = tiles.count(tile);
				int wBlack = tiles.count(std::pair<int, int>(x - 2, y));
				int eBlack = tiles.count(std::pair<int, int>(x + 2, y));
				int nwBlack = tiles.count(std::pair<int, int>(x - 1, y + 1));
				int neBlack = tiles.count(std::pair<int, int>(x + 1, y + 1));
				int swBlack = tiles.count(std::pair<int, int>(x - 1, y - 1));
				int seBlack = tiles.count(std::pair<int, int>(x + 1, y - 1));

				int surr = wBlack + eBlack + nwBlack + neBlack + swBlack + seBlack;
				if (surr == 2 || (surr == 1 && black)) {
					tilesCpy.insert(std::pair<int, int>(x, y));

					if (x < *minx) *minx = x;
					if (x > *maxx) *maxx = x;
					if (y < *miny) *miny = y;
					if (y > *maxy) *maxy = y;
				}
			}
		}
	}
	return tilesCpy;
}

int day24star1(std::vector<std::string> inputs) {
	std::set<std::pair<int, int>> tiles = init(inputs);
	return tiles.size();
}

int day24star2(std::vector<std::string> inputs) {
	int minx, miny, maxx, maxy;
	minx = miny = maxx = maxy = 0;

	std::set<std::pair<int, int>> tiles = init(inputs);
	for (std::pair<int, int> tile : tiles) {
		if (tile.first < minx) minx = tile.first;
		if (tile.first > maxx) maxx = tile.first;
		if (tile.second < miny) miny = tile.second;
		if (tile.second > maxy) maxy = tile.second;
	}

	for(size_t i = 0; i < 100; i++)
	{
		tiles = iter(tiles, &minx, &miny, &maxx, &maxy);
	}

	return tiles.size();
}