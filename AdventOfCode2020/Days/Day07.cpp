#include <vector>
#include <string>
#include <map>
#include <regex>

#include "../ClassHeaders/BagRule.h"

struct BagRules { 
	BagRules(std::vector<std::string> inputs) {
		for (std::string rule : inputs) {
			std::regex regex("^(.*) bags contain (.*bag)s?\\.$");
			std::smatch match;
			std::regex_match(rule, match, regex);

			BagRule* bagRule = new BagRule(match.str(1));
			bagRule->addContents(match.str(2));

			rules.insert_or_assign(match.str(1), bagRule);
		}

		for (std::pair<std::string, BagRule*> kv : rules) {
			kv.second->updatePointers(rules);
		}
	}

	~BagRules() {
		for (std::pair<std::string, BagRule*> kv : rules) {
			delete kv.second;
		}
	}

	std::map<std::string, BagRule*> rules;
};

int day7star1(std::vector<std::string> inputs) {
	BagRules rules(inputs);

	int canContainShinyGold = 0;
	for (std::pair<std::string, BagRule*> rule : rules.rules) {
		canContainShinyGold += rule.second->canContain("shiny gold");
	}

	return canContainShinyGold;
}

int day7star2(std::vector<std::string> inputs) {
	BagRules rules(inputs);
	return rules.rules["shiny gold"]->mustContain();
}