#include <vector>
#include <string>
#include <tuple>
#include "../ClassHeaders/LifeSpace.h"

LifeCube4::LifeCube4(std::vector<std::string> init) {
	maxx = init[0].length();
	maxy = init.size();
	maxz = 1;
	maxw = 1;

	std::vector<std::tuple<int, int, int, int>> newState;

	for (int x = 0; x < init.size(); x++) {
		for (int y = 0; y < init[x].length(); y++) {
			if (init[y][x] == '#') {
				newState.push_back(std::tuple<int, int, int, int>(x - 1, y - 1, -1, -1));
			}
		}
	}

	persist(newState);
}

int LifeCube4::activeCount() {
	int activeCt = 0;

	for (int i = 0; i < maxx; i++) {
		for (int j = 0; j < maxy; j++) {
			for (int k = 0; k < maxz; k++) {
				for (int l = 0; l < maxw; l++) {
					activeCt += active[i][j][k][l];
				}
			}
		}
	}

	return activeCt;
}


void LifeCube4::evolve() {
	std::vector<std::tuple<int, int, int, int>> newState;

	for (int x = -1; x <= maxx; x++) {
		for (int y = -1; y <= maxy; y++) {
			for (int z = -1; z <= maxz; z++) {
				for (int w = -1; w <= maxw; w++) {
					int isActive = 0;
					if (x >= 0 && y >= 0 && z >= 0 && w >= 0 && x < maxx && y < maxy && z < maxz && w < maxw) {
						isActive = active[x][y][z][w];
					}
					int surround = activeAround(x, y, z, w);

					if (isActive) {
						if (surround == 2 || surround == 3) {
							newState.push_back(std::tuple<int, int, int, int>(x, y, z, w));
						}
					}
					else {
						if (surround == 3) {
							newState.push_back(std::tuple<int, int, int, int>(x, y, z, w));
						}
					}
				}
			}
		}
	}

	clearActive();

	maxx += 2;
	maxy += 2;
	maxz += 2;
	maxw += 2;

	persist(newState);
}

void LifeCube4::persist(std::vector<std::tuple<int, int, int, int>> state) {
	alloc();
	for (std::tuple<int, int, int, int> s : state) {
		int x = std::get<0>(s) + 1;
		int y = std::get<1>(s) + 1;
		int z = std::get<2>(s) + 1;
		int w = std::get<3>(s) + 1;

		active[x][y][z][w] = 1;
	}
}

int LifeCube4::activeAround(int x, int y, int z, int w) {
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

				for (int l = w - 1; l <= w + 1; l++) {
					if (l < 0 || l >= maxw) {
						continue;
					}

					if (i != x || j != y || k != z || l != w) {
						activeCt += active[i][j][k][l];
					}
				}
			}
		}
	}

	return activeCt;
}

void LifeCube4::clearActive() {
	for (int i = 0; i < maxx; i++) {
		for (int j = 0; j < maxy; j++) {
			for (int k = 0; k < maxz; k++) {
				free(active[i][j][k]);
			}
			free(active[i][j]);
		}
		free(active[i]);
	}
	free(active);
}

void LifeCube4::alloc() {
	active = (int****)malloc(maxx * sizeof(int***));
	for (int i = 0; i < maxx; i++) {
		active[i] = (int***)malloc(maxy * sizeof(int**));
		for (int j = 0; j < maxy; j++) {
			active[i][j] = (int**)malloc(maxz * sizeof(int));
			for (int k = 0; k < maxz; k++) {
				active[i][j][k] = (int*)malloc(maxw * sizeof(int));
				for (int l = 0; l < maxw; l++) {
					active[i][j][k][l] = 0;
				}
			}
		}
	}
}