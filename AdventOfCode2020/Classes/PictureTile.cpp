#include <vector>
#include <string>
#include <cmath>

#include "../ClassHeaders/PictureTile.h"
#include "../Core/Util.h"

std::vector<PictureTile*> PictureTile::tiles;

void PictureTile::init(std::vector<std::string> inputs) {
	int tileSize = indexOf<std::string>(inputs, "") - 1;

	for (size_t i = 0; i < inputs.size(); i += tileSize + 2) {
		long long tileNum = stoll(inputs[i].substr(5, 4));
		std::vector<std::string> tileInputs(inputs.begin() + i + 1, inputs.begin() + i + tileSize + 1);
		tiles.push_back(new PictureTile(tileInputs, tileNum));
	}
}

void PictureTile::cleanup() {
	for (PictureTile* tile : tiles) {
		delete tile;
	}

	tiles.clear();
}

PictureTile::PictureTile(std::vector<std::string> inputs, long long tileNum) {
	this->tileNum = tileNum;
	this->tile = inputs;
}

std::vector<PictureTile*> PictureTile::partners() {
	if (partnerTiles.empty()) {
		std::vector<PictureTile*> partnerVec;
		for (PictureTile* tile : tiles) {
			if (tile == this) {
				continue;
			}

			int matches = 0;
			for (long long edge : getEdges()) {
				for (long long partnerEdge : tile->getEdges()) {
					if (edge == partnerEdge) {
						matches = 1;
					}
				}
			}

			if (matches) partnerVec.push_back(tile);
		}

		for (PictureTile* t : partnerVec) {
			partnerTiles.push_back(t);
		}
	}

	return partnerTiles;
}

std::vector<long long> PictureTile::getEdges() {
	if (edges.empty()) {
		std::string topEdge = "";
		std::string leftEdge = "";
		std::string rightEdge = "";
		std::string bottomEdge = "";

		for (size_t i = 0; i < tile.size(); i++) {
			for (size_t j = 0; j < tile[i].length(); j++) {
				if (i == 0) {
					topEdge += std::to_string(tile[i][j] == '#' ? 1 : 0);
				}
				if (i == tile.size() - 1) {
					bottomEdge += std::to_string(tile[i][j] == '#' ? 1 : 0);
				}
				if (j == 0) {
					leftEdge += std::to_string(tile[i][j] == '#' ? 1 : 0);
				}
				if (j == tile.size() - 1) {
					rightEdge += std::to_string(tile[i][j] == '#' ? 1 : 0);
				}
			}
		}

		std::vector<long long> edgeVec;
		edgeVec.push_back(std::stoll(topEdge, NULL, 2));
		edgeVec.push_back(std::stoll(leftEdge, NULL, 2));
		edgeVec.push_back(std::stoll(rightEdge, NULL, 2));
		edgeVec.push_back(std::stoll(bottomEdge, NULL, 2));

		std::reverse(topEdge.begin(), topEdge.end());
		std::reverse(leftEdge.begin(), leftEdge.end());
		std::reverse(rightEdge.begin(), rightEdge.end());
		std::reverse(bottomEdge.begin(), bottomEdge.end());

		edgeVec.push_back(std::stoll(topEdge, NULL, 2));
		edgeVec.push_back(std::stoll(leftEdge, NULL, 2));
		edgeVec.push_back(std::stoll(rightEdge, NULL, 2));
		edgeVec.push_back(std::stoll(bottomEdge, NULL, 2));

		edges = edgeVec;
	}

	return edges;
}

PictureTile* nextEdge(PictureTile* match, std::vector<PictureTile*>* tiles) {
	for (size_t i = 0; i < tiles->size(); i++) {
		for (PictureTile* partner : match->partners()) {
			if ((*tiles)[i] == partner) {
				tiles->erase(tiles->begin() + i);
				return partner;
			}
		}
	}

	return NULL;
}

