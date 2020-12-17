#include <vector>
#include <string>
#include "../ClassHeaders/TobogganMap.h"

int day3star1(std::vector<std::string> inputs) {
	TobogganMap map(inputs);

	int trees = 0;
	while (map.onHill()) {
		trees += map.isTree();
		map.move(3, 1);
	}

	return trees;
}

long long day3star2(std::vector<std::string> inputs) {
	TobogganMap map(inputs);

	long long trees11 = 0;
	while (map.onHill()) {
		trees11 += map.isTree();
		map.move(1, 1);
	}
	
	long long trees31 = 0;
	map.reset();
	while (map.onHill()) {
		trees31 += map.isTree();
		map.move(3, 1);
	}

	long long trees51 = 0;
	map.reset();
	while (map.onHill()) {
		trees51 += map.isTree();
		map.move(5, 1);
	}

	long long trees71 = 0;
	map.reset();
	while (map.onHill()) {
		trees71 += map.isTree();
		map.move(7, 1);
	}

	long long trees12 = 0;
	map.reset();
	while (map.onHill()) {
		trees12 += map.isTree();
		map.move(1, 2);
	}

	return trees11 * trees31 * trees51 * trees71 * trees12;
}