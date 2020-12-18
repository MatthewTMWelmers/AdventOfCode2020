#include <vector>
#include <string>

#include "../ClassHeaders/OpTree.h"

long long day18star1(std::vector<std::string> inputs) {
	long long total = 0;
	for (std::string exp : inputs) {
		OpTree* op = OpTree::parse(exp);
		total += op->eval();
		delete op;
	}

	return total;
}

long long  day18star2(std::vector<std::string> inputs) {
	long long total = 0;
	for (std::string exp : inputs) {
		OpTree* op = OpTree::parse(exp);
		op = op->rebalance();
		total += op->eval();
		delete op;
	}

	return total;
}