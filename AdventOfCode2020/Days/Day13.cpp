#include <vector>
#include <string>
#include <regex>
#include <boost/math/common_factor.hpp>

long long day13star1(std::vector<std::string> inputs) {
	int time = stoi(inputs[0]);
	std::vector<int> busses;

	std::regex regex("\\d+");
	std::smatch match;

	while (std::regex_search(inputs[1], match, regex)) {
		busses.push_back(stoi(match.str(0)));
		inputs[1] = match.suffix();
	}

	std::vector<std::pair<long long, long long>> busWaits;
	for (int i : busses) {
		busWaits.push_back(std::pair<int, int>(i - (time % i), i));
	}

	std::sort(busWaits.begin(), busWaits.end(), [](auto x, auto y) -> int { return x.first < y.first; });
	return busWaits[0].first * busWaits[0].second;
}

long long day13star2(std::vector<std::string> inputs) {
	std::vector<int> busses;

	std::regex regex("\\d+|x");
	std::smatch match;

	while (std::regex_search(inputs[1], match, regex)) {
		if (match.str(0) == "x") {
			busses.push_back(0);
		}
		else {
			busses.push_back(stoi(match.str(0)));
		}
		inputs[1] = match.suffix();
	}

	long long ts = 0;
	long long addl = 1;
	while (true) {
		int valid = 1;
		for (size_t i = 0; i < busses.size(); i++) {
			if (busses[i] != 0) {
				if ((ts + i) % busses[i] != 0) {
					valid = 0;
					break;
				}
				else if(addl % busses[i] != 0) {
					addl = boost::math::lcm(addl, (long long)busses[i]);
				}
			}
		}

		if (valid) {
			return ts;
		}

		ts += addl;
	}

	return 0;
}