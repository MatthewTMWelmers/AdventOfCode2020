#include <vector>
#include <string>
#include "../ClassHeaders/LifeSpace.h"

int day17star1(std::vector<std::string> inputs) {	
	LifeSpace* c = new LifeCube(inputs);

	for (int i = 0; i < 6; i++) {
		c->evolve();
	}

	int active = c->activeCount();
	delete c;
	return active;
}

int day17star2(std::vector<std::string> inputs) {
	LifeSpace* c = new LifeCube4(inputs);

	for (int i = 0; i < 6; i++) {
		c->evolve();
	}

	int active = c->activeCount();
	delete c;
	return active;
}