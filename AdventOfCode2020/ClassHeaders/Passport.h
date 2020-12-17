#pragma once
#include <vector>
#include <string>
#include <map>

class Passport {
public:
	Passport(std::vector<std::string>* init);
	int hasAllFields();
	int isValid();
private:
	std::map<std::string, std::string> values;
	void addLine(std::string line);
	void addKV(std::string kV);
};