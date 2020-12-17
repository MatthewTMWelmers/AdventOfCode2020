#pragma once
class BagRule {
public:
	BagRule(std::string name);
	void addContents(std::string contentsString);
	int canContain(std::string contained);
	int mustContain();
	void updatePointers(std::map<std::string, BagRule*> rules);


private:
	std::string name;
	std::vector<std::pair<std::string, int>> contentCounts;
	std::map<std::string, BagRule*> contents;
	std::map<std::string, int> nestedContainCache;
	int mustContainCount;
};