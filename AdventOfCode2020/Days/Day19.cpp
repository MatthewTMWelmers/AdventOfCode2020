#include <vector>
#include <string>
#include <map>
#include "../Core/Util.h"
#include "../ClassHeaders/MatchRule.h"

int day19star1(std::vector<std::string> inputs) {
	int ruleCount = indexOf<std::string>(inputs, "");
	int matched = 0;

	MatchRule::init(std::vector<std::string>(inputs.begin(), inputs.begin() + ruleCount));

	for (std::string s : std::vector<std::string>(inputs.begin() + ruleCount + 1, inputs.end())) {
		matched += MatchRule::matches0(s, 0);
	}

	return matched;
}

int day19star2(std::vector<std::string> inputs) {
	int ruleCount = indexOf<std::string>(inputs, "");
	int matched = 0;

	MatchRule::init(std::vector<std::string>(inputs.begin(), inputs.begin() + ruleCount));

	for (std::string s : std::vector<std::string>(inputs.begin() + ruleCount + 1, inputs.end())) {
		matched += MatchRule::matches0(s, 1);
	}

	return matched;
}