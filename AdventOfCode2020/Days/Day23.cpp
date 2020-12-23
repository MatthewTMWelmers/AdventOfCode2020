#include<vector>
#include<string>

struct Cup {
	Cup(long long val) {
		this->val = val;
	}

	Cup* next;
	long long val;
};

Cup* iter(Cup* current, Cup** cupList, int max) {
	Cup* next = current->next;
	current->next = current->next->next->next->next;
	int move = current->val;
	do {
		move--;
		if (move < 1) move = max;
	} while (next->val == move || next->next->val == move || next->next->next->val == move);
	Cup* moveTo = cupList[move - 1];
	next->next->next->next = moveTo->next;
	moveTo->next = next;
	return current->next;
}

Cup* cupGame(std::string init, size_t maxCup, size_t iterations) {
	Cup** cupList = (Cup**)malloc(10000000 * sizeof(Cup*));
	if (!cupList) {
		return 0;
	}

	Cup* current = new Cup(init[0] - '0');
	cupList[current->val - 1] = current;
	Cup* last = current;
	for (size_t i = 1; i < 9; i++) {
		Cup* prev = last;
		last = new Cup(init[i] - '0');
		prev->next = last;
		cupList[last->val - 1] = last;
	}
	for (size_t i = 10; i <= maxCup; i++) {
		Cup* prev = last;
		last = new Cup(i);
		prev->next = last;
		cupList[last->val - 1] = last;
	}
	last->next = current;

	for (size_t i = 0; i < iterations; i++) {
		current = iter(current, cupList, maxCup);
	}

	Cup* cup0 = cupList[0];
	free(cupList);
	return cup0;
}

void cleanup(Cup* cup, size_t maxCup) {
	for (size_t i = 0; i < maxCup; i++) {
		Cup* curr = cup;
		cup = cup->next;
		delete curr;
	}
}

std::string day23star1(std::string input) {
	Cup* current = cupGame(input, 9, 100);
	std::string result = "";
	for (size_t i = 0; i < 8; i++) {
		current = current->next;
		result += std::to_string(current->val);
	}

	cleanup(current, 9);
	return result;
}


long long day23star2(std::string input) {
	Cup* current = cupGame(input, 1000000, 10000000);
	long long result = current->next->val * current->next->next->val;
	cleanup(current, 1000000);
	return result;
}