PictureTile* nextTile(PictureTile* match1, PictureTile* match2, std::vector<PictureTile*>* tiles) {
	for (size_t i = 0; i < tiles->size(); i++) {
		for (PictureTile* partner1 : match1->partners()) {
			for (PictureTile* partner2 : match2->partners()) {
				if (partner1 == partner2 && (*tiles)[i] == partner1) {
					tiles->erase(tiles->begin() + i);
					return partner1;
				}
			}
		}
	}

	return NULL;
}

std::vector<std::vector<PictureTile*>> tileOrientation(std::vector<PictureTile*> tiles) {
	std::vector<PictureTile*> tileCopy(tiles);

	std::vector<std::vector<PictureTile*>> tileMap;
	size_t edgeSize = static_cast<int>(std::sqrt(tiles.size()));


	for (size_t i = 0; i < edgeSize; i++) {
		for (size_t j = 0; j < edgeSize; j++) {
			if (j == 0) {
				tileMap.push_back(std::vector<PictureTile*>());
			}

			if (i == 0 && j == 0) {
				for (size_t k = 0; k < tileCopy.size(); k++) {
					if (tileCopy[k]->isCorner()) {
						tileMap[0].push_back(tileCopy[k]);
						tileCopy.erase(tileCopy.begin() + k);
						break;
					}
				}
			} else if (i == 0) {
				for (PictureTile* t : tileMap[0][j - 1]->partners()) {
					if ((t->isEdge() || t->isCorner()) && indexOf(tileCopy, t) > -1) {
						tileMap[0].push_back(t);
						tileCopy.erase(tileCopy.begin() + indexOf(tileCopy, t));
						break;
					}
				}
			} else {
				for (PictureTile* t : tileMap[i - 1][j]->partners()) {
					if (indexOf(tileCopy, t) > -1) {
						tileMap[i].push_back(t);
						tileCopy.erase(tileCopy.begin() + indexOf(tileCopy, t));
						break;
					}
				}
			}
		}
	}

	return tileMap;
}

int orientTop(PictureTile* tile, long long top) {
	if (parseStringAsBinary(tile->tile[0], '#') == top) return 1;

	rotate(&(tile->tile));
	if (parseStringAsBinary(tile->tile[0], '#') == top) return 1;

	rotate(&(tile->tile));
	if (parseStringAsBinary(tile->tile[0], '#') == top) return 1;

	rotate(&(tile->tile));
	if (parseStringAsBinary(tile->tile[0], '#') == top) return 1;

	std::reverse(tile->tile.begin(), tile->tile.end());
	if (parseStringAsBinary(tile->tile[0], '#') == top) return 1;

	rotate(&(tile->tile));
	if (parseStringAsBinary(tile->tile[0], '#') == top) return 1;

	rotate(&(tile->tile));
	if (parseStringAsBinary(tile->tile[0], '#') == top) return 1;

	rotate(&(tile->tile));
	if (parseStringAsBinary(tile->tile[0], '#') == top) return 1;

	return 0;
}

void orientLeft(PictureTile* tile, long long left) {
	orientTop(tile, left);
	std::reverse(tile->tile.begin(), tile->tile.end());
	rotate(&(tile->tile));
}

void orientRight(PictureTile* tile, long long left) {
	orientTop(tile, left);
	rotate(&(tile->tile));
}

void orientAll(std::vector<std::vector<PictureTile*>> tiles) {
	for (long long i : tiles[0][0]->getEdges()) {
		for (long long j : tiles[0][1]->getEdges()) {
			if (i == j) {
				orientRight(tiles[0][0], i);
			}
		}
	}

	if (!orientTop(tiles[1][0], parseStringAsBinary(tiles[0][0]->tile.back(), '#'))) {
		std::reverse(tiles[0][0]->tile.begin(), tiles[0][0]->tile.end());
	}

	for (size_t i = 1; i < tiles[0].size(); i++) {
		ccRotate(&(tiles[0][i-1]->tile));
		long long target = parseStringAsBinary(tiles[0][i-1]->tile[0], '#');
		rotate(&(tiles[0][i-1]->tile));
		orientLeft(tiles[0][i], target);
	}

	for (size_t i = 1; i < tiles.size(); i++) {
		for (size_t j = 0; j < tiles[i].size(); j++) {
			orientTop(tiles[i][j], parseStringAsBinary(tiles[i-1][j]->tile.back(), '#'));
		}
	}
}

