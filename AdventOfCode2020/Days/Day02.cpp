#include <vector>
#include <string>
#include <regex>

struct PasswordRule {
	PasswordRule(std::string rule) {
		std::regex regex("^(\\d+)-(\\d+) (\\w): (\\w+)$");
		std::smatch match;
		std::regex_match(rule, match, regex);
		min = stoi(match.str(1));
		max = stoi(match.str(2));
		c = match.str(3)[0];
		pw = match.str(4);
	}

	size_t min;
	size_t max;
	char c;
	std::string pw;
};

int day2star1(std::vector<std::string> inputs) {
	int result = 0;

	for (std::string pass : inputs) {
		PasswordRule rule(pass);

		size_t count = 0;
		for (char c : rule.pw) {
			if (rule.c == c) {
				count++;
			}
		}
		result += (count >= rule.min) && (count <= rule.max);
	}

	return result;
}

int day2star2(std::vector<std::string> inputs) {
	int result = 0;

	for (std::string pass : inputs) {
		PasswordRule rule(pass);

		result += (rule.pw[rule.min - 1] == rule.c) ^ (rule.pw[rule.max - 1] == rule.c);
	}

	return result;
}
