#include <vector>
#include <string>
#include <map>
#include <regex>


class BagRule {
public:
	BagRule(std::string name) {
		this->name = name;
		this->mustContainCount = -1;
	}

	void addContents(std::string contentsString) {
		if (contentsString == "no other bag") {
			mustContainCount = 0;
			return;
		}

		std::regex regex("(\\d+) (\\D+) bags?");
		std::smatch match;

		while (std::regex_search(contentsString, match, regex)) {
			contents.push_back(std::pair<std::string, int>(match.str(2), stoi(match.str(1))));
			contentsString = match.suffix();
		}
	}

	int canContain(std::string contained) {
		if (_canContain.count(contained) > 0) {
			return _canContain[contained];
		}

		for (std::pair<std::string, BagRule*> rule : _contents) {
			if (rule.second->name == contained || rule.second->canContain(contained)) {
				_canContain[contained] = 1;
				return 1;
			}
		}

		_canContain[contained] = 0;
		return 0;
	}

	int mustContain() {
		if (mustContainCount >= 0) {
			return mustContainCount;
		}

		mustContainCount = 0;
		for (std::pair<std::string, int> in : contents) {
			mustContainCount += in.second * (_contents[in.first]->mustContain() + 1);
		}

		return mustContainCount;
	}

	void updatePointers(std::map<std::string, BagRule*> rules) {
		for (std::pair<std::string, int> content : contents) {
			_contents.insert_or_assign(content.first, rules[content.first]);
		}
	}

	std::string name;
	std::vector<std::pair<std::string, int>> contents;

private:
	std::map<std::string, BagRule*> _contents;
	std::map<std::string, int> _canContain;
	int mustContainCount;
};

class BagRules {
public: 
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