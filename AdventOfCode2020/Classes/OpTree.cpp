#include <string>
#include <regex>
#include <map>

#include "../ClassHeaders/OpTree.h"

OpTree* OpTree::root() {
	if (parent) return parent->root();
	return this;
}

long long OpTree::eval() {
	if (op == "+") return lchild->eval() + rchild->eval();
	if (op == "*") return lchild->eval() * rchild->eval();
	if (op == "(") return lchild->eval();
	return stoll(op);
}

OpTree* OpTree::rebalance() {
	if (lchild) {
		lchild->parent = this;
		lchild->rebalance();

		if (op == "+" && lchild->op == "*") {
			lchild->parent = parent;

			if (parent) {
				if (parent->lchild == this) parent->lchild = lchild;
				else parent->rchild = lchild;
			}

			parent = lchild;
			lchild = parent->rchild;
			parent->rchild = this;
		}
	}

	if (rchild) {
		rchild->parent = this;
		rchild->rebalance();
	}

	return root();
}

OpTree* OpTree::parse(std::string exp, std::map<char, OpTree*> subs, char sub) {
	std::regex parenRegex("\\(([^\\(]*?)\\)");
	std::regex operatorRegex("^([0-9a-z]+)([\\+\\*])([0-9a-z]+)");
	std::smatch match;

	size_t spacePos;
	while ((spacePos = exp.find(" ")) != std::string::npos) {
		exp = exp.erase(spacePos, 1);
	}

	while (std::regex_search(exp, match, parenRegex)) {
		OpTree* parenTree = new OpTree("(");
		OpTree* subTree = parse(match.str(1), subs, sub);
		parenTree->lchild = subTree;
		subs[sub] = parenTree;

		exp = (std::string)match.prefix() + sub + (std::string)match.suffix();
		sub++;
	}

	while (std::regex_search(exp, match, operatorRegex)) {
		OpTree* parenTree = new OpTree(match.str(2));

		if (subs.find(match.str(1)[0]) != subs.end()) {
			parenTree->lchild = subs[match.str(1)[0]];
		}
		else {
			parenTree->lchild = new OpTree(match.str(1));
		}


		if (subs.find(match.str(3)[0]) != subs.end()) {
			parenTree->rchild = subs[match.str(3)[0]];
		}
		else {
			parenTree->rchild = new OpTree(match.str(3));
		}

		subs[sub] = parenTree;
		exp = sub + (std::string)match.suffix();
		sub++;
	}

	return subs[exp[0]];
}