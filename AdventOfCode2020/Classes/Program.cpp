#include <string>
#include <vector>
#include <set>

#include "../ClassHeaders/Program.h"

std::vector<Instruction> instructionSet(std::vector<std::string> inputs) {
	std::vector<Instruction> instructions;
	for (std::string s : inputs) {
		instructions.push_back(Instruction(s));
	}

	return instructions;
}

Program::Program(std::vector<std::string> inputs) {
	instructions = instructionSet(inputs);
	reset();
}

int Program::tryRepair() {
	for (int i = 0; i < instructions.size(); i++) {
		if (instructions[i].op == "acc") {
			continue;
		}
		if (instructions[i].op == "nop") {
			instructions[i].op = "jmp";
			if (isInfinite()) {
				instructions[i].op = "nop";
			}
			else {
				return 1;
			}
		}

		if (instructions[i].op == "jmp") {
			instructions[i].op = "nop";
			if (isInfinite()) {
				instructions[i].op = "jmp";
			}
			else {
				return 1;
			}
		}
	}

	return 0;
}

int Program::isInfinite() {
	reset();
	std::set<int> run;

	while (true) {
		if (run.count(i)) {
			return 1;
		}
		if (i >= instructions.size()) {
			return 0;
		}

		run.insert(i);
		i = instructions[i].act(i, &acc);
	}
}

int Program::run() {
	isInfinite();
	return acc;
}

void Program::reset() {
	i = 0;
	acc = 0;
}
