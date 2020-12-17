#include <vector>
#include <string>
#include <iostream>

#include "../ClassHeaders/Seating.h"

int day11star1(std::vector<std::string> inputs) {
	Seating s(inputs, 3, 1);
	while (!s.isStable()) {
		s.evolve();
	}

	return s.occupied();
}

int day11star2(std::vector<std::string> inputs) {
	Seating s(inputs, 4, 0);
	while (!s.isStable()) {
		s.evolve();
	}

	return s.occupied();
}