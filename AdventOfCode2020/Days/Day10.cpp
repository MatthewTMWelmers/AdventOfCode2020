#include <vector>
#include <queue>
#include <algorithm>

long long subCombos(std::vector<int> diffs) {
	if (diffs.size() < 2) {
		return 1;
	}

	int back = diffs.back();
	diffs.pop_back();

	long long partial = subCombos(diffs);
	if (back + diffs.back() < 4) {
		int back2 = diffs.back();
		diffs.pop_back();
		diffs.push_back(back + back2);
		return partial + subCombos(diffs);
	}
	else {
		return partial;
	}
}

int day10star1(std::vector<int> inputs) {
	inputs.push_back(0);
	std::sort(inputs.begin(), inputs.end());
	inputs.push_back(inputs.back() + 3);


	int ones = 0;
	int threes = 0;
	for (int i = 1; i < inputs.size(); i++) {
		int diff = inputs[i] - inputs[i - 1];
		if (diff == 1) {
			ones++;
		}
		if (diff == 3) {
			threes++;
		}
	}

	return ones * threes;
}

long long day10star2(std::vector<int> inputs) {
	inputs.push_back(0);
	std::sort(inputs.begin(), inputs.end());
	inputs.push_back(inputs.back() + 3);
	std::vector<int> diffs;

	long long combos = 1;
	for (int i = 1; i < inputs.size(); i++) {
		int diff = inputs[i] - inputs[i - 1];
		if (diff == 3) {
			combos *= subCombos(diffs);
			diffs.clear();
		}
		else {
			diffs.push_back(diff);
		}
	}

	return combos;
}