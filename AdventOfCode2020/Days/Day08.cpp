#include <vector>
#include <string>
#include <regex>
#include <set>

class Instruction {
public:
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
	Program(std::vector<Instruction> instructions) {
		reset();
		this->instructions = instructions;
	}

	int tryRepair() {
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

	int isInfinite() {
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

	int run() {
		isInfinite();
		return acc;
	}

	void reset() {
		i = 0;
		acc = 0;
	}

private:
	std::vector<Instruction> instructions;
	int i;
	int acc;
};

std::vector<Instruction> instructionSet(std::vector<std::string> inputs) {
	std::vector<Instruction> instructions;
	for (std::string s : inputs) {
		instructions.push_back(Instruction(s));
	}

	return instructions;
}

int day8star1(std::vector<std::string> inputs) {
	std::vector<Instruction> instructions = instructionSet(inputs);
	Program p(instructions);

	return p.run();
	
}

int day8star2(std::vector<std::string> inputs) {
	std::vector<Instruction> instructions = instructionSet(inputs);
	Program p(instructions);

	if (p.tryRepair()) {
		return p.run();
	}

	return 0;
}