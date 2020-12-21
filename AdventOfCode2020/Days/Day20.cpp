#include <vector>
#include <string>
#include <iostream>

#include "../ClassHeaders/PictureTile.h"

long long day20star1(std::vector<std::string> inputs) {
	PictureTile::init(inputs);

	long long corners = 1;
	for (PictureTile* tile : PictureTile::allTiles()) {
		if (tile->isCorner()) {
			corners *= tile->tileNum;
		}
	}

	PictureTile::cleanup();
	return corners;
}

long long day20star2(std::vector<std::string> inputs) {
	PictureTile::init(inputs);

	int rough = 0;
	for (std::string line : PictureTile::picture(PictureTile::allTiles())) {
		for (char c : line) {
			rough += c == '#' ? 1 : 0;
		}
	}

	PictureTile::cleanup();
	return rough;
}