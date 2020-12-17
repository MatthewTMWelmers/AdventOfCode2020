#include <string>
#include <regex>
#include <map>

#include "../ClassHeaders/BagRule.h"

BagRule::BagRule(std::string name) {
	this->name = name;
	this->mustContainCount = -1;
}

void BagRule::addContents(std::string contentsString) {
	if (contentsString == "no other bag") {
		mustContainCount = 0;
		return;
	}

	std::regex regex("(\\d+) (\\D+) bags?");
	std::smatch match;

	while (std::regex_search(contentsString, match, regex)) {
		contentCounts.push_back(std::pair<std::string, int>(match.str(2), stoi(match.str(1))));
		contentsString = match.suffix();
	}
}

int BagRule::canContain(std::string contained) {
	if (nestedContainCache.count(contained) > 0) {
		return nestedContainCache[contained];
	}

	for (std::pair<std::string, BagRule*> rule : contents) {
		if (rule.second->name == contained || rule.second->canContain(contained)) {
			nestedContainCache[contained] = 1;
			return 1;
		}
	}

	nestedContainCache[contained] = 0;
	return 0;
}

int BagRule::mustContain() {
	if (mustContainCount >= 0) {
		return mustContainCount;
	}

	int mustContainCount = 0;
	for (std::pair<std::string, int> in : contentCounts) {
		mustContainCount += in.second * (contents[in.first]->mustContain() + 1);
	}

	return mustContainCount;
}

void BagRule::updatePointers(std::map<std::string, BagRule*> rules) {
	for (std::pair<std::string, int> content : contentCounts) {
		contents.insert_or_assign(content.first, rules[content.first]);
	}
}