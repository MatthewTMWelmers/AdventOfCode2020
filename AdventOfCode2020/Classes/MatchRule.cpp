#include <vector>
#include <string>

#include "../Core/Util.h"
#include "../ClassHeaders/MatchRule.h"


MatchRule::MatchRule(std::string rule) {
	std::vector<std::string> ruleParts = split<std::string>(rule, ":");
	int ruleNum = stoi(ruleParts[0]);
	unparsedRules = ruleParts[1];
	allRules[ruleNum] = this;
}

int MatchRule::matches0(std::string s, int modified) {
	//rule 0: 42 42 31
	//modified rule 0: 42*x 42*y 31*y

	std::vector<std::string> match31 = allRules[31]->match;
	std::vector<std::string> match42 = allRules[42]->match;
	int partLength = match31[0].length();

	if (s.length() % partLength != 0) {
		return 0;
	}
	else if (s.length() / partLength < 3 || (s.length() / partLength > 3 && !modified)) {
		return 0;
	}

	int partCt = 0;
	int count42 = 1;
	for (size_t i = 0; i * partLength < s.length(); i++) {
		std::string part = s.substr(i * partLength, partLength);
		int inPart31 = 0;
		int inPart42 = 0;
		for (std::string p31 : match31) {
			if (part == p31) {
				inPart31 = 1;
			}
		}
		for (std::string p42 : match42) {
			if (part == p42) {
				inPart42 = 1;
			}
		}

		if (!inPart31 && !inPart42) {
			return 0;
		}


		if (!count42 && !inPart31) {
			return 0;
		}

		if (!inPart42 || !count42) {
			count42 = 0;
			partCt--;
			if (partCt < 1) {
				return 0;
			}
		}
		else {
			partCt++;
		}
	}

	return count42 == 0;
}

void MatchRule::init(std::vector<std::string> rules) {
	ruleCount = rules.size();
	if (ruleCount < 43) {
		ruleCount = 43;
	}
	allRules = (MatchRule**)malloc(ruleCount * sizeof(MatchRule*));
	for (std::string rule : rules) {
		new MatchRule(rule);
	}

	allRules[31]->matchStrs();
	allRules[42]->matchStrs();
}

void MatchRule::cleanup() {
	for (size_t i = 0; i < ruleCount; i++) {
		delete allRules[i];
	}

	free(allRules);
}

std::vector<std::string> MatchRule::matchStrs() {

	if (match.empty()) {
		std::regex constRule("\\s*\"(.*)\"\\s*");
		std::smatch smatch;

		for (std::string unparsedRule : split<std::string>(unparsedRules, "\\|")) {
			if (std::regex_match(unparsedRule, smatch, constRule)) {
				match.push_back(smatch.str(1));
			}
			else {
				for (std::string rule : combineRules(split<int>(unparsedRule, " "))) {
					match.push_back(rule);
				}
			}
		}
	}

	return match;
}

std::vector<std::string> MatchRule::combineRules(std::vector<int> rules) {
	if (rules.size() == 1) {
		return allRules[rules[0]]->matchStrs();
	}

	int lastRule = rules.back();
	rules.pop_back();

	std::vector<std::string> subRules = combineRules(rules);
	std::vector<std::string> lastRules = allRules[lastRule]->matchStrs();
	std::vector<std::string> newRules;

	for (std::string subRule : subRules) {
		for (std::string subLastRule : lastRules) {
			newRules.push_back(subRule + subLastRule);
		}
	}

	return newRules;
}

size_t MatchRule::ruleCount;
MatchRule** MatchRule::allRules;