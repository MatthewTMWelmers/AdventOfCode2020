#pragma once

class MatchRule {
public:
	std::string unparsedRules;
	std::vector<std::string> match;

	MatchRule(std::string rule);
	static int matches0(std::string s, int modified);
	static void init(std::vector<std::string> rules);
	static void cleanup();

private:
	static size_t ruleCount;
	static MatchRule** allRules;

	std::vector<std::string> matchStrs();
	std::vector<std::string> combineRules(std::vector<int> rules);
};
