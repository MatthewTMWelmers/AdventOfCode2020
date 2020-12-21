#pragma once

class PictureTile {
public:
	long long tileNum;
	std::vector<std::string> tile;

	PictureTile(std::vector<std::string> inputs, long long tileNum);
	std::vector<long long> getEdges();
	std::vector<PictureTile*> partners();

	int isCorner() { return partners().size() == 2; }
	int isEdge() { return partners().size() == 3; }
	int isMiddle() { return partners().size() == 4; }

	static std::vector<PictureTile*> allTiles() { return tiles; }
	static std::vector<std::string> picture(std::vector<PictureTile*> tiles);
	static void init(std::vector<std::string> inputs);
	static void cleanup();

private:
	std::vector<PictureTile*> partnerTiles;
	std::vector<long long> edges;

	static std::vector<PictureTile*> tiles;
};