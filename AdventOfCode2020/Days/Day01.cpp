#include <vector>

int day1star1(std::vector<int> inputs) {
	for (size_t i = 0; i < inputs.size(); i++) {
		for (size_t j = 0; j < inputs.size(); j++) {
			if (i == j)
				continue;
			if (inputs[i] + inputs[j] == 2020) {
				return inputs[i] * inputs[j];
			}
		}
	}

	return 0;
}

int day1star2(std::vector<int> inputs) {
	for (size_t i = 0; i < inputs.size(); i++) {
		for (size_t j = 0; j < inputs.size(); j++) {
			for (size_t k = 0; k < inputs.size(); k++) {
				if (i == j || i == k || j == k)
					continue;
				if (inputs[i] + inputs[j] + inputs[k] == 2020) {
					return inputs[i] * inputs[j] * inputs[k];
				}
			}
		}
	}

	return 0;
}
