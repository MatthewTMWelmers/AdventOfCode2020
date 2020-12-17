#include <vector>
#include <string>
#include <tuple>
#include <iostream>

class LifeCube {
public:
	LifeCube(std::vector<std::string> init) {
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

	int activeCount() {
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


	int activeAround(int x, int y, int z) {
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

	void clearActive() {
		for (int i = 0; i < maxx; i++) {
			for (int j = 0; j < maxy; j++) {
				free(active[i][j]);
			}
			free(active[i]);
		}
		free(active);
	}

	void alloc() {
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

	void evolve() {
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

	void persist(std::vector<std::tuple<int, int, int>> state) {
		alloc();
		for (std::tuple<int, int, int> s : state) {
			int x = std::get<0>(s) + 1;
			int y = std::get<1>(s) + 1;
			int z = std::get<2>(s) + 1;

			active[x][y][z] = 1;
		}
	}

	void print() {
		for (int k = 0; k < maxz; k++) {
			for (int j = 0; j < maxx; j++) {
				for (int i = 0; i < maxx; i++) {
					std::cout << (active[i][j][k] ? '#' : '.');
				}

				std::cout << std::endl;
			}

			std::cout << std::endl << std::endl;
		}
	}

private:
	int maxx, maxy, maxz;
	int*** active;
};

//copy of LifeCube but with 4d
class LifeCube4 {
public:
	LifeCube4(std::vector<std::string> init) {
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

	int activeCount() {
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


	int activeAround(int x, int y, int z, int w) {
		int activeCt = 0;
		for (int i = x-1; i <= x+1; i++) {
			if (i < 0 || i >= maxx) {
				continue;
			}
			for (int j = y-1; j <= y+1; j++) {
				if (j < 0 || j >= maxy) {
					continue;
				}
				for (int k = z-1; k <= z+1; k++) {
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

	void clearActive() {
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

	void alloc() {
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

	void evolve() {
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

	void persist(std::vector<std::tuple<int, int, int, int>> state) {
		alloc();
		for (std::tuple<int, int, int, int> s : state) {
			int x = std::get<0>(s) + 1;
			int y = std::get<1>(s) + 1;
			int z = std::get<2>(s) + 1;
			int w = std::get<3>(s) + 1;

			active[x][y][z][w] = 1;
		}
	}

private:
	int maxx, maxy, maxz, maxw;
	int**** active;
};


int day17star1(std::vector<std::string> inputs) {	
	LifeCube c(inputs);

	for (int i = 0; i < 6; i++) {
		c.evolve();
	}

	return c.activeCount();
}

int day17star2(std::vector<std::string> inputs) {
	LifeCube4 c(inputs);

	for (int i = 0; i < 6; i++) {
		c.evolve();
	}

	return c.activeCount();
}