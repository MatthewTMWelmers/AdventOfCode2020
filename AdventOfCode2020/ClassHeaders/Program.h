#pragma once
#include <regex>

struct Instruction {
	Instruction(std::string instruction) {
		std::regex regex("^(...) (.\\d+)$");
		std::smatch match;
		std::regex_match(instruction, match, regex);


		op = match.str(1);
		arg = stoi(match.str(2));
	}

	int act(int i, int* acc) {
		if (op == "acc") { *acc += arg;  return i + 1; }
		if (op == "jmp") { return i + arg; }
		if (op == "nop") { return i + 1; }
	}

	std::string op;
	int arg;
};

class Program {
public:
	Program(std::vector<std::string> inputs);
	int tryRepair();
	int run();


private:
	std::vector<Instruction> instructions;
	int i;
	int acc;
	void reset();
	int isInfinite();
};