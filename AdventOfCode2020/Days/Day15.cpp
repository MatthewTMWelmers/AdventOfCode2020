#include <vector>
#include <map>

int getNumber(std::vector<int> inputs, int num)
{
	int size = inputs.size() - 1;
	int back = inputs.back();

	int* last = (int*)malloc(num * sizeof(int));
	if (!last) {
		return 0;
	}

	for (int i = 0; i < num; i++) {
		last[i] = 0;
	}
	for (int i = 0; i < size; i++) {
		last[inputs[i]] = i + 1;
	}

	while (size < num - 1) {
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

int day15star1(std::vector<int> inputs) {
	return getNumber(inputs, 2020);
}

int day15star2(std::vector<int> inputs) {
	return getNumber(inputs, 30000000);
}