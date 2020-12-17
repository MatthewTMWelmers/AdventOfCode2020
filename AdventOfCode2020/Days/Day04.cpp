#include <string>
#include <vector>
#include <map>
#include <regex>

#include "../ClassHeaders/Passport.h"

std::vector<Passport> passports(std::vector<std::string> inputs) {
	std::vector<Passport> result;
	while (inputs.size() > 0) {
		result.push_back(Passport(&inputs));
	}

	return result;
}

int day4star1(std::vector<std::string> inputs) {
	std::vector<Passport> pass = passports(inputs);

	int valid = 0;
	for (Passport p : pass) {
		valid += p.hasAllFields();
	}

	return valid;
}
int day4star2(std::vector<std::string> inputs) {
	std::vector<Passport> pass = passports(inputs);

	int valid = 0;
	for (Passport p : pass) {
		valid += p.isValid();
	}

	return valid;
}