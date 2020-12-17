#include "../ClassHeaders/Passport.h"
#include <regex>

Passport::Passport(std::vector<std::string>* init) {
	size_t i;
	for (i = 0; i < init->size() && (*init)[i].length() > 0; i++) {
		addLine((*init)[i]);
	}

	init->erase(init->begin(), init->begin() + i + (i < init->size()));
}

void Passport::addLine(std::string line) {
	size_t prev_find = 0;
	size_t find;

	while ((find = line.find(" ", prev_find)) != std::string::npos) {
		addKV(line.substr(prev_find, find - prev_find));
		prev_find = find + 1;
	}

	addKV(line.substr(prev_find));
}

int Passport::hasAllFields() {
	return values.count("byr") > 0
		&& values.count("iyr") > 0
		&& values.count("eyr") > 0
		&& values.count("hgt") > 0
		&& values.count("hcl") > 0
		&& values.count("ecl") > 0
		&& values.count("pid") > 0;
}

int Passport::isValid() {
	if (!hasAllFields()) {
		return 0;
	}

	std::string byr = values["byr"];
	if (!std::regex_match(byr, std::regex("\\d{4}"))) return 0;
	if (stoi(byr) < 1920 || stoi(byr) > 2002) return 0;

	std::string iyr = values["iyr"];
	if (!std::regex_match(iyr, std::regex("\\d{4}"))) return 0;
	if (stoi(iyr) < 2010 || stoi(iyr) > 2020) return 0;

	std::string eyr = values["eyr"];
	if (!std::regex_match(eyr, std::regex("\\d{4}"))) return 0;
	if (stoi(eyr) < 2020 || stoi(eyr) > 2030) return 0;

	std::string hgt = values["hgt"];
	if (std::regex_match(hgt, std::regex("\\d{3}cm"))) {
		hgt = hgt.substr(0, 3);
		if (stoi(hgt) < 150 || stoi(hgt) > 193) return 0;
	}
	else if (std::regex_match(hgt, std::regex("\\d{2}in"))) {
		hgt = hgt.substr(0, 2);
		if (stoi(hgt) < 59 || stoi(hgt) > 76) return 0;
	}
	else return 0;

	std::string hcl = values["hcl"];
	if (!std::regex_match(hcl, std::regex("#[0-9a-f]{6}"))) return 0;

	std::string ecl = values["ecl"];
	if (!std::regex_match(ecl, std::regex("(amb)|(blu)|(brn)|(gry)|(grn)|(hzl)|(oth)"))) return 0;

	std::string pid = values["pid"];
	if (!std::regex_match(pid, std::regex("\\d{9}"))) return 0;

	return 1;
}

void Passport::addKV(std::string kV) {
	size_t split = kV.find(":");
	values.insert_or_assign(kV.substr(0, split), kV.substr(split + 1));
}
