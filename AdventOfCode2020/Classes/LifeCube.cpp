#include <vector>
#include <string>
#include <tuple>
#include "../ClassHeaders/LifeSpace.h"

LifeCube::LifeCube(std::vector<std::string> init) {
	maxx = init[0].length();
	maxy = init.size();
	maxz = 1;

	std::vector<std::tuple<int, int, int>> newState;

	for (int x = 0; x < init.size(); x++) {
		for (int y = 0; y < init[x].length(); y++) {
			if (init[y][x] == '#') {
				newState.push_back(std::tuple<int, int, int>(x - 1, y - 1, -1));
			}
		}
	}

	persist(newState);
}

int LifeCube::activeCount() {
	int activeCt = 0;

	for (int i = 0; i < maxx; i++) {
		for (int j = 0; j < maxy; j++) {
			for (int k = 0; k < maxz; k++) {
				activeCt += active[i][j][k];
			}
		}
	}

	return activeCt;
}

void LifeCube::evolve() {
	std::vector<std::tuple<int, int, int>> newState;

	for (int x = -1; x <= maxx; x++) {
		for (int y = -1; y <= maxy; y++) {
			for (int z = -1; z <= maxz; z++) {
				int isActive = 0;
				if (x >= 0 && y >= 0 && z >= 0 && x < maxx && y < maxy && z < maxz) {
					isActive = active[x][y][z];
				}
				int surround = activeAround(x, y, z);

				if (isActive) {
					if (surround == 2 || surround == 3) {
						newState.push_back(std::tuple<int, int, int>(x, y, z));
					}
				}
				else {
					if (surround == 3) {
						newState.push_back(std::tuple<int, int, int>(x, y, z));
					}
				}
			}
		}
	}

	clearActive();

	maxx += 2;
	maxy += 2;
	maxz += 2;

	persist(newState);
}



void LifeCube::persist(std::vector<std::tuple<int, int, int>> state) {
	alloc();
	for (std::tuple<int, int, int> s : state) {
		int x = std::get<0>(s) + 1;
		int y = std::get<1>(s) + 1;
		int z = std::get<2>(s) + 1;

		active[x][y][z] = 1;
	}
}

int LifeCube::activeAround(int x, int y, int z) {
	int activeCt = 0;
	for (int i = x - 1; i <= x + 1; i++) {
		if (i < 0 || i >= maxx) {
			continue;
		}
		for (int j = y - 1; j <= y + 1; j++) {
			if (j < 0 || j >= maxy) {
				continue;
			}
			for (int k = z - 1; k <= z + 1; k++) {
				if (k < 0 || k >= maxz) {
					continue;
				}

				if (i != x || j != y || k != z) {
					activeCt += active[i][j][k];
				}
			}
		}
	}

	return activeCt;
}

void LifeCube::clearActive() {
	for (int i = 0; i < maxx; i++) {
		for (int j = 0; j < maxy; j++) {
			free(active[i][j]);
		}
		free(active[i]);
	}
	free(active);
}

void LifeCube::alloc() {
	active = (int***)malloc(maxx * sizeof(int**));
	for (int i = 0; i < maxx; i++) {
		active[i] = (int**)malloc(maxy * sizeof(int*));
		for (int j = 0; j < maxy; j++) {
			active[i][j] = (int*)malloc(maxy * sizeof(int));
			for (int k = 0; k < maxz; k++) {
				active[i][j][k] = 0;
			}
		}
	}
}