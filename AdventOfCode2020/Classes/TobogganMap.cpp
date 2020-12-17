#include <vector>
#include <string>
#include "../ClassHeaders/TobogganMap.h"

TobogganMap::TobogganMap(std::vector<std::string> map) {
	this->map = map;
	this->x = 0;
	this->y = 0;
	this->mapWidth = map[0].length();
	this->mapHeight = map.size();
}

void TobogganMap::move(int r, int d) {
	x = (x + r) % mapWidth;
	y = y + d;
}

char TobogganMap::getCurrentChar() {
	return map[y][x];
}

int TobogganMap::isTree() {
	return getCurrentChar() == '#';
}

int TobogganMap::onHill() {
	return y < mapHeight;
}

void TobogganMap::reset() {
	x = 0;
	y = 0;
}