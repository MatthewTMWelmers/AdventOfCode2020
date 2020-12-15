#include <vector>
#include <map>

int day15star1(std::vector<int> inputs) {
	int size = inputs.size() - 1;
	int back = inputs.back();

	int* last = (int*)malloc(2020 * sizeof(int));
	if (!last) {
		return 0;
	}

	for (int i = 0; i < 2020; i++) {
		last[i] = 0;
	}
	for (int i = 0; i < size; i++) {
		last[inputs[i]] = i + 1;
	}

	while (size < 2020 - 1) {
		int next;

		int lastVal = last[back];
		if (lastVal == 0) {
			next = 0;
		}
		else {
			next = size - lastVal + 1;
		}

		last[back] = size + 1;
		back = next;
		size++;
	}

	free(last);
	return back;
}

int day15star2(std::vector<int> inputs) {
	int size = inputs.size() - 1;
	int back = inputs.back();

	int* last = (int*)malloc(30000000 * sizeof(int));
	if (!last) {
		return 0;
	}

	for (int i = 0; i < 30000000; i++) {
		last[i] = 0;
	}
	for (int i = 0; i < size; i++) {
		last[inputs[i]] = i + 1;
	}

	while (size < 30000000 - 1) {
		int next;

		int lastVal = last[back];
		if (lastVal == 0) {
			next = 0;
		}
		else {
			next = size - lastVal + 1;
		}

		last[back] = size + 1;
		back = next;
		size++;
	}

	free(last);
	return back;
}