int findSeaMonsters(std::vector<std::string>* pic) {
	int seaMonsters = 0;

	for (size_t i = 0; i < (*pic).size() - 2; i++) {
		for (size_t j = 0; j < (*pic)[i].size() - 19; j++) {
			if ((*pic)[i][j + 18] != '#') continue;
			if ((*pic)[i + 1][j + 0] != '#') continue;
			if ((*pic)[i + 1][j + 5] != '#') continue;
			if ((*pic)[i + 1][j + 6] != '#') continue;
			if ((*pic)[i + 1][j + 11] != '#') continue;
			if ((*pic)[i + 1][j + 12] != '#') continue;
			if ((*pic)[i + 1][j + 17] != '#') continue;
			if ((*pic)[i + 1][j + 18] != '#') continue;
			if ((*pic)[i + 1][j + 19] != '#') continue;
			if ((*pic)[i + 2][j + 1] != '#') continue;
			if ((*pic)[i + 2][j + 4] != '#') continue;
			if ((*pic)[i + 2][j + 7] != '#') continue;
			if ((*pic)[i + 2][j + 10] != '#') continue;
			if ((*pic)[i + 2][j + 13] != '#') continue;
			if ((*pic)[i + 2][j + 16] != '#') continue;

			seaMonsters++;
			(*pic)[i][j + 18] = 'O';
			(*pic)[i + 1][j + 0] = 'O';
			(*pic)[i + 1][j + 5] = 'O';
			(*pic)[i + 1][j + 6] = 'O';
			(*pic)[i + 1][j + 11] = 'O';
			(*pic)[i + 1][j + 12] = 'O';
			(*pic)[i + 1][j + 17] = 'O';
			(*pic)[i + 1][j + 18] = 'O';
			(*pic)[i + 1][j + 19] = 'O';
			(*pic)[i + 2][j + 1] = 'O';
			(*pic)[i + 2][j + 4] = 'O';
			(*pic)[i + 2][j + 7] = 'O';
			(*pic)[i + 2][j + 10] = 'O';
			(*pic)[i + 2][j + 13] = 'O';
			(*pic)[i + 2][j + 16] = 'O';
		}
	}

	return seaMonsters;
}

std::vector<std::string> PictureTile::picture(std::vector<PictureTile*> tiles) {
	std::vector<std::string> pic;
	size_t tileSize = tiles[0]->tile[0].length();
	std::vector<std::vector<PictureTile*>> orientation = tileOrientation(tiles);
	orientAll(orientation);

	for (size_t i = 0; i < orientation.size(); i++) {
		for (size_t j = 1; j < tileSize - 1; j++) {
			pic.push_back("");
			for (size_t k = 0; k < orientation[i].size(); k++) {
				pic.back() += orientation[i][k]->tile[j].substr(1, tileSize-2);
			}
		}
	}


	int seaMonsters;
	if (seaMonsters = findSeaMonsters(&pic)) return pic;

	rotate(&pic);
	if (seaMonsters = findSeaMonsters(&pic)) return pic;

	rotate(&pic);
	if (seaMonsters = findSeaMonsters(&pic)) return pic;

	rotate(&pic);
	if (seaMonsters = findSeaMonsters(&pic)) return pic;

	std::reverse(pic.begin(), pic.end());
	if (seaMonsters = findSeaMonsters(&pic)) return pic;

	rotate(&pic);
	if (seaMonsters = findSeaMonsters(&pic)) return pic;

	rotate(&pic);
	if (seaMonsters = findSeaMonsters(&pic)) return pic;

	rotate(&pic);
	if (seaMonsters = findSeaMonsters(&pic)) return pic;
}