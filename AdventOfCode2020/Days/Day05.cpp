#include <vector>
#include <string>
#include <algorithm>
#include <iterator>

int binarySearch(int min, int max, char lower, std::string input) {
	if (min == max - 1) {
		return input[0] == lower ? min : max;
	}

	int split = (1 + min + max) / 2;
	if (input[0] == lower) {
		return binarySearch(min, split - 1, lower, input.substr(1));
	}
	else {
		return binarySearch(split, max, lower, input.substr(1));
	}
	
}

int seatId(std::string pass) {
	std::string fb = pass.substr(0, 7);
	std::string lr = pass.substr(7);

	int row = binarySearch(0, 127, 'F', fb);
	int col = binarySearch(0, 7, 'L', lr);

	return row * 8 + col;
}

int day5star1(std::vector<std::string> inputs) {
	int max = 0;
	for (std::string pass : inputs) {
		int seat = seatId(pass);
		if (seat > max) {
			max = seat;
		}
	}

	return max;
}

int day5star2(std::vector<std::string> inputs) {
	std::vector<int> sids;
	std::transform(inputs.begin(), inputs.end(), std::back_inserter(sids), [](auto s) -> int { return seatId(s); });
	std::sort(sids.begin(), sids.end());

	int last = 0;
	for (int i : sids) {
		if (i == last + 2) {
			return i - 1;
		}
		else {
			last = i;
		}
	}

	return -1;
}
