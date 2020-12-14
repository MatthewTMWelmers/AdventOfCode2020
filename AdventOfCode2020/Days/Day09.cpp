#include <vector>
#include <numeric>
#include <algorithm>

int isValidSum(long long x, std::vector<long long> list) {
	for (int i = 0; i < list.size(); i++) {
		for (int j = 0; j < list.size(); j++) {
			if (i != j && list[i] + list[j] == x) {
				return 1;
			}
		}
	}
	return 0;
}

long long day9star1(std::vector<long long> inputs) {
	for (int i = 25; i < inputs.size(); i++) {
		if (!isValidSum(inputs[i], std::vector<long long>(inputs.begin() + i - 25, inputs.begin() + i))) {
			return inputs[i];
		}
	}
	return 0;
}

long long day9star2(std::vector<long long> inputs) {
	long long bad = day9star1(inputs);
	for (int i = 0; i < inputs.size(); i++) {
		for (int j = 0; j < inputs.size() - i; j++) {
			long long sum = std::accumulate(inputs.begin() + i, inputs.begin() + i + j, 0LL);
			if (sum > bad) {
				break;
			}
			if (sum == bad) {
				std::vector<long long> nums(inputs.begin() + i, inputs.begin() + i + j);
				std::sort(nums.begin(), nums.end());
				return nums.front() + nums.back();
			}
		}
	}

	return 0;
}