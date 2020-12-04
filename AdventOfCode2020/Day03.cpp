#include <vector>
#include <string>

class TobogganMap {
private:
	std::vector<std::string> map;
	int x;
	int y;
	int mapWidth;
	int mapHeight;
public:
	TobogganMap(std::vector<std::string> map) {
		this->map = map;
		this->x = 0;
		this->y = 0;
		this->mapWidth = map[0].length();
		this->mapHeight = map.size();
	}

	void move(int r, int d) {
		x = (x + r) % mapWidth;
		y = y + d;
	}

	char getCurrentChar() {
		return map[y][x];
	}

	int isTree() {
		return getCurrentChar() == '#';
	}

	int onHill() {
		return y < mapHeight;
	}

	void reset() {
		x = 0;
		y = 0;
	}
};

int day3star1(std::vector<std::string> inputs) {
	TobogganMap* map = new TobogganMap(inputs);

	int trees = 0;
	while (map->onHill()) {
		trees += map->isTree();
		map->move(3, 1);
	}

	delete map;

	return trees;
}

long long day3star2(std::vector<std::string> inputs) {
	TobogganMap* map = new TobogganMap(inputs);

	long long trees11 = 0;
	while (map->onHill()) {
		trees11 += map->isTree();
		map->move(1, 1);
	}
	
	long long trees31 = 0;
	map->reset();
	while (map->onHill()) {
		trees31 += map->isTree();
		map->move(3, 1);
	}

	long long trees51 = 0;
	map->reset();
	while (map->onHill()) {
		trees51 += map->isTree();
		map->move(5, 1);
	}

	long long trees71 = 0;
	map->reset();
	while (map->onHill()) {
		trees71 += map->isTree();
		map->move(7, 1);
	}

	long long trees12 = 0;
	map->reset();
	while (map->onHill()) {
		trees12 += map->isTree();
		map->move(1, 2);
	}
	delete map;

	return trees11 * trees31 * trees51 * trees71 * trees12;
}