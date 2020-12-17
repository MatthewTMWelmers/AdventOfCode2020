#include <vector>
#include <string>
#include <regex>
#include <set>

#include "../ClassHeaders/Program.h"

int day8star1(std::vector<std::string> inputs) {
	Program p(inputs);
	return p.run();	
}

int day8star2(std::vector<std::string> inputs) {
	Program p(inputs);

	if (p.tryRepair()) {
		return p.run();
	}

	return 0;
}