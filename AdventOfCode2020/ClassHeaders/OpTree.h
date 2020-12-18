#pragma once
#include <string>
#include <map>

class OpTree {

public:
	OpTree(std::string op) {
		this->op = op;
		lchild = NULL;
		rchild = NULL;
		parent = NULL;
	}

	~OpTree() {
		if (lchild) delete lchild;
		if (rchild) delete rchild;
	}

	long long eval();
	OpTree* rebalance();

	static OpTree* parse(std::string exp) { return parse(exp, std::map<char, OpTree*>(), 'a'); }

private:
	std::string op;

	OpTree* parent;
	OpTree* lchild;
	OpTree* rchild;

	OpTree* root();
	static OpTree* parse(std::string exp, std::map<char, OpTree*> subs, char sub);

};