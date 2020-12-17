#pragma once
class TobogganMap {
public:
	TobogganMap(std::vector<std::string> map);

	void move(int r, int d);
	char getCurrentChar();
	int isTree();
	int onHill();
	void reset();

private:
	std::vector<std::string> map;
	int x;
	int y;
	int mapWidth;
	int mapHeight;
};