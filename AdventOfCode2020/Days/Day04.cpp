#include <string>
#include <vector>
#include <map>
#include <regex>

class Passport {
public:
	void addLine(std::string line) {
		size_t prev_find = 0;
		size_t find;

		while ((find = line.find(" ", prev_find)) != std::string::npos) {
			addKV(line.substr(prev_find, find - prev_find));
			prev_find = find + 1;
		}

		addKV(line.substr(prev_find));
	}

	int isValid() {
		return values.count("byr") > 0
			&& values.count("iyr") > 0
			&& values.count("eyr") > 0
			&& values.count("hgt") > 0
			&& values.count("hcl") > 0
			&& values.count("ecl") > 0
			&& values.count("pid") > 0
			&& values.count("cid") >= 0;
	}

	std::string get(std::string key) {
		return values[key];
	}
private:
	std::map<std::string, std::string> values;

	void addKV(std::string kV) {
		size_t split = kV.find(":");
		values.insert_or_assign(kV.substr(0, split), kV.substr(split + 1));
	}
};

std::vector<Passport> passports(std::vector<std::string> inputs) {
	std::vector<Passport> result;
	Passport* p = new Passport();

	for (std::string line : inputs) {
		if (line.length() == 0) {
			result.push_back(*p);
			p = new Passport();
		}
		else {
			p->addLine(line);
		}
	}

	result.push_back(*p);
	return result;
}

int day4star1(std::vector<std::string> inputs) {
	std::vector<Passport> pass = passports(inputs);

	int valid = 0;
	for (Passport p : pass) {
		valid += p.isValid();
	}

	return valid;
}
int day4star2(std::vector<std::string> inputs) {
	std::vector<Passport> pass = passports(inputs);

	int valid = 0;
	for (Passport p : pass) {
		if (p.isValid()) {
			std::string byr = p.get("byr");
			if (!std::regex_match(byr, std::regex("\\d{4}"))) continue;
			if (stoi(byr) < 1920 || stoi(byr) > 2002) continue;

			std::string iyr = p.get("iyr");
			if (!std::regex_match(iyr, std::regex("\\d{4}"))) continue;
			if (stoi(iyr) < 2010 || stoi(iyr) > 2020) continue;

			std::string eyr = p.get("eyr");
			if (!std::regex_match(eyr, std::regex("\\d{4}"))) continue;
			if (stoi(eyr) < 2020 || stoi(eyr) > 2030) continue;

			std::string hgt = p.get("hgt");
			if (std::regex_match(hgt, std::regex("\\d{3}cm"))) {
				hgt = hgt.substr(0, 3);
				if (stoi(hgt) < 150 || stoi(hgt) > 193) continue;
			} else if (std::regex_match(hgt, std::regex("\\d{2}in"))) {
				hgt = hgt.substr(0, 2);
				if (stoi(hgt) < 59 || stoi(hgt) > 76) continue;
			} else continue;

			std::string hcl = p.get("hcl");
			if (!std::regex_match(hcl, std::regex("#[0-9a-f]{6}"))) continue;

			std::string ecl = p.get("ecl");
			if (!std::regex_match(ecl, std::regex("(amb)|(blu)|(brn)|(gry)|(grn)|(hzl)|(oth)"))) continue;

			std::string pid = p.get("pid");
			if (!std::regex_match(pid, std::regex("\\d{9}"))) continue;

			valid++;
		}

	}

	return valid;
}