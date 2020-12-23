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

std::string day23star1(std::string input) {
	Cup** cupList = (Cup**)malloc(10 * sizeof(Cup*));
	if (!cupList) {
		return 0;
	}

	Cup* current = new Cup(input[0] - '0');
	cupList[current->val - 1] = current;
	Cup* last = current;
	for (size_t i = 1; i < 9; i++) {
		Cup* prev = last;
		last = new Cup(input[i] - '0');
		prev->next = last;
		cupList[last->val - 1] = last;
	}
	last->next = current;

	for (size_t i = 0; i < 100; i++) {
		current = iter(current, cupList, 9);
	}

	current = cupList[0];
	std::string result = "";
	for (size_t i = 0; i < 8; i++) {
		current = current->next;
		result += std::to_string(current->val);
	}

	return result;
}


long long day23star2(std::string input) {
	Cup** cupList = (Cup**)malloc(10000000 * sizeof(Cup*));
	if (!cupList) {
		return 0;
	}

	Cup* current = new Cup(input[0] - '0');
	cupList[current->val - 1] = current;
	Cup* last = current;
	for (size_t i = 1; i < 9; i++) {
		Cup* prev = last;
		last = new Cup(input[i] - '0');
		prev->next = last;
		cupList[last->val - 1] = last;
	}
	for (size_t i = 10; i <= 1000000; i++) {
		Cup* prev = last;
		last = new Cup(i);
		prev->next = last;
		cupList[last->val - 1] = last;
	}
	last->next = current;

	for (size_t i = 0; i < 10000000; i++) {
		current = iter(current, cupList, 1000000);
	}

	current = cupList[0];
	return current->next->val * current->next->next->val;
}